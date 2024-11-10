/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright 2016 Michal Meloun <mmel@FreeBSD.org>
 *
 * Copyright (c) 2020 Oskar Holmlund <oskar.holmlund@ohdata.se>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include <sys/fbio.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/rman.h>
#include <sys/resource.h>
#include <machine/bus.h>
#include <vm/vm.h>
#include <vm/vm_extern.h>
#include <vm/vm_kern.h>
#include <vm/pmap.h>

#include <dev/extres/clk/clk_gate.h>
#include <dev/extres/clk/clk_div.h>
#include <dev/extres/clk/clk_mux.h>
#include <dev/fdt/simplebus.h>

#include <dev/ofw/ofw_bus.h>
#include <dev/ofw/ofw_bus_subr.h>

#include <arm/ti/clk/am33xx.h>
#include <arm/ti/clk/ti_clock_common.h>
#include <arm/ti/clk/ti_clk_clkctrl.h>
#include <arm/ti/ti_omap4_cm.h>
#include <arm/ti/ti_cpuid.h>
#include <dt-bindings/clock/am3.h>

#if 0
#define DPRINTF(dev, msg...) device_printf(dev, msg)
#else
#define DPRINTF(dev, msg...)
#endif

/* Documentation/devicetree/bindings/clock/ti-clkctrl.txt */

#define TI_CLKCTRL_L4_WKUP	5
#define TI_CLKCTRL_L4_SECURE	4
#define TI_CLKCTRL_L4_PER	3
#define TI_CLKCTRL_L4_CFG	2
#define TI_CLKCTRL		1
#define TI_CLKCTRL_END		0

static struct ofw_compat_data compat_data[] = {
	{ "ti,clkctrl-l4-wkup",		TI_CLKCTRL_L4_WKUP },
	{ "ti,clkctrl-l4-secure",	TI_CLKCTRL_L4_SECURE },
	{ "ti,clkctrl-l4-per",		TI_CLKCTRL_L4_PER },
	{ "ti,clkctrl-l4-cfg",		TI_CLKCTRL_L4_CFG },
	{ "ti,clkctrl",			TI_CLKCTRL },
	{ NULL,				TI_CLKCTRL_END }
};

struct ti_clkctrl_softc {
	device_t			dev;

	struct clkdom			*clkdom;
};

static int ti_clkctrl_probe(device_t dev);
static int ti_clkctrl_attach(device_t dev);
static int ti_clkctrl_detach(device_t dev);
int clkctrl_ofw_map(struct clkdom *clkdom, uint32_t ncells,
    phandle_t *cells, struct clknode **clk);

static int
create_clkctrl(struct ti_clkctrl_softc *sc, struct ti_clkctrl_lookup_table *table, int nitems, uint32_t reg_offset);

static int
ti_clkctrl_probe(device_t dev)
{
	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data == 0)
		return (ENXIO);

	device_set_desc(dev, "TI clkctrl");
	if (bootverbose == 0)
		device_quiet(dev);


	return (BUS_PROBE_DEFAULT);
}

static int
ti_clkctrl_attach(device_t dev)
{
	struct ti_clkctrl_softc *sc;
	phandle_t node;
	cell_t	*reg;
	ssize_t numbytes_reg;
	int err, ti_clock_cells;
	const char *org_name;
	uint64_t parent_offset;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	/* Sanity check */
	err = OF_searchencprop(node, "#clock-cells",
		&ti_clock_cells, sizeof(ti_clock_cells));
	if (err == -1) {
		DPRINTF(sc->dev, "Failed to get #clock-cells\n");
		return (ENXIO);
	}

	if (ti_clock_cells != 2) {
		DPRINTF(sc->dev, "clock cells(%d) != 2\n",
			ti_clock_cells);
		return (ENXIO);
	}

	/* Grab the content of reg properties */
	numbytes_reg = OF_getproplen(node, "reg");
	if (numbytes_reg == 0) {
		DPRINTF(sc->dev, "reg property empty - check your devicetree\n");
		return (ENXIO);
	}

	reg = malloc(numbytes_reg, M_DEVBUF, M_WAITOK);
	OF_getencprop(node, "reg", reg, numbytes_reg);

	/* Create clock domain */
	sc->clkdom = clkdom_create(sc->dev);
	if (sc->clkdom == NULL) {
		free(reg, M_DEVBUF);
		DPRINTF(sc->dev, "Failed to create clkdom\n");
		return (ENXIO);
	}
	clkdom_set_ofw_mapper(sc->clkdom, clkctrl_ofw_map);

	/* Create clock nodes */
	/* name */
	clk_parse_ofw_clk_name(sc->dev, node, &org_name);

	/* Get parent range */
	parent_offset = ti_omap4_cm_get_simplebus_base_host(device_get_parent(dev));

	/* Find which clkctrl to populate */
	switch (ti_chip()) {
#ifdef SOC_OMAP4
	case CHIP_OMAP_4:
		/* FIXME: Todo */
		break;
#endif /* SOC_OMAP4 */

#ifdef SOC_TI_AM335X
	/* Checkout TRM 8.1.12.1.29 - 8.1.12.31 and 8.1.12.2.3
	 * and the DTS.
	 */
	case CHIP_AM335X:
	if (strcmp(org_name, "l4ls_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_l4ls_clkctrl_table,
		    nitems(am33xx_l4ls_clkctrl_table), parent_offset + AM3_L4LS_CLKCTRL_OFFSET);
	else if (strcmp(org_name, "l3s_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_l3s_clkctrl_table,
		    nitems(am33xx_l3s_clkctrl_table), parent_offset + AM3_L3S_CLKCTRL_OFFSET);
	else if (strcmp(org_name, "l3_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_l3_clkctrl_table,
		    nitems(am33xx_l3_clkctrl_table), parent_offset + AM3_L3_CLKCTRL_OFFSET);
	else if (strcmp(org_name, "l4hs_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_l4hs_clkctrl_table,
		    nitems(am33xx_l4hs_clkctrl_table), parent_offset + AM3_L4HS_CLKCTRL_OFFSET);
	else if (strcmp(org_name, "pruss_ocp_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_pruss_clkctrl_table,
		    nitems(am33xx_pruss_clkctrl_table), parent_offset + AM3_PRUSS_OCP_CLKCTRL_OFFSET);
	else if (strcmp(org_name, "cpsw_125mhz_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_cpsw_clkctrl_table,
		    nitems(am33xx_cpsw_clkctrl_table), parent_offset + 0);
	else if (strcmp(org_name, "lcdc_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_lcdc_clkctrl_table,
		    nitems(am33xx_lcdc_clkctrl_table), parent_offset + AM3_LCDC_CLKCTRL_OFFSET);
	else if (strcmp(org_name, "clk_24mhz_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_clk_24mhz_clkctrl_table,
		    nitems(am33xx_clk_24mhz_clkctrl_table), parent_offset + AM3_CLK_24MHZ_CLKCTRL_OFFSET);
	else if (strcmp(org_name, "l4_wkup_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_l4_wkup_clkctrl_table,
		    nitems(am33xx_l4_wkup_clkctrl_table), parent_offset + 0);
	else if (strcmp(org_name, "l3_aon_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_l3_aon_clkctrl_table,
		    nitems(am33xx_l3_aon_clkctrl_table), parent_offset + AM3_L3_AON_CLKCTRL_OFFSET);
	else if (strcmp(org_name, "l4_wkup_aon_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_l4_wkup_aon_clkctrl_table,
		    nitems(am33xx_l4_wkup_aon_clkctrl_table), parent_offset + AM3_L4_WKUP_AON_CLKCTRL_OFFSET);
	else if (strcmp(org_name, "mpu_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_mpu_clkctrl_table,
		    nitems(am33xx_mpu_clkctrl_table), parent_offset + 0);
	else if (strcmp(org_name, "l4_rtc_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_l4_rtc_clkctrl_table,
		    nitems(am33xx_l4_rtc_clkctrl_table), parent_offset + 0);
	else if (strcmp(org_name, "gfx_l3_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_gfx_l3_clkctrl_table,
		    nitems(am33xx_gfx_l3_clkctrl_table), parent_offset + 0);
	else if (strcmp(org_name, "l4_cefuse_clkctrl") == 0)
		err = create_clkctrl(sc, am33xx_l4_cefuse_clkctrl_table,
		    nitems(am33xx_l4_cefuse_clkctrl_table), parent_offset + 0);
	else
		panic("Not expected clkctrl %s", org_name);
	break;
#endif /* SOC_TI_AM335X */
	default:
		break;
	}

	if (err != 0) {
		DPRINTF(sc->dev, "%s failed to create clock\n",
			org_name);
		err = ENXIO;
		goto cleanup;
	}


	err = clkdom_finit(sc->clkdom);
	if (err != 0) {
		DPRINTF(sc->dev, "Clk domain finit fails %x.\n", err);
		err = ENXIO;
		goto cleanup;
	}

cleanup:
	OF_prop_free(__DECONST(char *, org_name));

	free(reg, M_DEVBUF);

	if (err != 0)
		return (err);

	return (bus_generic_attach(dev));
}

static int
ti_clkctrl_detach(device_t dev)
{
	return (EBUSY);
}

/* modified version of default mapper from clk.c */
int
clkctrl_ofw_map(struct clkdom *clkdom, uint32_t ncells,
    phandle_t *cells, struct clknode **clk) {
	if (ncells == 0)
		*clk = clknode_find_by_id(clkdom, 1);
	else if (ncells == 1)
		*clk = clknode_find_by_id(clkdom, cells[0]);
	else if (ncells == 2) {
		/* To avoid collision with other IDs just add one.
		 * All other registers has an offset of 4 from each other.
		 */
		if (cells[1])
			*clk = clknode_find_by_id(clkdom, cells[0]+1);
		else
			*clk = clknode_find_by_id(clkdom, cells[0]);
	}
	else
		return (ERANGE);

	if (*clk == NULL)
		return (ENXIO);

	return (0);
}

static int
create_clkctrl(struct ti_clkctrl_softc *sc, struct ti_clkctrl_lookup_table *table, int nitems, uint32_t reg_offset) {
	struct ti_clk_clkctrl_def 	clkctrl;
	struct clk_gate_def		gate;
	struct clk_mux_def		mux;
	struct clk_div_def		divider;
	int err;

	for (int index = 0; index < nitems; index++) {
	switch (table[index].clk_type) {
	case TI_CLKCTRL_NO_SUB_CLOCK:
		DPRINTF(sc->dev, "NO_SUB_CLOCK: %s\n", table[index].node_name);
		/* set flags and name */
		clkctrl.clkdef.flags = CLK_NODE_STATIC_STRINGS;
		clkctrl.clkdef.name = table[index].node_name;
		clkctrl.clkdef.id = table[index].offset + table[index].id_subclock;

		/* Handle parents */
		clkctrl.clkdef.parent_cnt = table[index].parent_cnt;
		clkctrl.clkdef.parent_names = table[index].parents;

		clkctrl.register_offset = table[index].offset + reg_offset;
		clkctrl.flags = table[index].flags;

		/* Register the clkctrl */
		err = ti_clknode_clkctrl_register(sc->clkdom, &clkctrl);
		break;
	case TI_CLKCTRL_GATE:
		DPRINTF(sc->dev, "GATE %s\n", table[index].node_name);
		/* set flags and name */
		gate.clkdef.flags = CLK_NODE_STATIC_STRINGS;
		gate.clkdef.name = table[index].node_name;
		gate.clkdef.id = table[index].offset + table[index].id_subclock;
		gate.clkdef.parent_names = table[index].parents;
		gate.clkdef.parent_cnt = table[index].parent_cnt;

		gate.offset = table[index].offset + reg_offset;
		gate.shift = table[index].shift;
		gate.mask = table[index].mask;
		gate.on_value = 1;
		gate.off_value = 0;
		gate.gate_flags = 0;

		err = clknode_gate_register(sc->clkdom, &gate);
		break;
	case TI_CLKCTRL_MUX:
		DPRINTF(sc->dev, "MUX %s\n", table[index].node_name);
		/* set flags and name */
		mux.clkdef.flags = CLK_NODE_STATIC_STRINGS;
		mux.clkdef.name = table[index].node_name;
		mux.clkdef.id = table[index].offset + table[index].id_subclock;
		mux.clkdef.parent_names = table[index].parents;
		mux.clkdef.parent_cnt = table[index].parent_cnt;

		mux.offset = table[index].offset + reg_offset;
		mux.shift = table[index].shift;
		mux.width = fls(table[index].mask >> table[index].shift);

		err = clknode_mux_register(sc->clkdom, &mux);
		break;
	case TI_CLKCTRL_DIVIDER:
		DPRINTF(sc->dev, "DIVIDER %s\n", table[index].node_name);
		/* set flags and name */
		divider.clkdef.flags = CLK_NODE_STATIC_STRINGS;
		divider.clkdef.name = table[index].node_name;
		divider.clkdef.id = table[index].offset + table[index].id_subclock;
		divider.clkdef.parent_names = table[index].parents;
		divider.clkdef.parent_cnt = table[index].parent_cnt;

		divider.offset = table[index].offset + reg_offset;
		divider.i_shift = table[index].shift;
		divider.i_width = fls(table[index].mask >> table[index].shift);
		divider.f_shift = 0;
		divider.f_width = 0;
		divider.div_flags = 0;
		divider.div_table = NULL;

		err = clknode_div_register(sc->clkdom, &divider);
		break;
	default:
		panic("clk_type %x not implemented\n",
			table[index].clk_type);
		break;
	}

	if (err != 0) {
		DPRINTF(sc->dev,
			"ti_clknode_clkctrl_register[%d:%d] failed %x\n",
			index, reg_offset, err);
		err = ENXIO;
		break;
	}
	} /* for */
	return (err);
}

static device_method_t ti_clkctrl_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe,		ti_clkctrl_probe),
	DEVMETHOD(device_attach,	ti_clkctrl_attach),
	DEVMETHOD(device_detach,	ti_clkctrl_detach),

	DEVMETHOD_END
};

DEFINE_CLASS_0(ti_clkctrl, ti_clkctrl_driver, ti_clkctrl_methods,
    sizeof(struct ti_clkctrl_softc));

EARLY_DRIVER_MODULE(ti_clkctrl, simplebus, ti_clkctrl_driver, 0, 0,
    BUS_PASS_BUS + BUS_PASS_ORDER_MIDDLE);

MODULE_VERSION(ti_clkctrl, 1);
