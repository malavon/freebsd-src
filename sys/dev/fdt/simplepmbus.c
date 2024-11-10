/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2023 Oskar Holmlund <oskar.holmlund@ohdata.se>
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
/*
 * Bindings
 * sys/contrib/device-tree/Bindings/bus/simple-pm-bus.yaml
 */

#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/module.h>
#include <sys/bus.h>
#include <sys/conf.h>
#include <sys/kernel.h>
#include <sys/rman.h>

#include <dev/extres/clk/clk.h>

#include <dev/ofw/openfirm.h>
#include <dev/ofw/ofw_bus.h>
#include <dev/ofw/ofw_bus_subr.h>

#include <dev/fdt/simplebus.h>

static int
simple_pm_bus_probe(device_t dev)
{
	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	/*
	 * for now: require "ranges"
	 * later require "clock" or "power-domains" aswell.
	 */
	if (!(ofw_bus_is_compatible(dev, "simple-pm-bus") &&
	    ofw_bus_has_prop(dev, "ranges")))
	{
		return (ENXIO);
	}

	device_set_desc(dev, "Simple Power-Managed Bus");

	if (bootverbose == 0)
		device_quiet(dev);

	return (BUS_PROBE_GENERIC);
}

static device_method_t simple_pm_bus_methods[] = {
	DEVMETHOD(device_probe, simple_pm_bus_probe),
	DEVMETHOD(device_attach, simplebus_attach),
	DEVMETHOD(device_detach, simplebus_detach),
	DEVMETHOD_END
};

DEFINE_CLASS_1(simple_pm_bus, simple_pm_bus_driver, simple_pm_bus_methods,
    sizeof(struct simplebus_softc), simplebus_driver);

EARLY_DRIVER_MODULE(simple_pm_bus, simplebus, simple_pm_bus_driver, 0, 0,
    BUS_PASS_BUS + BUS_PASS_ORDER_MIDDLE);

MODULE_VERSION(simple_pm_bus, 1);
