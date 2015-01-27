/*
 *  cpu/s3c24xx/s3c2416/cpu_init.S
 *
 *  Memory controller and cache code for U-Boot
 *
 *  Copyright (c) 2006,  Samsung Electronics
 *  All rights reserved.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * $Id: cpu_init.S,v 1.1 2008/03/31 23:21:29 boyko Exp $
 */

#include <config.h>
#include <asm/arch/clock-config.h>
#include <s3c2416.h>

/*
 * sdr_ram_asm_init: Initialize memory controller
 *
 * r0: input argument that contains memory setting value
 * r1: BANKCON1 Value
 * r2: BANKCON1 Value Modified
 * r3: Temp value
 * r4: MEMCON Base Address
 * r5-r11: setting value
 *
 */

	.globl sdr_ctrl_asm_init
sdr_ctrl_asm_init:
/* boyko : Memory Type DDR2 */
	ldr	r4, =ELFIN_MEMCTL_BASE

	/* Step 1: BANKCFG Setting */
	ldr	r2, =CFG_BANK_CFG_VAL_DDR2
	str	r2, [r4, #BANKCFG_OFFSET]

	ldr	r1, =0x44000040
	ldr	r2, =0x44000040
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 2: BANKCON2 Setting */

	ldr	r2, =CFG_BANK_CON2_VAL_DDR2
	str	r2, [r4, #BANKCON2_OFFSET]

	/* Step 3: issue PALL */
	orr	r2, r1, #INIT_PALL
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 4: Issue a EMRS2 command */
	ldr	r2, =0x80000000
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 5: Issue a EMRS3 command */
	ldr	r2, =0xc0000000
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 6: Issue a EMRS1 command */
	ldr	r2, =0x44000000
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 7: issue MRS */
	ldr	r2, =0x44000130
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_MRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 8: issue PALL */
	orr	r2, r1, #INIT_PALL
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 9: write 0xff into the refresh timer */
	mov	r3, #0xff
	str	r3, [r4, #REFRESH_OFFSET]

	/* Step 10: wait more than 120 clk */
	mov	r3, #0x100
10:	subs	r3, r3, #1
	bne	10b

	/* Step 11: issue MRS */
	ldr	r2, =0x44000030
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_MRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 12: Issue a EMRS1 command */
	ldr	r2, =0x47800030
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	ldr	r2, =0x44000030
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 13: write 0x87 into the refresh timer */
	mov	r3, #0x87
	str	r3, [r4, #REFRESH_OFFSET]

	/* Step 14: Normal Mode */
	orr	r2, r1, #INIT_NORMAL
	str	r2, [r4, #BANKCON1_OFFSET]

/* boyko : Memory Type DDR2 */

	mov	pc, lr

	.ltorg


/* Below code is for ARM920T */
	.globl cleanDCache
cleanDCache:
	mcr	p15, 0, r0, c7, c10, 2
	add	r0, r0, #(1<<5)
	tst	r0, #(1<<7)
	beq	cleanDCache
	bic	r0, r0, #(1<<7)
	adds	r0, r0, #(1<<26)

	bcc	cleanDCache
	mov	pc, lr

	.globl cleanFlushDCache
cleanFlushDCache:
	mcr	p15, 0, r0, c7, c14, 2
	add	r0, r0, #(1<<5)
	tst	r0, #(1<<7)
	beq	cleanFlushDCache
	bic	r0, r0, #(1<<7)
	adds	r0, r0, #(1<<26)

	bcc	cleanFlushDCache
	mov	pc, lr

	.globl cleanFlushCache
cleanFlushCache:
	mrc	p15, 0, pc, c7, c14, 3	/* test/cleanflush D-Cache */
	bne	cleanFlushCache
	mcr	p15, 0, r0, c7, c5, 0	/* flush I-Cache */
	mov	pc, lr

	.ltorg

