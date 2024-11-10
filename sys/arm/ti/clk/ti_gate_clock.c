/*-
 * SPDX-License-Identifier: BSD-2-Clause
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
#include <sys/conf.h>
#include <sys/bus.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/systm.h>
#include <sys/libkern.h>

#include <machine/bus.h>
#include <dev/fdt/simplebus.h>

#include <dev/ofw/ofw_bus.h>
#include <dev/ofw/ofw_bus_subr.h>
#include <dev/extres/clk/clk_gate.h>
#include <dev/extres/syscon/syscon.h>

#include <arm/ti/clk/am33xx.h>
#include <arm/ti/clk/ti_clock_common.h>
#include <arm/ti/clk/ti_clksel.h>
#include "clkdev_if.h"
#include "syscon_if.h"

#define DEBUG_GATE	0

#if DEBUG_GATE
#define DPRINTF(dev, msg...) device_printf(dev, msg)
#else
#define DPRINTF(dev, msg...)
#endif

struct ti_gate_softc {
	device_t		dev;
	uint8_t			sc_type;

	struct clk_gate_def	gate_def;
	struct clkdom		*clkdom;
	struct syscon		*syscon;
};

static int ti_gate_probe(device_t dev);
static int ti_gate_attach(device_t dev);
static int ti_gate_detach(device_t dev);

#define TI_GATE_CLOCK			7
#define TI_WAIT_GATE_CLOCK		6
#define TI_DSS_GATE_CLOCK		5
#define TI_AM35XX_GATE_CLOCK		4
#define TI_CLKDM_GATE_CLOCK		3
#define TI_HSDIV_GATE_CLOCK		2
#define TI_COMPOSITE_NO_WAIT_GATE_CLOCK	1
#define TI_GATE_END			0

static struct ofw_compat_data compat_data[] = {
	{ "ti,gate-clock",			TI_GATE_CLOCK },
	{ "ti,wait-gate-clock",			TI_WAIT_GATE_CLOCK },
	{ "ti,dss-gate-clock",			TI_DSS_GATE_CLOCK },
	{ "ti,am35xx-gate-clock",		TI_AM35XX_GATE_CLOCK },
	/* For now, dont support clkdm-gate-clock */
	/* { "ti,clkdm-gate-clock",		TI_CLKDM_GATE_CLOCK }, */
	{ "ti,hsdiv-gate-cloc",			TI_HSDIV_GATE_CLOCK },
	{ "ti,composite-no-wait-gate-clock", TI_COMPOSITE_NO_WAIT_GATE_CLOCK },
	{ NULL,					TI_GATE_END }
};

static int
ti_gate_clkdev_write_4(device_t dev, bus_addr_t addr, uint32_t val)
{
	struct ti_gate_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "gate_clkdev_write_4: addr %x val %x\n",
	    addr, val);
	return (SYSCON_UNLOCKED_WRITE_4(sc->syscon, addr, val));
}

static int
ti_gate_clkdev_read_4(device_t dev, bus_addr_t addr, uint32_t *val)
{
	struct ti_gate_softc *sc;

	sc = device_get_softc(dev);

	*val = SYSCON_UNLOCKED_READ_4(sc->syscon, addr);
	DPRINTF(sc->dev, "gate_clkdev_write_4: addr %x val %x\n",
	     addr, *val);
	return (0);
}

static int
ti_gate_clkdev_modify_4(device_t dev, bus_addr_t addr,
    uint32_t clear_mask, uint32_t set_mask)
{
	struct ti_gate_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "clkdev_modify_4: addr %x clear_mask %x set_mask %x\n",
	     addr, clear_mask, set_mask);
	return (SYSCON_UNLOCKED_MODIFY_4(sc->syscon, addr, clear_mask,
	    set_mask));
}

static void
ti_gate_clkdev_device_lock(device_t dev)
{
	struct ti_gate_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "ti_gate_clkdev_device_lock\n");
	SYSCON_DEVICE_LOCK(sc->syscon->pdev);
}

static void
ti_gate_clkdev_device_unlock(device_t dev)
{
	struct ti_gate_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "ti_gate_clkdev_device_unlock\n");
	SYSCON_DEVICE_UNLOCK(sc->syscon->pdev);
}

static int
ti_gate_probe(device_t dev)
{
	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data == 0)
		return (ENXIO);

	device_set_desc(dev, "TI Gate Clock");
	if (bootverbose == 0)
		device_quiet(dev);

	return (BUS_PROBE_DEFAULT);
}

static int
ti_gate_attach(device_t dev)
{
	struct ti_gate_softc *sc;
	phandle_t	node;
	int		err, index;
	cell_t 		value;
	const char	*node_name;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	/* Get syscon */
	err = SYSCON_GET_HANDLE(dev, &sc->syscon);
	if (err != 0) {
		panic("Cannot get syscon handle.\n");
	}

	clk_parse_ofw_clk_name(dev, node, &node_name);
	if (node_name == NULL) {
		panic("Cannot get name of the clock node");
	}

	/* Get the compatible type */
	sc->sc_type = ofw_bus_search_compatible(dev, compat_data)->ocd_data;

	/* Get the content of reg properties */
	if (OF_hasprop(node, "reg") == 1) {
		OF_getencprop(node, "reg", &value, sizeof(value));
		sc->gate_def.offset = value;
	} else {
		/* assume parent is clksel... */
		sc->gate_def.offset = ti_clksel_get_reg(device_get_parent(dev));
	}

	if (OF_hasprop(node, "ti,bit-shift")) {
		OF_getencprop(node, "ti,bit-shift", &value, sizeof(value));
		sc->gate_def.shift = value;
		DPRINTF(sc->dev, "ti,bit-shift => shift %x\n",
		    sc->gate_def.shift);
	}
	if (OF_hasprop(node, "ti,set-bit-to-disable")) {
		sc->gate_def.on_value = 0;
		sc->gate_def.off_value = 1;
		DPRINTF(sc->dev,
			"ti,set-bit-to-disable (on = 0, off = 1)\n");
	} else {
		sc->gate_def.on_value = 1;
		sc->gate_def.off_value = 0;
		DPRINTF(sc->dev,
			"!ti,set-bit-to-disable (on = 1, off = 0)\n");
	}

	sc->gate_def.gate_flags = 0x0;


	/* Find parent in lookup table */
	for (index = 0; index < nitems(gate_parent_table); index++) {
		if (strcmp(node_name, gate_parent_table[index].node_name) == 0)
			break;
	}

	if (index == nitems(gate_parent_table))
		panic("Cant find clock %s\n", node_name);

	DPRINTF(dev, "%s at gate_parent_table[%d]\n",
		node_name, index);

	/* Fill clknode_init_def */
	sc->gate_def.clkdef.id = 1;
	sc->gate_def.clkdef.flags = CLK_NODE_STATIC_STRINGS;
	sc->gate_def.clkdef.name = gate_parent_table[index].node_name;
	sc->gate_def.clkdef.parent_cnt = gate_parent_table[index].parent_cnt;
	sc->gate_def.clkdef.parent_names =gate_parent_table[index].parent_names;

	/* Calculate mask */
	sc->gate_def.mask = (1 << fls(sc->gate_def.clkdef.parent_cnt)) - 1;
	DPRINTF(sc->dev, "num_real_clocks %x gate_def.mask %x\n",
		sc->gate_def.clkdef.parent_cnt,
		sc->gate_def.mask);

	sc->clkdom = clkdom_create(sc->dev);
	if (sc->clkdom == NULL) {
		DPRINTF(sc->dev, "Failed to create clkdom\n");
		return ENXIO;
	}

	err = clknode_gate_register(sc->clkdom, &sc->gate_def);
	if (err != 0) {
		DPRINTF(sc->dev, "clknode_gate_register failed %x\n", err);
		return ENXIO;
	}

	err = clkdom_finit(sc->clkdom);
	if (err != 0) {
		DPRINTF(sc->dev, "Clk domain finit fails %x.\n", err);
		return ENXIO;
	}

	return (bus_generic_attach(sc->dev));
}

static int
ti_gate_detach(device_t dev)
{
	return (EBUSY);
}

static device_method_t ti_gate_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe,		ti_gate_probe),
	DEVMETHOD(device_attach,	ti_gate_attach),
	DEVMETHOD(device_detach,	ti_gate_detach),

	/* Clock device interface */
	DEVMETHOD(clkdev_device_lock,	ti_gate_clkdev_device_lock),
	DEVMETHOD(clkdev_device_unlock,	ti_gate_clkdev_device_unlock),
	DEVMETHOD(clkdev_read_4,	ti_gate_clkdev_read_4),
	DEVMETHOD(clkdev_write_4,	ti_gate_clkdev_write_4),
	DEVMETHOD(clkdev_modify_4,	ti_gate_clkdev_modify_4),

	DEVMETHOD_END
};

DEFINE_CLASS_0(ti_gate, ti_gate_driver, ti_gate_methods,
	sizeof(struct ti_gate_softc));

EARLY_DRIVER_MODULE(ti_gate, simplebus, ti_gate_driver, 0, 0,
    BUS_PASS_BUS + BUS_PASS_ORDER_MIDDLE);
MODULE_VERSION(ti_gate, 1);
