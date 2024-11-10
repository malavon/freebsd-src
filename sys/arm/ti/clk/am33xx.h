/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2024 Oskar Holmlund <oskar.holmlund@ohdata.se>
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

#ifndef __AM33XX_H__
#define __AM33XX_H__

#include <arm/ti/clk/ti_clock_common.h>
#include <dev/extres/clk/clk_link.h>
#include <dt-bindings/clock/am3.h>

/* === ti_sysc.c === */
PLIST(target_module_7000) = {
	"l4-wkup-clkctrl@0_8",
	"l4-wkup-clkctrl@0_9"
}; /* gpio0 */
PLIST(target_module_9000) = { "l4-wkup-clkctrl@0_b4" }; /* uart0 */
PLIST(target_module_b000) = { "l4-wkup-clkctrl@0_b8" }; /* i2c1 */
PLIST(target_module_d000) = { "l4-wkup-clkctrl@0_bc" }; /* adc_tsc */
PLIST(target_module_31000) = { "l4-wkup-clkctrl@0_c4" }; /* timer1 */
PLIST(target_module_35000) = { "l4-wkup-clkctrl@0_d4" }; /* timer2 */

PLIST(target_module_3e000) = { "l4-rtc-clkctrl@0_0" }; /* rtc */

PLIST(target_module_100000) = {
	"cpsw-125mhz-clkctrl@0_14"
}; /* cpsw (ethernet) */

PLIST(target_module_300000) = { "pruss-ocp-clkctrl@e8_0" }; /* pru */

PLIST(target_module_22000) = { "l4ls-clkctrl@38_34" }; /* uart2 */
PLIST(target_module_24000) = { "l4ls-clkctrl@38_38" }; /* uart3 */
PLIST(target_module_2a000) = { "l4ls-clkctrl@38_10" }; /* i2c2 */
PLIST(target_module_30000) = { "l4ls-clkctrl@38_14" }; /* spi0 */

PLIST(target_module_40000) = { "l4ls-clkctrl@38_48" }; /* timer2 */
PLIST(target_module_42000) = { "l4ls-clkctrl@38_4c" }; /* timer3 */
PLIST(target_module_44000) = { "l4ls-clkctrl@38_50" }; /* timer4 */
PLIST(target_module_46000) = { "l4ls-clkctrl@38_b4" }; /* timer5 */
PLIST(target_module_48000) = { "l4ls-clkctrl@38_b8" }; /* timer6 */
PLIST(target_module_4a000) = { "l4ls-clkctrl@38_44" }; /* timer7 */
PLIST(target_module_4c000) = {
	"l4ls-clkctrl@38_74",
	"l4ls-clkctrl@38_75"
}; /* gpio2 */
PLIST(target_module_60000) = { "l4ls-clkctrl@38_4" }; /* mmc1 */
PLIST(target_module_80000) = { "l4ls-clkctrl@38_8" }; /* elm */
PLIST(target_module_c8000) = { "l4ls-clkctrl@38_d8" }; /* mailbox */
PLIST(target_module_ca000) = { "l4ls-clkctrl@38_d4" }; /* spinlock */
PLIST(target_module_9c000) = { "l4ls-clkctrl@38_c" }; /* i2c3 */
PLIST(target_module_a0000) = { "l4ls-clkctrl@38_18" }; /* spi1 */
PLIST(target_module_a6000) = { "l4ls-clkctrl@38_3c" }; /* uart4 */
PLIST(target_module_a8000) = { "l4ls-clkctrl@38_40" }; /* uart5 */
PLIST(target_module_aa000) = { "l4ls-clkctrl@38_0" }; /* uart6 */
PLIST(target_module_ac000) = {
	"l4ls-clkctrl@38_78",
	"l4ls-clkctrl@38_79"
}; /* gpio3 */
PLIST(target_module_ae000) = {
	"l4ls-clkctrl@38_7c",
	"l4ls-clkctrl@38_7d"
}; /* gpio4 */
PLIST(target_module_cc000) = { "l4ls-clkctrl@38_88" }; /* dcan0 */
PLIST(target_module_d0000) = { "l4ls-clkctrl@38_8c" }; /* dcan1 */
PLIST(target_module_d8000) = { "l4ls-clkctrl@38_bc" }; /* mmc2 */
PLIST(target_module_0) = { "l4ls-clkctrl@38_9c" }; /* epwmss0 */
PLIST(target_module_2000) = { "l4ls-clkctrl@38_94" }; /* epwmss1 */
PLIST(target_module_4000) = { "l4ls-clkctrl@38_a0" }; /* epwmss2 */

PLIST(target_module_e000) = { "lcdc-clkctrl@18_0" }; /* lcdc */

PLIST(target_module_10000) = { "l4ls-clkctrl@38_58" }; /* rng */

PLIST(target_module_49800000) = { "l3-clkctrl@24_0" }; /* tptco */
PLIST(target_module_4c000000) = { "l3-clkctrl@24_4" }; /* emif */
PLIST(target_module_40300000) = { "l3-clkctrl@24_8" }; /* ocmcram */
PLIST(target_module_53500000) = { "l3-clkctrl@24_70" }; /* aes */
PLIST(target_module_53100000) = { "l3-clkctrl@24_7c" }; /* sham */

PLIST(target_module_49000000) = { "l3-clkctrl@24_98" }; /* tpcc */
PLIST(target_module_4b000000) = { "l3-clkctrl@24_b8" }; /* l3 instr */
PLIST(target_module_49900000) = { "l3-clkctrl@24_d8" }; /* tptc1 */
PLIST(target_module_49a00000) = { "l3-clkctrl@24_dc" }; /* tptc2 */

PLIST(target_module_47400000) = { "l3s-clkctrl@1c_0" }; /* usb otg hs */
PLIST(target_module_50000000) = { "l3s-clkctrl@1c_14" }; /* gpmc */
PLIST(target_module_38000) = { "l3s-clkctrl@1c_18" }; /* mcasp0 */
PLIST(target_module_3c000) = { "l3s-clkctrl@1c_4c" }; /* mcasp1 */
PLIST(target_module_47810000) = { "l3s-clkctrl@1c_dc" }; /* mmc3 */
PLIST(target_module_140000) = { "l3-aon-clkctrl@14_0" }; /* l3 debugss */
PLIST(target_module_56000000) = { "gfx-l3-clkctrl@0_4" }; /* gfx */


static struct parent_lookup_table sysc_clock_table[] = {
{
	"target-module@7000",
	nitems(target_module_7000),
	target_module_7000
},
{
	"target-module@9000",
	nitems(target_module_9000),
	target_module_9000
},
{
	"target-module@b000",
	nitems(target_module_b000),
	target_module_b000
},
{
	"target-module@d000",
	nitems(target_module_d000),
	target_module_d000
},
{
	"target-module@31000",
	nitems(target_module_31000),
	target_module_31000
},
{
	"target-module@35000",
	nitems(target_module_35000),
	target_module_35000
},

{
	"target-module@3e000",
	nitems(target_module_3e000),
	target_module_3e000
},

{
	"target-module@100000",
	nitems(target_module_100000),
	target_module_100000
},
{
	"target-module@300000",
	nitems(target_module_300000),
	target_module_300000
},
{
	"target-module@22000",
	nitems(target_module_22000),
	target_module_22000
},
{
	"target-module@24000",
	nitems(target_module_24000),
	target_module_24000
},
{
	"target-module@2a000",
	nitems(target_module_2a000),
	target_module_2a000
},
{
	"target-module@30000",
	nitems(target_module_30000),
	target_module_30000
},
{
	"target-module@40000",
	nitems(target_module_40000),
	target_module_40000
},
{
	"target-module@42000",
	nitems(target_module_42000),
	target_module_42000
},
{
	"target-module@44000",
	nitems(target_module_44000),
	target_module_44000
},
{
	"target-module@46000",
	nitems(target_module_46000),
	target_module_46000
},
{
	"target-module@48000",
	nitems(target_module_48000),
	target_module_48000
},
{
	"target-module@4a000",
	nitems(target_module_4a000),
	target_module_4a000
},
{
	"target-module@4c000",
	nitems(target_module_4c000),
	target_module_4c000
},
{
	"target-module@60000",
	nitems(target_module_60000),
	target_module_60000
},
{
	"target-module@80000",
	nitems(target_module_80000),
	target_module_80000
},
{
	"target-module@c8000",
	nitems(target_module_c8000),
	target_module_c8000
},
{
	"target-module@ca000",
	nitems(target_module_ca000),
	target_module_ca000
},
{
	"target-module@9c000",
	nitems(target_module_9c000),
	target_module_9c000
},
{
	"target-module@a0000",
	nitems(target_module_a0000),
	target_module_a0000
},
{
	"target-module@a6000",
	nitems(target_module_a6000),
	target_module_a6000
},
{
	"target-module@a8000",
	nitems(target_module_a8000),
	target_module_a8000
},
{
	"target-module@aa000",
	nitems(target_module_aa000),
	target_module_aa000
},
{
	"target-module@ac000",
	nitems(target_module_ac000),
	target_module_ac000
},
{
	"target-module@ae000",
	nitems(target_module_ae000),
	target_module_ae000
},
{
	"target-module@cc000",
	nitems(target_module_cc000),
	target_module_cc000
},
{
	"target-module@d0000",
	nitems(target_module_d0000),
	target_module_d0000
},
{
	"target-module@d8000",
	nitems(target_module_d8000),
	target_module_d8000
},
{
	"target-module@0",
	nitems(target_module_0),
	target_module_0
},
{
	"target-module@2000",
	nitems(target_module_2000),
	target_module_2000
},
{
	"target-module@4000",
	nitems(target_module_4000),
	target_module_4000
},
{
	"target-module@e000",
	nitems(target_module_e000),
	target_module_e000
},
{
	"target-module@10000",
	nitems(target_module_10000),
	target_module_10000
},
{
	"target-module@49000000",
	nitems(target_module_49000000),
	target_module_49000000
},
{
	"target-module@49800000",
	nitems(target_module_49800000),
	target_module_49800000
},
{
	"target-module@4c000000",
	nitems(target_module_4c000000),
	target_module_4c000000
},
{
	"target-module@40300000",
	nitems(target_module_40300000),
	target_module_40300000
},
{
	"target-module@49900000",
	nitems(target_module_49900000),
	target_module_49900000
},
{
	"target-module@49a00000",
	nitems(target_module_49a00000),
	target_module_49a00000
},
{
	"target-module@47810000",
	nitems(target_module_47810000),
	target_module_47810000
},
{
	"target-module@47400000",
	nitems(target_module_47400000),
	target_module_47400000
},
{
	"target-module@50000000",
	nitems(target_module_50000000),
	target_module_50000000
},
{
	"target-module@38000",
	nitems(target_module_38000),
	target_module_38000
},
{
	"target-module@3c000",
	nitems(target_module_3c000),
	target_module_3c000
},
{
	"target-module@4b000000",
	nitems(target_module_4b000000),
	target_module_4b000000
},
{
	"target-module@140000",
	nitems(target_module_140000),
	target_module_140000
},
{
	"target-module@53100000",
	nitems(target_module_53100000),
	target_module_53100000
},
{
	"target-module@53500000",
	nitems(target_module_53500000),
	target_module_53500000
},
{
	"target-module@56000000",
	nitems(target_module_56000000),
	target_module_56000000
},
};

static struct clk_link_def scm_clocks[] = {
	LINK("sys_clkin_ck"),
	LINK("adc_tsc_fck"),
	LINK("dcan0_fck"),
	LINK("dcan1_fck"),
	LINK("mcasp0_fck"),
	LINK("mcasp1_fck"),
	LINK("smartreflex0_fck"),
	LINK("smartreflex1_fck"),
	LINK("sha0_fck"),
	LINK("aes0_fck"),
	LINK("rng_fck"),
	LINK("ehrpwm0_tbclk"),
	LINK("ehrpwm1_tbclk"),
	LINK("ehrpwm2_tbclk"),
};

static struct clk_link_def per_cm_0[] = {
	/* reg = <0x38 0x2c>, <0x6c 0x28>, <0xac 0xc>,
		 <0xc0 0x1c>, <0xec 0xc>, <0x10c 0x8>, <0x130 0x4>; */
	/* <0x38 0x2c> */
	LINK("l4ls-clkctrl@38_0"),
	LINK("l4ls-clkctrl@38_4"),
	LINK("l4ls-clkctrl@38_8"),
	LINK("l4ls-clkctrl@38_c"),
	LINK("l4ls-clkctrl@38_10"),
	LINK("l4ls-clkctrl@38_14"),
	LINK("l4ls-clkctrl@38_18"),
	LINK("l4ls-clkctrl@38_1c"),
	LINK("l4ls-clkctrl@38_20"),
	LINK("l4ls-clkctrl@38_24"),
	LINK("l4ls-clkctrl@38_28"),
	/* <0x6c 0x28> */
	LINK("l4ls-clkctrl@38_34"),
	LINK("l4ls-clkctrl@38_38"),
	LINK("l4ls-clkctrl@38_3c"),
	LINK("l4ls-clkctrl@38_40"),
	LINK("l4ls-clkctrl@38_44"),
	LINK("l4ls-clkctrl@38_48"),
	LINK("l4ls-clkctrl@38_4c"),
	LINK("l4ls-clkctrl@38_50"),
	LINK("l4ls-clkctrl@38_54"),
	LINK("l4ls-clkctrl@38_58"),
	/* <0xac 0xc> */
	LINK("l4ls-clkctrl@38_74"),
	LINK("l4ls-clkctrl@38_75"),
	LINK("l4ls-clkctrl@38_78"),
	LINK("l4ls-clkctrl@38_79"),
	LINK("l4ls-clkctrl@38_7c"),
	LINK("l4ls-clkctrl@38_7d"),
	/* <0xc0 0x1c> */
	LINK("l4ls-clkctrl@38_88"),
	LINK("l4ls-clkctrl@38_8c"),
	LINK("l4ls-clkctrl@38_90"),
	LINK("l4ls-clkctrl@38_94"),
	LINK("l4ls-clkctrl@38_98"),
	LINK("l4ls-clkctrl@38_9c"),
	LINK("l4ls-clkctrl@38_a0"),
	/* <0xec 0xc> */
	LINK("l4ls-clkctrl@38_b4"),
	LINK("l4ls-clkctrl@38_b8"),
	LINK("l4ls-clkctrl@38_bc"),
	/* <0xd4 0x8> */
	LINK("l4ls-clkctrl@38_d4"),
	LINK("l4ls-clkctrl@38_d8"),
	/* <0x130 0x4> */
	LINK("l4ls-clkctrl@38_f8"),

	/* reg = <0x1c 0x4>, <0x30 0x8>, <0x68 0x4>, <0xf8 0x4> */
	/* <0x1c 0x4> */
	LINK("l3s-clkctrl@1c_0"),
	/* <0x30 0x8> */
	LINK("l3s-clkctrl@1c_14"),
	LINK("l3s-clkctrl@1c_18"),
	/* <0x68 0x4> */
	LINK("l3s-clkctrl@1c_4c"),
	/* <0xf8 0x4> */
	LINK("l3s-clkctrl@1c_dc"),


	/* reg = <0x24 0xc>, <0x94 0x10>, <0xbc 0x4>, <0xdc 0x8>, <0xfc 0x8>; */
	/* <0x24 0xc> */
	LINK("l3-clkctrl@24_0"),
	LINK("l3-clkctrl@24_4"),
	LINK("l3-clkctrl@24_8"),
	/* <0x94 0x10> */
	LINK("l3-clkctrl@24_70"),
	LINK("l3-clkctrl@24_74"),
	LINK("l3-clkctrl@24_78"),
	LINK("l3-clkctrl@24_7c"),
	/* <0xbc 0x4> */
	LINK("l3-clkctrl@24_98"),
	/* <0xdc 0x8> */
	LINK("l3-clkctrl@24_b8"),
	LINK("l3-clkctrl@24_bc"),
	/* <0xfc 0x8> */
	LINK("l3-clkctrl@24_d8"),
	LINK("l3-clkctrl@24_dc"),

	/* reg = <0x120 0x4>; */
	LINK("l4hs-clkctrl@120_0"),

	/* reg = <0xe8 0x4>; */
	LINK("pruss-ocp-clkctrl@e8_0"),

	/* reg = <0x0 0x18>; */
	LINK("cpsw-125mhz-clkctrl@0_0"),
	LINK("cpsw-125mhz-clkctrl@0_4"),
	LINK("cpsw-125mhz-clkctrl@0_8"),
	LINK("cpsw-125mhz-clkctrl@0_c"),
	LINK("cpsw-125mhz-clkctrl@0_10"),
	LINK("cpsw-125mhz-clkctrl@0_14"),

	/* reg = <0x18 0x4>; */
	LINK("lcdc-clkctrl@18_0"),

	/* reg = <0x14c 0x4>; */
	LINK("clk-24mhz-clkctrl@14c_0"),

	/* reg = <0x0 0x10>, <0xb4 0x24>; */
	/* <0x0 0x10> */
	LINK("l4-wkup-clkctrl@0_0"),
	LINK("l4-wkup-clkctrl@0_4"),
	LINK("l4-wkup-clkctrl@0_8"),
	LINK("l4-wkup-clkctrl@0_9"),
	LINK("l4-wkup-clkctrl@0_c"),
	/* <0xb4 0x24> */
	LINK("l4-wkup-clkctrl@0_b4"),
	LINK("l4-wkup-clkctrl@0_b8"),
	LINK("l4-wkup-clkctrl@0_bc"),
	LINK("l4-wkup-clkctrl@0_c0"),
	LINK("l4-wkup-clkctrl@0_c4"),
	LINK("l4-wkup-clkctrl@0_c8"),
	LINK("l4-wkup-clkctrl@0_cc"),
	LINK("l4-wkup-clkctrl@0_d0"),
	LINK("l4-wkup-clkctrl@0_d4"),

	/* reg = <0x14 0x4>; */
	LINK("l3-aon-clkctrl@14_0"),

	/* reg = <0xb0 0x4>; */
	LINK("l4-wkup-aon-clkctrl@b0_0"),

	/* reg = <0x0 0x8>; */
	LINK("mpu-clkctrl@0_0"),
	LINK("mpu-clkctrl@0_4"),

	/* reg = <0x0 0x4>; */
	LINK("l4-rtc-clkctrl@0_0"),

	/* reg = <0x0 0x8>; */
	LINK("gfx-l3-clkctrl@0_0"),
	LINK("gfx-l3-clkctrl@0_4"),

	/* reg = <0x0 0x24>; */
	LINK("l4-cefuse-clkctrl@0_0"),
	LINK("l4-cefuse-clkctrl@0_4"),
	LINK("l4-cefuse-clkctrl@0_8"),
	LINK("l4-cefuse-clkctrl@0_c"),
	LINK("l4-cefuse-clkctrl@0_10"),
	LINK("l4-cefuse-clkctrl@0_14"),
	LINK("l4-cefuse-clkctrl@0_18"),
	LINK("l4-cefuse-clkctrl@0_1c"),
	LINK("l4-cefuse-clkctrl@0_20"),
};

/* === ti_clkctrl.c === */
/*
 * Check out XX_CLKCTRL-INDEX(offset)-macro dance in
 * sys/gnu/dts/dts/include/dt-bindings/clock/am3.h
 * sys/gnu/dts/dts/include/dt-bindings/clock/am4.h
 * sys/gnu/dts/dts/include/dt-bindings/clock/dra7.h
 * it is the basis for the name scheme
 * xxx_clkctrl_[baseoffset]_[offset from base]
 */

/* reg = <0x38 0x2c>, <0x6c 0x28>, <0xac 0xc>, <0xc0 0x1c>, <0xec 0xc>, <0x10c 0x8>, <0x130 0x4>; */
/* <0x38 0x2c> */
PLIST(l4ls_clkctrl_38_0) = { "dpll_per_m2_div4_ck" }; /* am3.h UART6 clkctrl, TRM 19.2.2 */
PLIST(l4ls_clkctrl_38_4) = { "mmc_clk" }; /* am3.h MMC1 clkctrl, TRM 18.2.2 */
PLIST(l4ls_clkctrl_38_8) = { "l4ls_gclk" }; /* am3.h ELM clkctrl, TRM 7.4.2.2 */
PLIST(l4ls_clkctrl_38_c) = { "dpll_per_m2_div4_ck" }; /* am3.h I2C3 clkctrl, TRM 21.2.2 */
PLIST(l4ls_clkctrl_38_10) = { "dpll_per_m2_div4_ck" }; /* am3.h I2C2 clkctrl, TRM 21.2.2 */
PLIST(l4ls_clkctrl_38_14) = { "dpll_per_m2_div4_ck" }; /* am3.h SPI0 clkctrl, TRM 24.2.2 */
PLIST(l4ls_clkctrl_38_18) = { "dpll_per_m2_div4_ck" }; /* am3.h SPI1 clkctrl, TRM 24.2.2 */
/* 1c, 20, 24 are not described in the TRM */
//PLIST(l4ls_clkctrl_38_1c) = { NULL }; /* am3.h TRM ? */
//PLIST(l4ls_clkctrl_38_20) = { NULL }; /* am3.h TRM ? */
//PLIST(l4ls_clkctrl_38_24) = { NULL }; /* am3.h TRM ? */
PLIST(l4ls_clkctrl_38_28) = { "l4ls_gclk" }; /* am3.h L4_LS clkctrl, TRM 8.1.12.1.19 */
/* <0x6c 0x28> */
PLIST(l4ls_clkctrl_38_34) = { "dpll_per_m2_div4_ck" }; /* am3.h UART2 clkctrl, TRM 19.2.2 */
PLIST(l4ls_clkctrl_38_38) = { "dpll_per_m2_div4_ck" }; /* am3.h UART3 clkctrl, TRM 19.2.2 */
PLIST(l4ls_clkctrl_38_3c) = { "dpll_per_m2_div4_ck" }; /* am3.h UART4 clkctrl, TRM 19.2.2 */
PLIST(l4ls_clkctrl_38_40) = { "dpll_per_m2_div4_ck" }; /* am3.h UART5 clkctrl, TRM 19.2.2 */
PLIST(l4ls_clkctrl_38_44) = { "timer7_fck" }; /* am3.h TIMER7 clkctrl, TRM 20.1.2.3 */
PLIST(l4ls_clkctrl_38_48) = { "timer2_fck" }; /* am3.h TIMER7 clkctrl, TRM 20.1.2.3 */
PLIST(l4ls_clkctrl_38_4c) = { "timer3_fck" }; /* am3.h TIMER2 clkctrl, TRM 20.1.2.3 */
PLIST(l4ls_clkctrl_38_50) = { "timer4_fck" }; /* am3.h TIMER3 clkctrl, TRM 20.1.2.3 */
//PLIST(l4ls_clkctrl_38_54) = { NULL }; /* am3.h ? TRM ? */
PLIST(l4ls_clkctrl_38_58) = { "rng_fck" }; /* am3.h RNG clkctrl, TRM doesnt describe the rng, rng_fck only from the am33xx-clocks.dtsi */
/* <0xac 0xc> */
PLIST(l4ls_clkctrl_38_74) = { "l4ls_gclk" }; /* am3.h GPIO2 clkctrl, TRM 25.2.2 */
PLIST(l4ls_clkctrl_38_75) = { "clk_32768_ck" }; /* am3.h GPIO2 clkctrl, TRM 25.2.2 */
PLIST(l4ls_clkctrl_38_78) = { "l4ls_gclk" }; /* am3.h GPIO3 clkctrl, TRM 25.2.2 */
PLIST(l4ls_clkctrl_38_79) = { "clk_32768_ck" }; /* am3.h GPIO3 clkctrl, TRM 25.2.2 */
PLIST(l4ls_clkctrl_38_7c) = { "l4ls_gclk" }; /* am3.h GPIO4 clkctrl, TRM 25.2.2 */
PLIST(l4ls_clkctrl_38_7d) = { "clk_32768_ck" }; /* am3.h GPIO4 clkctrl, TRM 25.2.2 */
/* <0xc0 0x1c> */
PLIST(l4ls_clkctrl_38_88) = { "dcan0_fck" }; /* am3.h D_CAN0 clkctrl, TRM 23.2.2 */
PLIST(l4ls_clkctrl_38_8c) = { "dcan1_fck" }; /* am3.h D_CAN1 clkctrl, TRM 23.2.2 */
/* 90 not described in am3.h */
//PLIST(l4ls_clkctrl_38_90) = { NULL }; /* am3.h */
PLIST(l4ls_clkctrl_38_94) = { "l4ls_gclk" }; /* am3.h EPWMMS1 clkctrl, TRM 15.1.2.3 */
/* 98 not described in am3.h */
//PLIST(l4ls_clkctrl_38_98) = { NULL }; /* am3.h */
PLIST(l4ls_clkctrl_38_9c) = { "l4ls_gclk" }; /* am3.h EPWMMS0 clkctrl, TRM 15.1.2.3 */
PLIST(l4ls_clkctrl_38_a0) = { "l4ls_gclk" }; /* am3.h EPWMMS2 clkctrl, TRM 15.1.2.3 */
/* <0xec 0xc> */
PLIST(l4ls_clkctrl_38_b4) = { "timer5_fck" }; /* am3.h TIMER5 clkctrl, TRM 20.1.2.3 */
PLIST(l4ls_clkctrl_38_b8) = { "timer6_fck" }; /* am3.h TIMER6 clkctrl, TRM 20.1.2.3 */
PLIST(l4ls_clkctrl_38_bc) = { "mmc_clk" }; /* am3.h MMC2 clkctrl, TRM 18.2.2 */
/* <0xd4 0x8> */
PLIST(l4ls_clkctrl_38_d4) = { "l4ls_gclk" }; /* am3.h SPINLOCK clkctrl, TRM 8.1.12.1.48 "SPINLOCK clocks" */
PLIST(l4ls_clkctrl_38_d8) = { "l4ls_gclk" }; /* am3.h MAILBOX clkctrl, TRM 17.1.1.2 */
/* <0x130 0x4> */
PLIST(l4ls_clkctrl_38_f8) = { "l4ls_gclk" }; /* am3.h OCPWP clkctrl, TRM 8.1.12.1.53 "OCPWP clocks" */

/* reg = <0x1c 0x4>, <0x30 0x8>, <0x68 0x4>, <0xf8 0x4> */
/* <0x1c 0x4> */
PLIST(l3s_clkctrl_1c_0) = { "usbotg_fck" }; /* am3.h USB_OTG_HS clkctrl, TRM 16.1.2 fig 16-1 */
/* <0x30 0x8> */
PLIST(l3s_clkctrl_1c_14) = { "l3s_gclk" }; /* am3.h GPMC clkctrl, TRM 7.1.2.2 */
PLIST(l3s_clkctrl_1c_18) = { "mcasp0_fck" }; /* am3.h MCASP0 clkctrl, TRM 22.2.2 */
/* <0x68 0x4> */
PLIST(l3s_clkctrl_1c_4c) = { "mcasp1_fck" }; /* am3.h MCASP1 clkctrl, TRM 22.2.2 */
/* <0xf8 0x4> */
PLIST(l3s_clkctrl_1c_dc) = { "mmc_clk" }; /* am3.h MMC3 clkctrl, TRM 18.2.2 */

/* reg = <0x24 0xc>, <0x94 0x10>, <0xbc 0x4>, <0xdc 0x8>, <0xfc 0x8>; */
/* <0x24 0xc> */
PLIST(l3_clkctrl_24_0) = { "l3_gclk" }; /* am3.h TPTC0 clkctrl, TRM 11.2.2.2 */
PLIST(l3_clkctrl_24_4) = { "dpll_ddr_m2_div2_ck" }; /* am3.h EMIF clkctrl, TRM 7.3.2.2 */
PLIST(l3_clkctrl_24_8) = { "l3_gclk" }; /* am3.h OCMCRAM clkctrl, TRM 7.2.2.2 */
/* <0x94 0x10> */
PLIST(l3_clkctrl_24_70) = { "aes0_fck" }; /* am3.h AES clkctrl, not in TRM, derived from am33xx-clocks.dtsi */
//PLIST(l3_clkctrl_24_74) = { NULL }; /* am3.h ?? clkctrl, TRM ??? */
//PLIST(l3_clkctrl_24_78) = { NULL }; /* am3.h ?? clkctrl, TRM ???? */
PLIST(l3_clkctrl_24_7c) = { "l3_gclk" }; /* am3.h SHAM clkctrl, not in TRM, assume l3_gclk */
/* <0xbc 0x4> */
PLIST(l3_clkctrl_24_98) = { "l3_gclk" }; /* am3.h TPCC clkctrl, TRM 11.2.1.2 */
/* <0xdc 0x8> */
PLIST(l3_clkctrl_24_b8) = { "l3_gclk" }; /* am3.h L3 INSTR clkctrl, TRM 8.1.12.1.38 "L3 INSTR clocks" */
PLIST(l3_clkctrl_24_bc) = { "l3_gclk" }; /* am3.h L3 Main clkctrl, TRM 18.1.12.1.39 "L3 interconnect clocks" */
/* <0xfc 0x8> */
PLIST(l3_clkctrl_24_d8) = { "l3_gclk" }; /* am3.h TPTC1 clkctrl, TRM 11.2.2.2 */
PLIST(l3_clkctrl_24_dc) = { "l3_gclk" }; /* am3.h TPTC2 clkctrl, TRM 11.2.2.2 */

/* reg = <0x120 0x4>; */
PLIST(l4hs_clkctrl_120_0) = { "l4hs_gclk" }; /* am3.h L4HS clkctrl, TRM 8.1.12.1.50 */

/* reg = <0xe8 0x4>; */
PLIST(pruss_ocp_clkctrl_e8_0) = { "pruss_ocp_gclk" }; /* am3.h ocp pruss clkctrl, TRM 4.2.2 */

/* reg = <0x0 0x18>; */
#if 0
PLIST(cpsw_125mhz_clkctrl_0_0) = { NULL }; /* am3.h Not mentioned in TRM, TRM 14.2.2 */
PLIST(cpsw_125mhz_clkctrl_0_4) = { NULL }; /* am3.h Not mentioned in TRM, TRM 14.2.2 */
PLIST(cpsw_125mhz_clkctrl_0_8) = { NULL }; /* am3.h Not mentioned in TRM, TRM 14.2.2 */
PLIST(cpsw_125mhz_clkctrl_0_c) = { NULL }; /* am3.h Not mentioned in TRM, TRM 14.2.2 */
PLIST(cpsw_125mhz_clkctrl_0_10) = { NULL }; /* am3.h Not mentioned in TRM, TRM 14.2.2 */
#endif
PLIST(cpsw_125mhz_clkctrl_0_14) = { "cpsw_125mhz_gclk" }; /* am3.h cpsw 125 mhz cpgmaco clkctrl, TRM 14.2.2 */

/* reg = <0x18 0x4>; */
PLIST(lcdc_clkctrl_18_0) = { "lcd_gclk" }; /* am3.h lcdc clkctrl, TRM 13.2.2 */

/* reg = <0x14c 0x4>; */
PLIST(clk_24mhz_clkctrl_14c_0) = { "clkdiv32k_ck" }; /* am3.h clkdiv32k clkctrl, TRM 8.1.12.1.57 */

/* reg = <0x0 0x10>, <0xb4 0x24>; */
/* <0x0 0x10> */
//PLIST(l4_wkup_clkctrl_0_0) = { NULL }; /* am3.h clkstctrl, TRM 8.1.12.2.1 */
PLIST(l4_wkup_clkctrl_0_4) = { "mmc_clk" }; /* am3.h control clkctrl, TRM 18.2.2 */
PLIST(l4_wkup_clkctrl_0_8) = { "dpll_core_m4_div2_ck" }; /* am3.h gpio1 clkctrl, TRM 25.2.2 */
PLIST(l4_wkup_clkctrl_0_9) = { "gpio0_dbclk_mux_ck" }; /* am3.h gpio1 clkctrl, TRM 25.2.2 */
PLIST(l4_wkup_clkctrl_0_c) = { "mmc_clk" }; /* am3.h L4 wkup clkctrl, TRM 18.2.2 */
/* <0xb4 0x24> */
PLIST(l4_wkup_clkctrl_0_b4) = { "dpll_per_m2_div4_wkupdm_ck" }; /* am3.h uart1 clkctrl, TRM 19.2.2 */
PLIST(l4_wkup_clkctrl_0_b8) = { "dpll_per_m2_div4_wkupdm_ck" }; /* am3.h i2c1 wkup clkctrl, TRM 21.2.2 */
PLIST(l4_wkup_clkctrl_0_bc) = { "adc_tsc_fck" }; /* am3.h adc tsc clkctrl, TRM 12.2.2 */
PLIST(l4_wkup_clkctrl_0_c0) = { "smartreflex0_fck" }; /* am3.h smartreflex0 clkctrl, TRM 8.1.12.2.49 */
PLIST(l4_wkup_clkctrl_0_c4) = { "timer1_fck" }; /* am3.h timer1 clkctrl, TRM 20.1.2.3 */
PLIST(l4_wkup_clkctrl_0_c8) = { "smartreflex1_fck" }; /* am3.h smartreflex1 clkctrl, TRM 8.1.12.2.51 */
//PLIST(l4_wkup_clkctrl_0_cc) = { NULL }; /* am3.h l4_wkup_aon_clkstctrl, TRM 8.1.12.2.52 */
//PLIST(l4_wkup_clkctrl_0_d0) = { NULL }; /* am3.h ??? clkctrl, not in TRM */
PLIST(l4_wkup_clkctrl_0_d4) = { "wdt1_fck" }; /* am3.h wd timer2 clkctrl, TRM 20.4.2.2 */

/* reg = <0x14 0x4>; */
//PLIST(l3_aon_clkctrl_14_0) = { NULL }; /* am3.h debugss clkctrl, TRM 8.1.12.2.6 multiple sub clocks - todo */

/* reg = <0xb0 0x4>; */
//PLIST(l4_wkup_aon_wkup_m3_clkctrl_b0_0) = { NULL }; /* am3.h l4 wkup aon wkup m3 clkctrl, TRM 8.1.12.2.45 */

/* reg = <0x0 0x8>; */
//PLIST(mpu_clkctrl_0_0) = { NULL }; /* am3.h mpu clkstctrl, TRM 8.1.12.4.1 */
PLIST(mpu_clkctrl_0_4) = { "dpll_mpu_ck" }; /* am3.h mpu clkctrl, TRM 8.1.12.4.2 / 3.1.3 */

/* reg = <0x0 0x4>; */
PLIST(l4_rtc_clkctrl_0_0) = { "clk_32768_ck" }; /* am3.h RTC clkctrl, TRM 20.3.2.2 */

/* reg = <0x0 0x8>; */
//PLIST(gfx_l3_clkctrl_0_0) = { NULL }; /* am3.h L3 GFX clkctrl, TRM 5.1.2 */
PLIST(gfx_l3_clkctrl_0_4) = { "gfx_fck_div_ck" }; /* am3.h L3 GFX clkctrl, TRM 5.1.2 */

/* reg = <0x0 0x24>; */
#if 0
PLIST(l4_cefuse_clkctrl_0_0) = { NULL }; /* am3.h cefuse clkctrl, TRM 8.1.12.8.2  */
PLIST(l4_cefuse_clkctrl_0_4) = { NULL }; /* am3.h cefuse clkctrl, TRM 8.1.12.8.2  */
PLIST(l4_cefuse_clkctrl_0_8) = { NULL }; /* am3.h cefuse clkctrl, TRM 8.1.12.8.2  */
PLIST(l4_cefuse_clkctrl_0_c) = { NULL }; /* am3.h cefuse clkctrl, TRM 8.1.12.8.2  */
PLIST(l4_cefuse_clkctrl_0_10) = { NULL }; /* am3.h cefuse clkctrl, TRM 8.1.12.8.2  */
PLIST(l4_cefuse_clkctrl_0_14) = { NULL }; /* am3.h cefuse clkctrl, TRM 8.1.12.8.2  */
PLIST(l4_cefuse_clkctrl_0_18) = { NULL }; /* am3.h cefuse clkctrl, TRM 8.1.12.8.2  */
PLIST(l4_cefuse_clkctrl_0_1c) = { NULL }; /* am3.h cefuse clkctrl, TRM 8.1.12.8.2  */
PLIST(l4_cefuse_clkctrl_0_20) = { NULL }; /* am3.h cefuse clkctrl, TRM 8.1.12.8.2  */
#endif


static struct ti_clkctrl_lookup_table am33xx_l4ls_clkctrl_table[] = {

/* reg = <0x38 0x2c>, <0x6c 0x28>, <0xac 0xc>, <0xc0 0x1c>, <0xec 0xc>, <0x10c 0x8>, <0x130 0x4>;
	*/
/* <0x38 0x2c> */
	{ "l4ls-clkctrl@38_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_UART6_CLKCTRL, 0, nitems(l4ls_clkctrl_38_0), l4ls_clkctrl_38_0 },
	{ "l4ls-clkctrl@38_4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_MMC1_CLKCTRL, 0, nitems(l4ls_clkctrl_38_4), l4ls_clkctrl_38_4 },
	{ "l4ls-clkctrl@38_8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_ELM_CLKCTRL, 0, nitems(l4ls_clkctrl_38_8), l4ls_clkctrl_38_8 },
	{ "l4ls-clkctrl@38_c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_I2C3_CLKCTRL, 0, nitems(l4ls_clkctrl_38_c), l4ls_clkctrl_38_c },
	{ "l4ls-clkctrl@38_10", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_I2C2_CLKCTRL, 0, nitems(l4ls_clkctrl_38_10), l4ls_clkctrl_38_10 },
	{ "l4ls-clkctrl@38_14", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_SPI0_CLKCTRL, 0, nitems(l4ls_clkctrl_38_14), l4ls_clkctrl_38_14 },
	{ "l4ls-clkctrl@38_18", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_SPI1_CLKCTRL, 0, nitems(l4ls_clkctrl_38_18), l4ls_clkctrl_38_18 },
	{ "l4ls-clkctrl@38_1c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4ls-clkctrl@38_20", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4ls-clkctrl@38_24", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4ls-clkctrl@38_28", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_L4_LS_CLKCTRL, 0, nitems(l4ls_clkctrl_38_28), l4ls_clkctrl_38_28 },
/* <0x6c 0x28> */
	{ "l4ls-clkctrl@38_34", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_UART2_CLKCTRL, 0, nitems(l4ls_clkctrl_38_34), l4ls_clkctrl_38_34 },
	{ "l4ls-clkctrl@38_38", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_UART3_CLKCTRL, 0, nitems(l4ls_clkctrl_38_38), l4ls_clkctrl_38_38 },
	{ "l4ls-clkctrl@38_3c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_UART4_CLKCTRL, 0, nitems(l4ls_clkctrl_38_3c), l4ls_clkctrl_38_3c },
	{ "l4ls-clkctrl@38_40", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_UART5_CLKCTRL, 0, nitems(l4ls_clkctrl_38_40), l4ls_clkctrl_38_40 },
	{ "l4ls-clkctrl@38_44", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_TIMER7_CLKCTRL, 0, nitems(l4ls_clkctrl_38_44), l4ls_clkctrl_38_44 },
	{ "l4ls-clkctrl@38_48", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_TIMER2_CLKCTRL, 0, nitems(l4ls_clkctrl_38_48), l4ls_clkctrl_38_48 },
	{ "l4ls-clkctrl@38_4c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_TIMER3_CLKCTRL, 0, nitems(l4ls_clkctrl_38_4c), l4ls_clkctrl_38_4c },
	{ "l4ls-clkctrl@38_50", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_TIMER4_CLKCTRL, 0, nitems(l4ls_clkctrl_38_50), l4ls_clkctrl_38_50 },
	{ "l4ls-clkctrl@38_54", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4ls-clkctrl@38_58", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_RNG_CLKCTRL, 0, nitems(l4ls_clkctrl_38_58), l4ls_clkctrl_38_58 },
/* <0xac 0xc> */
	{ "l4ls-clkctrl@38_74", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_GPIO2_CLKCTRL, 0, nitems(l4ls_clkctrl_38_74), l4ls_clkctrl_38_74 },
	{ "l4ls-clkctrl@38_75", TI_CLKCTRL_GATE, 18, 0x40000, 0, AM3_L4LS_GPIO2_CLKCTRL, 1, nitems(l4ls_clkctrl_38_75), l4ls_clkctrl_38_75 },
	{ "l4ls-clkctrl@38_78", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_GPIO3_CLKCTRL, 0, nitems(l4ls_clkctrl_38_78), l4ls_clkctrl_38_78 },
	{ "l4ls-clkctrl@38_79", TI_CLKCTRL_GATE, 18, 0x40000, 0, AM3_L4LS_GPIO3_CLKCTRL, 1, nitems(l4ls_clkctrl_38_79), l4ls_clkctrl_38_79 },
	{ "l4ls-clkctrl@38_7c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_GPIO4_CLKCTRL, 0, nitems(l4ls_clkctrl_38_7c), l4ls_clkctrl_38_7c },
	{ "l4ls-clkctrl@38_7d", TI_CLKCTRL_GATE, 18, 0x40000, 0, AM3_L4LS_GPIO4_CLKCTRL, 1, nitems(l4ls_clkctrl_38_7d), l4ls_clkctrl_38_7d },
/* <0xc0 0x1c> */
	{ "l4ls-clkctrl@38_88", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_D_CAN0_CLKCTRL, 0, nitems(l4ls_clkctrl_38_88), l4ls_clkctrl_38_88 },
	{ "l4ls-clkctrl@38_8c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_D_CAN1_CLKCTRL, 0, nitems(l4ls_clkctrl_38_8c), l4ls_clkctrl_38_8c },
	{ "l4ls-clkctrl@38_90", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4ls-clkctrl@38_94", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_EPWMSS1_CLKCTRL, 0, nitems(l4ls_clkctrl_38_94), l4ls_clkctrl_38_94 },
	{ "l4ls-clkctrl@38_98", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4ls-clkctrl@38_9c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_EPWMSS0_CLKCTRL, 0, nitems(l4ls_clkctrl_38_9c), l4ls_clkctrl_38_9c },
	{ "l4ls-clkctrl@38_a0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_EPWMSS2_CLKCTRL, 0, nitems(l4ls_clkctrl_38_a0), l4ls_clkctrl_38_a0 },
/* <0xec 0xc> */
	{ "l4ls-clkctrl@38_b4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_TIMER5_CLKCTRL, 0, nitems(l4ls_clkctrl_38_b4), l4ls_clkctrl_38_b4 },
	{ "l4ls-clkctrl@38_b8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_TIMER6_CLKCTRL, 0, nitems(l4ls_clkctrl_38_b8), l4ls_clkctrl_38_b8 },
	{ "l4ls-clkctrl@38_bc", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_MMC2_CLKCTRL, 0, nitems(l4ls_clkctrl_38_bc), l4ls_clkctrl_38_bc },
/* <0xd4 0x8> */
	{ "l4ls-clkctrl@38_d4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_SPINLOCK_CLKCTRL, 0, nitems(l4ls_clkctrl_38_d4), l4ls_clkctrl_38_d4 },
	{ "l4ls-clkctrl@38_d8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_MAILBOX_CLKCTRL, 0, nitems(l4ls_clkctrl_38_d8), l4ls_clkctrl_38_d8 },
/* <0x130 0x4> */
	{ "l4ls-clkctrl@38_f8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4LS_OCPWP_CLKCTRL, 0, nitems(l4ls_clkctrl_38_f8), l4ls_clkctrl_38_f8 },
};

static struct ti_clkctrl_lookup_table am33xx_l3s_clkctrl_table[] = {
/* reg = <0x1c 0x4>, <0x30 0x8>, <0x68 0x4>, <0xf8 0x4> */
/* <0x1c 0x4> */
	{ "l3s-clkctrl@1c_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3S_USB_OTG_HS_CLKCTRL, 0, nitems(l3s_clkctrl_1c_0), l3s_clkctrl_1c_0 },
/* <0x30 0x8> */
	{ "l3s-clkctrl@1c_14", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3S_GPMC_CLKCTRL, 0, nitems(l3s_clkctrl_1c_14), l3s_clkctrl_1c_14 },
	{ "l3s-clkctrl@1c_18", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3S_MCASP0_CLKCTRL, 0, nitems(l3s_clkctrl_1c_18), l3s_clkctrl_1c_18 },
/* <0x68 0x4> */
	{ "l3s-clkctrl@1c_4c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3S_MCASP1_CLKCTRL, 0, nitems(l3s_clkctrl_1c_4c), l3s_clkctrl_1c_4c },
/* <0xf8 0x4> */
	{ "l3s-clkctrl@1c_dc", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3S_MMC3_CLKCTRL, 0, nitems(l3s_clkctrl_1c_dc), l3s_clkctrl_1c_dc },
};

static struct ti_clkctrl_lookup_table am33xx_l3_clkctrl_table[] = {
/* reg = <0x24 0xc>, <0x94 0x10>, <0xbc 0x4>, <0xdc 0x8>, <0xfc 0x8>; */
/* <0x24 0xc> */
	{ "l3-clkctrl@24_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3_TPTC0_CLKCTRL, 0, nitems(l3_clkctrl_24_0), l3_clkctrl_24_0 },
	{ "l3-clkctrl@24_4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3_EMIF_CLKCTRL, 0, nitems(l3_clkctrl_24_4), l3_clkctrl_24_4 },
	{ "l3-clkctrl@24_8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3_OCMCRAM_CLKCTRL, 0, nitems(l3_clkctrl_24_8), l3_clkctrl_24_8 },
/* <0x94 0x10> */
	{ "l3-clkctrl@24_70", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3_AES_CLKCTRL, 0, nitems(l3_clkctrl_24_70), l3_clkctrl_24_70 },
	{ "l3-clkctrl@24_74", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l3-clkctrl@24_78", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l3-clkctrl@24_7c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3_SHAM_CLKCTRL, 0, nitems(l3_clkctrl_24_7c), l3_clkctrl_24_7c },
/* <0xbc 0x4> */
	{ "l3-clkctrl@24_98", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3_TPCC_CLKCTRL, 0, nitems(l3_clkctrl_24_98), l3_clkctrl_24_98 },
/* <0xdc 0x8> */
	{ "l3-clkctrl@24_b8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3_L3_INSTR_CLKCTRL, 0, nitems(l3_clkctrl_24_b8), l3_clkctrl_24_b8 },
	{ "l3-clkctrl@24_bc", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3_L3_MAIN_CLKCTRL, 0, nitems(l3_clkctrl_24_bc), l3_clkctrl_24_bc },
/* <0xfc 0x8> */
	{ "l3-clkctrl@24_d8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3_TPTC1_CLKCTRL, 0, nitems(l3_clkctrl_24_d8), l3_clkctrl_24_d8 },
	{ "l3-clkctrl@24_dc", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L3_TPTC2_CLKCTRL, 0, nitems(l3_clkctrl_24_dc), l3_clkctrl_24_dc },
};

static struct ti_clkctrl_lookup_table am33xx_l4hs_clkctrl_table[] = {
/* reg = <0x120 0x4>; */
	{ "l4hs-clkctrl@120_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4HS_L4_HS_CLKCTRL, 0, nitems(l4hs_clkctrl_120_0), l4hs_clkctrl_120_0 },
};

static struct ti_clkctrl_lookup_table am33xx_pruss_clkctrl_table[] = {
/* reg = <0xe8 0x4>; */
	{ "pruss-ocp-clkctrl@e8_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_PRUSS_OCP_PRUSS_CLKCTRL, 0, nitems(pruss_ocp_clkctrl_e8_0), pruss_ocp_clkctrl_e8_0 },
};

static struct ti_clkctrl_lookup_table am33xx_cpsw_clkctrl_table[] = {
/* reg = <0x0 0x18>; */
	{ "cpsw-125mhz-clkctrl@0_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "cpsw-125mhz-clkctrl@0_4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "cpsw-125mhz-clkctrl@0_8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "cpsw-125mhz-clkctrl@0_c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "cpsw-125mhz-clkctrl@0_10", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "cpsw-125mhz-clkctrl@0_14", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_CPSW_125MHZ_CPGMAC0_CLKCTRL, 0, nitems(cpsw_125mhz_clkctrl_0_14), cpsw_125mhz_clkctrl_0_14 },
};

static struct ti_clkctrl_lookup_table am33xx_lcdc_clkctrl_table[] = {
/* reg = <0x18 0x4>; */
	{ "lcdc-clkctrl@18_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_LCDC_LCDC_CLKCTRL, 0, nitems(lcdc_clkctrl_18_0), lcdc_clkctrl_18_0 },
};

static struct ti_clkctrl_lookup_table am33xx_clk_24mhz_clkctrl_table[] = {
/* reg = <0x14c 0x4>; */
	{ "clk-24mhz-clkctrl@14c_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_CLK_24MHZ_CLKDIV32K_CLKCTRL, 0, nitems(clk_24mhz_clkctrl_14c_0), clk_24mhz_clkctrl_14c_0 },
};

static struct ti_clkctrl_lookup_table am33xx_l4_wkup_clkctrl_table[] = {
/* reg = <0x0 0x10>, <0xb4 0x24>; */
/* <0x0 0x10> */
	{ "l4-wkup-clkctrl@0_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-wkup-clkctrl@0_4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_WKUP_CONTROL_CLKCTRL, 0, nitems(l4_wkup_clkctrl_0_4), l4_wkup_clkctrl_0_4 },
	{ "l4-wkup-clkctrl@0_8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_WKUP_GPIO1_CLKCTRL, 0, nitems(l4_wkup_clkctrl_0_8), l4_wkup_clkctrl_0_8 },
	{ "l4-wkup-clkctrl@0_9", TI_CLKCTRL_GATE, 18, 0x40000, 0, AM3_L4_WKUP_GPIO1_CLKCTRL, 1, nitems(l4_wkup_clkctrl_0_9), l4_wkup_clkctrl_0_9 },
	{ "l4-wkup-clkctrl@0_c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_WKUP_L4_WKUP_CLKCTRL, 0, nitems(l4_wkup_clkctrl_0_c), l4_wkup_clkctrl_0_c },
/* <0xb4 0x24> */
	{ "l4-wkup-clkctrl@0_b4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_WKUP_UART1_CLKCTRL, 0, nitems(l4_wkup_clkctrl_0_b4), l4_wkup_clkctrl_0_b4 },
	{ "l4-wkup-clkctrl@0_b8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_WKUP_I2C1_CLKCTRL, 0, nitems(l4_wkup_clkctrl_0_b8), l4_wkup_clkctrl_0_b8 },
	{ "l4-wkup-clkctrl@0_bc", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_WKUP_ADC_TSC_CLKCTRL, 0, nitems(l4_wkup_clkctrl_0_bc), l4_wkup_clkctrl_0_bc },
	{ "l4-wkup-clkctrl@0_c0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_WKUP_SMARTREFLEX0_CLKCTRL, 0, nitems(l4_wkup_clkctrl_0_c0), l4_wkup_clkctrl_0_c0 },
	{ "l4-wkup-clkctrl@0_c4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_WKUP_TIMER1_CLKCTRL, 0, nitems(l4_wkup_clkctrl_0_c4), l4_wkup_clkctrl_0_c4 },
	{ "l4-wkup-clkctrl@0_c8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_WKUP_SMARTREFLEX1_CLKCTRL, 0, nitems(l4_wkup_clkctrl_0_c8), l4_wkup_clkctrl_0_c8 },
	{ "l4-wkup-clkctrl@0_cc", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-wkup-clkctrl@0_d0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-wkup-clkctrl@0_d4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_WKUP_WD_TIMER2_CLKCTRL, 0, nitems(l4_wkup_clkctrl_0_d4), l4_wkup_clkctrl_0_d4 },
};

static struct ti_clkctrl_lookup_table am33xx_l3_aon_clkctrl_table[] = {
/* reg = <0x14 0x4>; */
	{ "l3-aon-clkctrl@14_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
};

static struct ti_clkctrl_lookup_table am33xx_l4_wkup_aon_clkctrl_table[] = {
/* reg = <0xb0 0x4>; */
	{ "l4-wkup-aon-clkctrl@b0_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
};

static struct ti_clkctrl_lookup_table am33xx_mpu_clkctrl_table[] = {
/* reg = <0x0 0x8>; */
	{ "mpu-clkctrl@0_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "mpu-clkctrl@0_4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_MPU_MPU_CLKCTRL, 0, nitems(mpu_clkctrl_0_4), mpu_clkctrl_0_4 },
};

static struct ti_clkctrl_lookup_table am33xx_l4_rtc_clkctrl_table[] = {
/* reg = <0x0 0x4>; */
	{ "l4-rtc-clkctrl@0_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_L4_RTC_RTC_CLKCTRL, 0, nitems(l4_rtc_clkctrl_0_0), l4_rtc_clkctrl_0_0 },
};

static struct ti_clkctrl_lookup_table am33xx_gfx_l3_clkctrl_table[] = {
/* reg = <0x0 0x8>; */
	{ "gfx-l3-clkctrl@0_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "gfx-l3-clkctrl@0_4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, AM3_GFX_L3_GFX_CLKCTRL, 0, nitems(gfx_l3_clkctrl_0_4), gfx_l3_clkctrl_0_4 },
};

static struct ti_clkctrl_lookup_table am33xx_l4_cefuse_clkctrl_table[] = {
/* reg = <0x0 0x24>; */
	{ "l4-cefuse-clkctrl@0_0", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-cefuse-clkctrl@0_4", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-cefuse-clkctrl@0_8", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-cefuse-clkctrl@0_c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-cefuse-clkctrl@0_10", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-cefuse-clkctrl@0_14", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-cefuse-clkctrl@0_18", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-cefuse-clkctrl@0_1c", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
	{ "l4-cefuse-clkctrl@0_20", TI_CLKCTRL_NO_SUB_CLOCK, 0, 0, 0, 0, 0, 0, NULL },
};

/* === ti_div_clock.c === */
PLIST(dpll_core_m4_ck_parent) = { "dpll_core_x2_ck" };
PLIST(dpll_core_m5_ck_parent) = { "dpll_core_x2_ck" };
PLIST(dpll_core_m6_ck_parent) = { "dpll_core_x2_ck" };
PLIST(dpll_mpu_m2_ck_parent) = { "dpll_mpu_ck" };
PLIST(dpll_ddr_m2_ck_parent) = { "dpll_ddr_ck" };
PLIST(dpll_disp_m2_ck_parent) = { "dpll_disp_ck" };
PLIST(dpll_per_m2_ck_parent) = { "dpll_per_ck" };
PLIST(gfx_fck_div_ck_parent) = { "gfx_fclk_clksel_ck" };
PLIST(clkout2_div_ck_parent) = { "sysclkout_pre_ck" };

static struct parent_lookup_table div_parent_table[] = {
{
	"dpll_core_m4_ck",
	nitems(dpll_core_m4_ck_parent),
	dpll_core_m4_ck_parent
},
{
	"dpll_core_m5_ck",
	nitems(dpll_core_m5_ck_parent),
	dpll_core_m5_ck_parent
},
{
	"dpll_core_m6_ck",
	nitems(dpll_core_m6_ck_parent),
	dpll_core_m6_ck_parent
},
{
	"dpll_mpu_m2_ck",
	nitems(dpll_mpu_m2_ck_parent),
	dpll_mpu_m2_ck_parent
},
{
	"dpll_ddr_m2_ck",
	nitems(dpll_ddr_m2_ck_parent),
	dpll_ddr_m2_ck_parent
},
{
	"dpll_disp_m2_ck",
	nitems(dpll_disp_m2_ck_parent),
	dpll_disp_m2_ck_parent
},
{
	"dpll_per_m2_ck",
	nitems(dpll_per_m2_ck_parent),
	dpll_per_m2_ck_parent
},
{
	"gfx_fck_div_ck",
	nitems(gfx_fck_div_ck_parent),
	gfx_fck_div_ck_parent
},
{
	"clkout2_div_ck",
	nitems(clkout2_div_ck_parent),
	clkout2_div_ck_parent
},
};

/* === ti_dpll_clock.c === */
PLIST(dpll_core_ck_parent) = { "sys_clkin_ck", "sys_clkin_ck" };
PLIST(dpll_core_x2_parent) = { "dpll_core_ck" };
 
PLIST(dpll_mpu_ck_parent) = { "sys_clkin_ck", "sys_clkin_ck" };

PLIST(dpll_ddr_ck_parent) = { "sys_clkin_ck", "sys_clkin_ck" };
PLIST(dpll_ddr_m2_div2_ck_parent) = { "dpll_ddr_m2_ck" };

PLIST(dpll_disp_ck_parent) = { "sys_clkin_ck", "sys_clkin_ck" };

PLIST(dpll_per_ck_parent) = { "sys_clkin_ck", "sys_clkin_ck" };

PLIST(dpll_per_m2_div4_wkupdm_ck_parent) = { "dpll_per_m2_ck" };
PLIST(dpll_per_m2_div4_ck_parent) = { "dpll_per_m2_ck" };

static struct parent_lookup_table dpll_parent_table[] = {
{
	"dpll_core_ck",
	nitems(dpll_core_ck_parent),
	dpll_core_ck_parent
},
{
	"dpll_core_x2_ck",
	nitems(dpll_core_x2_parent),
	dpll_core_x2_parent
},

{
	"dpll_mpu_ck",
	nitems(dpll_mpu_ck_parent),
	dpll_mpu_ck_parent
},

{
	"dpll_ddr_ck",
	nitems(dpll_ddr_ck_parent),
	dpll_ddr_ck_parent
},
{
	"dpll_ddr_m2_div2_ck",
	nitems(dpll_ddr_m2_div2_ck_parent),
	dpll_ddr_m2_div2_ck_parent
},
{
	"dpll_disp_ck",
	nitems(dpll_disp_ck_parent),
	dpll_disp_ck_parent
},

{
	"dpll_per_ck",
	nitems(dpll_per_ck_parent),
	dpll_per_ck_parent
},
{
	"dpll_per_m2_div4_wkupdm_ck",
	nitems(dpll_per_m2_div4_wkupdm_ck_parent),
	dpll_per_m2_div4_wkupdm_ck_parent
},
{
	"dpll_per_m2_div4_ck",
	nitems(dpll_per_m2_div4_ck_parent),
	dpll_per_m2_div4_ck_parent
},
};

/* === ti_gate_clock.c === */
PLIST(ehrpwm0_tbclk_parent) = { "l4ls_gclk" };
PLIST(ehrpwm1_tbclk_parent) = { "l4ls_gclk" };
PLIST(ehrpwm2_tbclk_parent) = { "l4ls_gclk" };
PLIST(mmu_fck_parent) = { "dpll_core_m4_ck" };
PLIST(usbotg_fck_parent) = { "dpll_per_ck" };
PLIST(ieee5000_fck_parent) = { "dpll_core_m4_div2_ck" };
PLIST(clkout2_ck_parent) = { "clkout2_div_ck" };

static struct parent_lookup_table gate_parent_table[] = {
{
	"ehrpwm0_tbclk",
	nitems(ehrpwm0_tbclk_parent),
	ehrpwm0_tbclk_parent
},
{
	"ehrpwm1_tbclk",
	nitems(ehrpwm1_tbclk_parent),
	ehrpwm1_tbclk_parent
},
{
	"ehrpwm2_tbclk",
	nitems(ehrpwm2_tbclk_parent),
	ehrpwm2_tbclk_parent
},
{
	"mmu_fck",
	nitems(mmu_fck_parent),
	mmu_fck_parent
},
{
	"usbotg_fck",
	nitems(usbotg_fck_parent),
	usbotg_fck_parent
},
{
	"ieee5000_fck",
	nitems(ieee5000_fck_parent),
	ieee5000_fck_parent
},
{
	"clkout2_ck",
	nitems(clkout2_ck_parent),
	clkout2_ck_parent
},
};

/* === ti_mux_clock.c === */
PLIST(sys_clkin_ck_parent) = {
	"virt_19200000_ck",
	"virt_24000000_ck",
	"virt_25000000_ck",
	"virt_26000000_ck"
};
PLIST(pruss_ocp_gclk_parent) = {
	"l3_gclk",
	"dpll_disp_m2_ck"
};
PLIST(timer1_fck_parent) = {
	"sys_clkin_ck",
	"clk-24mhz-clkctrl@14c_0",
	"tclkin_ck",
	"clk_rc32k_ck",
	"clk_32768_ck"
};
PLIST(timer2_fck_parent) = {
	"tclkin_ck",
	"sys_clkin_ck",
	"clk-24mhz-clkctrl@14c_0"
};
PLIST(timer3_fck_parent) = {
	"tclkin_ck",
	"sys_clkin_ck",
	"clk-24mhz-clkctrl@14c_0"
};
PLIST(timer4_fck_parent) = {
	"tclkin_ck",
	"sys_clkin_ck",
	"clk-24mhz-clkctrl@14c_0"
};
PLIST(timer5_fck_parent) = {
	"tclkin_ck",
	"sys_clkin_ck",
	"clk-24mhz-clkctrl@14c_0"
};
PLIST(timer6_fck_parent) = {
	"tclkin_ck",
	"sys_clkin_ck",
	"clk-24mhz-clkctrl@14c_0"
};
PLIST(timer7_fck_parent) = {
	"tclkin_ck",
	"sys_clkin_ck",
	"clk-24mhz-clkctrl@14c_0"
};
PLIST(wdt1_fck_parent) = {
	"clk_rc32k_ck",
	"clk-24mhz-clkctrl@14c_0"
};
PLIST(cpsw_cpts_tft_clk_parent) = {
	"dpll_core_m5_ck",
	"dpll_core_m4_ck"
};
PLIST(gpio0_dbclk_mux_ck_parent) = {
	"clk_rc32k_ck",
	"clk_32768_ck",
	"clk-24mhz-clkctrl@14c_0"
};
PLIST(lcd_gclk_parent) = {
	"dpll_disp_m2_ck",
	"dpll_core_m5_ck",
	"dpll_per_m2_ck"
};
PLIST(gfx_fclk_clksel_ck_parent) = {
	"dpll_core_m4_ck",
	"dpll_per_m2_ck"
};
PLIST(sysclkout_pre_ck_parent) = {
	"clk_32768_ck",
	"l3_gclk",
	"dpll_ddr_m2_ck",
	"dpll_per_m2_ck",
	"lcd_gclk"
};

static struct parent_lookup_table mux_parent_table[] =
{
{
	"sys_clkin_ck",
	nitems(sys_clkin_ck_parent),
	sys_clkin_ck_parent
},
{
	"pruss_ocp_gclk",
	nitems(pruss_ocp_gclk_parent),
	pruss_ocp_gclk_parent
},
{
	"timer1_fck",
	nitems(timer1_fck_parent),
	timer1_fck_parent
},
{
	"timer2_fck",
	nitems(timer2_fck_parent),
	timer2_fck_parent
},
{
	"timer3_fck",
	nitems(timer3_fck_parent),
	timer3_fck_parent
},
{
	"timer4_fck",
	nitems(timer4_fck_parent),
	timer4_fck_parent
},
{
	"timer5_fck",
	nitems(timer5_fck_parent),
	timer5_fck_parent
},
{
	"timer6_fck",
	nitems(timer6_fck_parent),
	timer6_fck_parent
},
{
	"timer7_fck",
	nitems(timer7_fck_parent),
	timer7_fck_parent
},
{
	"wdt1_fck",
	nitems(wdt1_fck_parent),
	wdt1_fck_parent
},
{
	"cpsw_cpts_rft_clk",
	nitems(cpsw_cpts_tft_clk_parent),
	cpsw_cpts_tft_clk_parent
},
{
	"gpio0_dbclk_mux_ck",
	nitems(gpio0_dbclk_mux_ck_parent),
	gpio0_dbclk_mux_ck_parent
},
{
	"lcd_gclk",
	nitems(lcd_gclk_parent),
	lcd_gclk_parent
},
{
	"gfx_fclk_clksel_ck",
	nitems(gfx_fclk_clksel_ck_parent),
	gfx_fclk_clksel_ck_parent
},
{
	"sysclkout_pre_ck",
	nitems(sysclkout_pre_ck_parent),
	sysclkout_pre_ck_parent
},
};

#endif /* __AM33XX_H__ */
