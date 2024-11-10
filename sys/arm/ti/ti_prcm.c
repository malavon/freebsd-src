/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2012 Damjan Marion <dmarion@Freebsd.org>
 * All rights reserved.
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

/* Based on sys/arm/ti/am335x/am335x_prcm.c */

#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/bus.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/mutex.h>
#include <sys/rman.h>
#include <machine/bus.h>

#include <arm/ti/ti_cpuid.h>
#include <arm/ti/ti_prcm.h>
#include <arm/ti/tivar.h>

#include <dev/fdt/simplebus.h>

#include <dev/ofw/openfirm.h>
#include <dev/ofw/ofw_bus.h>
#include <dev/ofw/ofw_bus_subr.h>

#include <dev/extres/clk/clk.h>
#include <dev/extres/syscon/syscon.h>
#include <dev/extres/syscon/syscon_generic.h>

#include "syscon_if.h"
#include "clkdev_if.h"

#if 0
#define DPRINTF(dev, msg...) device_printf(dev, msg)
#else
#define DPRINTF(dev, msg...)
#endif

static device_t ti_prcm_dev;
static void omap4_prcm_reset(void);
static void am335x_prcm_reset(void);

#define TI_AM3_PRCM		18
#define TI_AM4_PRCM		17
#define TI_OMAP2_PRCM		16
#define TI_OMAP3_PRM		15
#define TI_OMAP3_CM		14
#define TI_OMAP4_CM1		13
#define TI_OMAP4_PRM		12
#define TI_OMAP4_CM2		11
#define TI_OMAP4_SCRM		10
#define TI_OMAP5_PRM		9
#define TI_OMAP5_CM_CORE_AON	8
#define TI_OMAP5_SCRM		7
#define TI_OMAP5_CM_CORE	6
#define TI_DRA7_PRM		5
#define TI_DRA7_CM_CORE_AON	4
#define TI_DRA7_CM_CORE		3
#define TI_DM814_PRCM		2
#define TI_DM816_PRCM		1
#define TI_PRCM_END		0

static struct ofw_compat_data compat_data[] = {
	{ "ti,am3-prcm",	TI_AM3_PRCM },
	{ "ti,am4-prcm",	TI_AM4_PRCM },
	{ "ti,omap2-prcm",	TI_OMAP2_PRCM },
	{ "ti,omap3-prm",	TI_OMAP3_PRM },
	{ "ti,omap3-cm",	TI_OMAP3_CM },
	{ "ti,omap4-cm1",	TI_OMAP4_CM1 },
	{ "ti,omap4-prm",	TI_OMAP4_PRM },
	{ "ti,omap4-cm2",	TI_OMAP4_CM2 },
	{ "ti,omap4-scrm",	TI_OMAP4_SCRM },
	{ "ti,omap5-prm",	TI_OMAP5_PRM },
	{ "ti,omap5-cm-core-aon", TI_OMAP5_CM_CORE_AON },
	{ "ti,omap5-scrm",	TI_OMAP5_SCRM },
	{ "ti,omap5-cm-core",	TI_OMAP5_CM_CORE },
	{ "ti,dra7-prm",	TI_DRA7_PRM },
	{ "ti,dra7-cm-core-aon", TI_DRA7_CM_CORE_AON },
	{ "ti,dra7-cm-core",	TI_DRA7_CM_CORE },
	{ "ti,dm814-prcm",	TI_DM814_PRCM },
	{ "ti,dm816-prcm",	TI_DM816_PRCM },
	{ NULL,			TI_PRCM_END}
};

static int
ti_prcm_probe(device_t dev)
{
	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data == 0)
		return (ENXIO);

	device_set_desc(dev, "TI Power and Clock Management");
	if (bootverbose == 0)
		device_quiet(dev);

	/* Setup reset handler */
	ti_prcm_dev = dev;

	switch(ti_chip()) {
#ifdef SOC_OMAP4
	case CHIP_OMAP_4:
		ti_cpu_reset = omap4_prcm_reset;
		break;
#endif
#ifdef SOC_TI_AM335X
	case CHIP_AM335X:
		ti_cpu_reset = am335x_prcm_reset;
		break;
#endif
	}

	return (BUS_PROBE_DEFAULT);
}

int
ti_prcm_write_4(device_t dev, bus_addr_t addr, uint32_t val)
{
	struct syscon_generic_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "ti_prcm_write_4: offset=%lx write %x\n", addr, val);
	return (SYSCON_UNLOCKED_WRITE_4(sc->syscon, addr, val));
}

int
ti_prcm_read_4(device_t dev, bus_addr_t addr, uint32_t *val)
{
	struct syscon_generic_softc *sc;

	sc = device_get_softc(dev);
	*val = SYSCON_UNLOCKED_READ_4(sc->syscon, addr);
	DPRINTF(sc->dev, "offset=%lx Read %x\n", addr, *val);
	return (0);
}

int
ti_prcm_modify_4(device_t dev, bus_addr_t addr, uint32_t clr, uint32_t set)
{
	struct syscon_generic_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "ti_prcm_modify_4: addr %x clear_mask %x set_mask %x\n",
		 addr, clr, set);
	return (SYSCON_UNLOCKED_MODIFY_4(sc->syscon, addr, clr,
		set));
}

void
ti_prcm_device_lock(device_t dev)
{
	struct syscon_generic_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "ti_prcm_device_lock\n");
	SYSCON_DEVICE_LOCK(sc->syscon->pdev);
}

void
ti_prcm_device_unlock(device_t dev)
{
	struct syscon_generic_softc *sc;

	sc = device_get_softc(dev);
	DPRINTF(sc->dev, "ti_prcm_device_unlock\n");
	SYSCON_DEVICE_UNLOCK(sc->syscon->pdev);
}

static int
ti_prcm_get_handle(device_t dev, struct syscon **syscon)
{
	struct syscon_generic_softc *sc;

	sc = device_get_softc(dev);
	*syscon = sc->syscon;
	if (*syscon == NULL)
		return (ENODEV);
	return (0);
}

static device_method_t ti_prcm_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe,		ti_prcm_probe),

	/* Syscon */
	DEVMETHOD(syscon_get_handle, ti_prcm_get_handle),

	/* clkdev interface */
	DEVMETHOD(clkdev_write_4,	ti_prcm_write_4),
	DEVMETHOD(clkdev_read_4,	ti_prcm_read_4),
	DEVMETHOD(clkdev_modify_4,	ti_prcm_modify_4),
	DEVMETHOD(clkdev_device_lock,	ti_prcm_device_lock),
	DEVMETHOD(clkdev_device_unlock, ti_prcm_device_unlock),

	DEVMETHOD_END
};

DEFINE_CLASS_1(ti_prcm, ti_prcm_driver, ti_prcm_methods,
	sizeof(struct syscon_generic_softc), syscon_generic_driver);

EARLY_DRIVER_MODULE(ti_prcm, simplebus, ti_prcm_driver, 0, 0,
    BUS_PASS_BUS + BUS_PASS_ORDER_MIDDLE);

MODULE_VERSION(ti_prcm, 1);
MODULE_DEPEND(ti_prcm, syscon_generic_dev, 1, 1, 1);

/* From sys/arm/ti/am335x/am335x_prcm.c
 * Copyright (c) 2012 Damjan Marion <dmarion@Freebsd.org>
 */
#define PRM_DEVICE_OFFSET		0xF00
#define AM335x_PRM_RSTCTRL		(PRM_DEVICE_OFFSET + 0x00)

static void
am335x_prcm_reset(void)
{
	ti_prcm_device_lock(ti_prcm_dev);
	ti_prcm_write_4(ti_prcm_dev, AM335x_PRM_RSTCTRL, (1<<1));
	ti_prcm_device_unlock(ti_prcm_dev);
}

/* FIXME: Is this correct - or should the license part be ontop? */

/* From sys/arm/ti/omap4/omap4_prcm_clks.c */
/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2011
 *      Ben Gray <ben.r.gray@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the company nor the name of the author may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BEN GRAY ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL BEN GRAY BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#define PRM_RSTCTRL		0x1b00
#define PRM_RSTCTRL_RESET	0x2

static void
omap4_prcm_reset(void)
{
	uint32_t reg;

	ti_prcm_device_lock(ti_prcm_dev);
	ti_prcm_read_4(ti_prcm_dev, PRM_RSTCTRL, &reg);
	reg = reg | PRM_RSTCTRL_RESET;
	ti_prcm_write_4(ti_prcm_dev, PRM_RSTCTRL, reg);
	ti_prcm_read_4(ti_prcm_dev, PRM_RSTCTRL, &reg);
	ti_prcm_device_unlock(ti_prcm_dev);
}
