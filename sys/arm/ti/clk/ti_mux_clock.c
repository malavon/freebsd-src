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
#include <sys/types.h>
#include <sys/malloc.h>

#include <machine/bus.h>
#include <dev/fdt/simplebus.h>

#include <dev/extres/clk/clk_mux.h>
#include <dev/extres/syscon/syscon.h>

#include <dev/ofw/ofw_bus.h>
#include <dev/ofw/ofw_bus_subr.h>

#include <arm/ti/clk/am33xx.h>
#include <arm/ti/clk/ti_clock_common.h>
#include <arm/ti/clk/ti_clksel.h>
#include "clkdev_if.h"
#include "syscon_if.h"

#if 0
#define DPRINTF(dev, msg...) device_printf(dev, msg)
#else
#define DPRINTF(dev, msg...)
#endif

struct ti_mux_softc {
	device_t		dev;

	struct clk_mux_def	mux_def;
	struct clkdom 		*clkdom;
	struct syscon		*syscon;
};

static int ti_mux_probe(device_t dev);
static int ti_mux_attach(device_t dev);
static int ti_mux_detach(device_t dev);

#define TI_MUX_CLOCK			2
#define TI_COMPOSITE_MUX_CLOCK		1
#define TI_MUX_END			0

static struct ofw_compat_data compat_data[] = {
	{ "ti,mux-clock",		TI_MUX_CLOCK },
	{ "ti,composite-mux-clock",	TI_COMPOSITE_MUX_CLOCK },
	{ NULL,				TI_MUX_END }
};

static int
ti_mux_clkdev_write_4(device_t dev, bus_addr_t addr, uint32_t val)
{
	struct ti_mux_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "mux_clkdev_write_4: addr %x val %x\n",
	     addr, val);
	return (SYSCON_UNLOCKED_WRITE_4(sc->syscon, addr, val));
}

static int
ti_mux_clkdev_read_4(device_t dev, bus_addr_t addr, uint32_t *val)
{
	struct ti_mux_softc *sc;
	uint32_t rdval;

	sc = device_get_softc(dev);

	rdval = SYSCON_UNLOCKED_READ_4(sc->syscon, addr);
	*val = rdval;
	DPRINTF(sc->dev, "clkdev_read_4: addr %x val %x\n",
	    addr, *val);
	return (0);
}

static int
ti_mux_clkdev_modify_4(device_t dev, bus_addr_t addr,
    uint32_t clear_mask, uint32_t set_mask)
{
	struct ti_mux_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "clkdev_modify_4: addr %x clear %x mask %x\n",
	    addr, clear_mask, set_mask);
	return (SYSCON_UNLOCKED_MODIFY_4(sc->syscon, addr, clear_mask,
	    set_mask));
}

static void
ti_mux_clkdev_device_lock(device_t dev)
{
	struct ti_mux_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "ti_mux_clkdev_device_lock\n");
	SYSCON_DEVICE_LOCK(sc->syscon->pdev);
}

static void
ti_mux_clkdev_device_unlock(device_t dev)
{
	struct ti_mux_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "ti_mux_clkdev_device_unlock\n");
	SYSCON_DEVICE_UNLOCK(sc->syscon->pdev);
}

static int
ti_mux_probe(device_t dev)
{
	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data == 0)
		return (ENXIO);

	device_set_desc(dev, "TI Mux Clock");
	if (bootverbose == 0)
		device_quiet(dev);

	return (BUS_PROBE_DEFAULT);
}

static int
ti_mux_attach(device_t dev)
{
	struct ti_mux_softc *sc;
	phandle_t	node;
	int		err, index;
	cell_t		value;
	const char 	*node_name;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	err = SYSCON_GET_HANDLE(device_get_parent(dev), &sc->syscon);
	if (err != 0) {
		panic("Cannot get syscon handle.\n");
	}

	clk_parse_ofw_clk_name(dev, node, &node_name);
	if (node_name == NULL) {
		panic("Cannot get name of the clock node");
	}

	/* Grab the content of reg properties */
	if (OF_hasprop(node, "reg") == 1) {
		OF_getencprop(node, "reg", &value, sizeof(value));
		sc->mux_def.offset = value;
	} else {
		/* assume parent is clksel... */
		sc->mux_def.offset = ti_clksel_get_reg(device_get_parent(dev));
	}

	if (OF_hasprop(node, "ti,bit-shift")) {
		OF_getencprop(node, "ti,bit-shift", &value, sizeof(value));
		sc->mux_def.shift = value;
		DPRINTF(sc->dev, "ti,bit-shift => shift %x\n",
		    sc->mux_def.shift);
	}
	if (OF_hasprop(node, "ti,index-starts-at-one")) {
		/* FIXME: Add support in dev/extres/clk */
		/*sc->mux_def.mux_flags =  ... */
		DPRINTF(sc->dev,
		    "ti,index-starts-at-one - Not implemented\n");
	}

	if (OF_hasprop(node, "ti,set-rate-parent"))
		DPRINTF(sc->dev,
		    "ti,set-rate-parent - Not implemented\n");
	if (OF_hasprop(node, "ti,latch-bit"))
		DPRINTF(sc->dev,
		    "ti,latch-bit - Not implemented\n");


	/* Find parent in lookup table */
	for (index = 0; index < nitems(mux_parent_table); index++) {
		if (strcmp(node_name, mux_parent_table[index].node_name) == 0)
			break;
	}
	if (index == nitems(mux_parent_table))
		panic("Cant find clock %s\n", node_name);

	DPRINTF(sc->dev, "%s at mux_parent_table[%d]\n",
			node_name, index);
	/* Fill clknode_init_def */
	sc->mux_def.clkdef.id = 1;
	sc->mux_def.clkdef.flags = CLK_NODE_STATIC_STRINGS;

	sc->mux_def.clkdef.name = mux_parent_table[index].node_name;
	sc->mux_def.clkdef.parent_cnt = mux_parent_table[index].parent_cnt;
	sc->mux_def.clkdef.parent_names = mux_parent_table[index].parent_names;

	/* Figure out the width from ti_max_div */
	if (sc->mux_def.mux_flags)
		sc->mux_def.width = fls(sc->mux_def.clkdef.parent_cnt-1);
	else
		sc->mux_def.width = fls(sc->mux_def.clkdef.parent_cnt);

	DPRINTF(sc->dev, "parents %x def.width %x\n",
		sc->mux_def.clkdef.parent_cnt, sc->mux_def.width);

	sc->clkdom = clkdom_create(sc->dev);
	if (sc->clkdom == NULL) {
		DPRINTF(sc->dev, "Failed to create clkdom\n");
		return ENXIO;
	}

	err = clknode_mux_register(sc->clkdom, &sc->mux_def);
	if (err != 0) {
		DPRINTF(sc->dev, "clknode_mux_register failed %x\n", err);
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
ti_mux_detach(device_t dev)
{
	return (EBUSY);
}

static device_method_t ti_mux_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe,		ti_mux_probe),
	DEVMETHOD(device_attach,	ti_mux_attach),
	DEVMETHOD(device_detach,	ti_mux_detach),

	/* Clock device interface */
	DEVMETHOD(clkdev_device_lock,	ti_mux_clkdev_device_lock),
	DEVMETHOD(clkdev_device_unlock,	ti_mux_clkdev_device_unlock),
	DEVMETHOD(clkdev_read_4,	ti_mux_clkdev_read_4),
	DEVMETHOD(clkdev_write_4,	ti_mux_clkdev_write_4),
	DEVMETHOD(clkdev_modify_4,	ti_mux_clkdev_modify_4),

	DEVMETHOD_END
};

DEFINE_CLASS_0(ti_mux, ti_mux_driver, ti_mux_methods,
	sizeof(struct ti_mux_softc));

EARLY_DRIVER_MODULE(ti_mux, simplebus, ti_mux_driver, 0, 0,
    BUS_PASS_BUS + BUS_PASS_ORDER_MIDDLE);
MODULE_VERSION(ti_mux, 1);
