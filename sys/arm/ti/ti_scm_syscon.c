/*-
 * Copyright (c) 2019 Emmanuel Vadot <manu@FreeBSD.org>
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
/* Based on sys/arm/ti/ti_sysc.c */

#include <sys/param.h>
#include <sys/bus.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/mutex.h>
#include <sys/rman.h>

#include <dev/ofw/openfirm.h>
#include <dev/ofw/ofw_bus.h>
#include <dev/ofw/ofw_bus_subr.h>

#include <dev/extres/syscon/syscon.h>
#include <dev/extres/syscon/syscon_generic.h>
#include <arm/ti/ti_cpuid.h>

#include "syscon_if.h"

#if 0
#define DPRINTF(dev, msg...) device_printf(dev, msg)
#else
#define DPRINTF(dev, msg...)
#endif

/* device interface */
static int
ti_scm_syscon_probe(device_t dev)
{
	const char *name;
	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (!ti_soc_is_supported())
		return (ENXIO);

	/* Need to be both "syscon" and "simple-bus" */
	if (ofw_bus_is_compatible(dev, "syscon") == 0 ||
		ofw_bus_is_compatible(dev, "simple-bus") == 0)
		return (ENXIO);

	/* Require the node are named scm_conf@0 */
	name = ofw_bus_get_name(dev);
	if (name == NULL || strcmp(name, "scm_conf@0") != 0)
		return (ENXIO);

	device_set_desc(dev, "TI OMAP Control Module Syscon");

	if (bootverbose == 0)
		device_quiet(dev);

	return(BUS_PROBE_DEFAULT);
}

static int
ti_scm_syscon_get_handle(device_t dev, struct syscon **syscon)
{
	struct syscon_generic_softc *sc;

	sc = device_get_softc(dev);
	*syscon = sc->syscon;
	if (*syscon == NULL)
		return (ENODEV);
	return (0);
}

static device_method_t ti_scm_syscon_methods[] = {
	DEVMETHOD(device_probe,		ti_scm_syscon_probe),
	DEVMETHOD(syscon_get_handle,	ti_scm_syscon_get_handle),

	DEVMETHOD_END
};

DEFINE_CLASS_1(ti_scm_syscon, ti_scm_syscon_driver, ti_scm_syscon_methods,
    sizeof(struct syscon_generic_softc), syscon_generic_driver);

/* ti_scm_syscon needs to attach "as soon as posible" due to it has clocks */
EARLY_DRIVER_MODULE(ti_scm_syscon, simplebus, ti_scm_syscon_driver, 0, 0,
    BUS_PASS_BUS + BUS_PASS_ORDER_MIDDLE);
MODULE_VERSION(ti_scm_syscon, 1);
MODULE_DEPEND(ti_scm_syscon, ti_scm, 1, 1, 1);
