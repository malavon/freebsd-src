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

#ifndef __TI_CLOCK_COMMON_H__
#define __TI_CLOCK_COMMON_H__

#include <sys/cdefs.h>
struct parent_lookup_table {
        const char      *node_name;
	int		parent_cnt;
	const char	**parent_names;
};

/* sub clock types */
#define TI_CLKCTRL_GATE		0x3
#define TI_CLKCTRL_MUX          0x2
#define TI_CLKCTRL_DIVIDER      0x1
#define TI_CLKCTRL_NO_SUB_CLOCK	0x0

/* flags */
#define TI_CLKCTRL_FLAGS_MM_HW  0x1
#define TI_CLKCTRL_FLAGS_MM_SW  0x2

struct ti_clkctrl_lookup_table {
        const char      *node_name;
        uint8_t         clk_type;
        /* clk_gate/mux/div_def */
        uint32_t        shift;
        uint32_t        mask;
	uint8_t		flags;
        uint32_t        offset;
        /* clknode_init_def */
	int		id_subclock; /* id = offset + id_subclock */
        int             parent_cnt;
        const char      **parents;
};


/* From rk3399_cru.c & rk_cru.c */
#define PLIST(x) static const char *x[]

#define LINK(_name)						\
{								\
	.clkdef.id = 0,						\
	.clkdef.name = _name,					\
	.clkdef.parent_names = NULL,				\
	.clkdef.parent_cnt = 0,					\
	.clkdef.flags = CLK_NODE_STATIC_STRINGS,		\
}
#endif /* __TI_CLOCK_COMMON_H__ */
