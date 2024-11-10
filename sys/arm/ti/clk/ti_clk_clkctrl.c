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
#include <sys/systm.h>
#include <sys/bus.h>
#include <sys/malloc.h>

#include <dev/extres/clk/clk.h>

#include <arm/ti/clk/ti_clk_clkctrl.h>
#include <arm/ti/clk/ti_clock_common.h>

#include "clkdev_if.h"

#if 0
#define DPRINTF(dev, msg...) device_printf(dev, msg)
#else
#define DPRINTF(dev, msg...)
#endif

/*
 * clknode for clkctrl, implements gate and mux (for gpioc)
 */

#define IDLEST_MASK		0x00030000
#define MODULEMODE_MASK		0x00000003

#define IDLEST_FUNC		0x00000000
#define IDLEST_TRANS		0x00010000
#define IDLEST_IDLE		0x00020000
#define IDLEST_DISABLE		0x00030000

#define MODULEMODE_DISABLE	0x0
#define MODULEMODE_ENABLE_HW	0x1
#define MODULEMODE_ENABLE_SW	0x2

struct ti_clkctrl_clknode_sc {
	device_t	dev;
	/* omap4-cm range.host + ti,clkctrl reg[0] */
	uint32_t	register_offset;
	uint8_t		flags;
};

#define	WRITE4(_clk, off, val)						\
	CLKDEV_WRITE_4(clknode_get_device(_clk), off, val)
#define	READ4(_clk, off, val)						\
	CLKDEV_READ_4(clknode_get_device(_clk), off, val)
#define	DEVICE_LOCK(_clk)						\
	CLKDEV_DEVICE_LOCK(clknode_get_device(_clk))
#define	DEVICE_UNLOCK(_clk)						\
	CLKDEV_DEVICE_UNLOCK(clknode_get_device(_clk))

static int
ti_clkctrl_init(struct clknode *clk, device_t dev)
{
	struct ti_clkctrl_clknode_sc *sc;

	sc = clknode_get_softc(clk);
	sc->dev = dev;

	clknode_init_parent_idx(clk, 0);
	return (0);
}

static int
ti_clkctrl_set_gate(struct clknode *clk, bool enable)
{
	struct ti_clkctrl_clknode_sc *sc;
	uint32_t	val, idlest, modulemode_reg, modulemode_val=0;
	uint32_t timeout=100;

	sc = clknode_get_softc(clk);

	DEVICE_LOCK(clk);
	READ4(clk, sc->register_offset, &val);

	if (enable == false)
		WRITE4(clk, sc->register_offset, MODULEMODE_DISABLE);
	/* enable == true for following two */
	else if ((sc->flags & TI_CLKCTRL_FLAGS_MM_HW) == TI_CLKCTRL_FLAGS_MM_HW) {
		modulemode_val = MODULEMODE_ENABLE_HW;
		WRITE4(clk, sc->register_offset, MODULEMODE_ENABLE_HW);
	} else {
		modulemode_val = MODULEMODE_ENABLE_SW;
		WRITE4(clk, sc->register_offset, MODULEMODE_ENABLE_SW);
	}

	while (timeout) {
		READ4(clk, sc->register_offset, &val);
		idlest = val & IDLEST_MASK;
		modulemode_reg = val & MODULEMODE_MASK;
		if (enable == true &&
		    (idlest == IDLEST_FUNC || idlest == IDLEST_IDLE) &&
		    modulemode_reg == modulemode_val)
			break;
		else if (enable == false &&
		    idlest == IDLEST_DISABLE &&
		    modulemode_reg == MODULEMODE_DISABLE)
			break;
		DELAY(10);
		timeout--;
	}

	DEVICE_UNLOCK(clk);
	if (timeout == 0) {
		DPRINTF(sc->dev, "ti_clkctrl_set_gate: Timeout\n");
		return (1);
	}

	return (0);
}

static clknode_method_t ti_clkctrl_clknode_methods[] = {
	/* Device interface */
	CLKNODEMETHOD(clknode_init,	ti_clkctrl_init),
	CLKNODEMETHOD(clknode_set_gate, ti_clkctrl_set_gate),
	CLKNODEMETHOD_END
};

DEFINE_CLASS_1(ti_clkctrl_clknode, ti_clkctrl_clknode_class,
    ti_clkctrl_clknode_methods, sizeof(struct ti_clkctrl_clknode_sc),
    clknode_class);

int
ti_clknode_clkctrl_register(struct clkdom *clkdom,
    struct ti_clk_clkctrl_def *clkdef)
{
	struct clknode *clk;
	struct ti_clkctrl_clknode_sc *sc;

	clk = clknode_create(clkdom, &ti_clkctrl_clknode_class,
	    &clkdef->clkdef);

	if (clk == NULL) {
		DPRINTF(sc->dev, "clknode_create failed.\n");
		return (1);
	}

	sc = clknode_get_softc(clk);
	sc->register_offset = clkdef->register_offset;
	sc->flags = clkdef->flags;

	if (clknode_register(clkdom, clk) == NULL) {
		DPRINTF(sc->dev, "clknode_register failed.\n");
		return (2);
	}
	return (0);
}
