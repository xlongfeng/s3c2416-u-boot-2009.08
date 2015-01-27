/*
 * Memory Setup stuff - taken from blob memsetup.S
 *
 * Copyright (C) 1999 2000 2001 Erik Mouw (J.A.K.Mouw@its.tudelft.nl) and
 *                     Jan-Derk Bakker (J.D.Bakker@its.tudelft.nl)
 *
 * Modified for the VITAS2416 by
 * (C) Copyright 2015
 * xlongfeng <xlongfeng@126.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */


#include <config.h>
#include <version.h>
#include <asm/arch/clock-config.h>
#include <s3c2416.h>


_TEXT_BASE:
	.word	TEXT_BASE

	.globl lowlevel_init
lowlevel_init:

	/* perserve link reg across call */
	mov	ip, lr

	/*
	 * Retention IO power will be turen off whel sleep mode,
	 * but, when wakeup process starts, User should write '1'
	 * produce power on retention IO. PM check
	 */
	ldr	r0, =0x4c00006c
	ldr	r1, =0x4c000064
	ldr	r2, [r0]
	tst 	r2, #0x8

	ldreq	r2, [r1]
	orreq	r2, r2, #0x10000  /* (1<<16) */
	streq	r2, [r1]

	/* Power Down SDRAM Control Register */
	/* Power Down SRAM Control Register */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r1, =0x5451100
	str	r1, [r0, #0x118]

	/* Set system wide power off (GPA15), GPA16 output, */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, [r0, #GPACON_OFFSET]
	ldr	r1, =0x1019000
	bic	r2, r1
	str	r2, [r0, #GPACON_OFFSET]
	ldr	r2, [r0, #GPADAT_OFFSET]
	bic	r2, r1
	/* ldr	r1, =0x4000 */
	/* orr	r2, r2, r1 */
	str	r2, [r0, #GPADAT_OFFSET]

	/* Set GPB[1,2,3,9] output, GPB[0,4,5,10] input */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, =0x140054
	str	r2, [r0, #GPBCON_OFFSET]
	ldr	r2, =0x00000000
	str	r2, [r0, #GPBDAT_OFFSET]

	/* hardware Watchdog reset GPB2 */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, [r0, #GPBDAT_OFFSET]
	eor	r2, r2, #0x04
	str	r2, [r0, #GPBDAT_OFFSET]

	/* Set GPC port */
#if 0
	/* LED on to show U-Boot code is running */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, [r0, #GPCCON_OFFSET]
	bic	r2, #3
	orr	r1, r2, #1
	str	r1, [r0, #GPCCON_OFFSET]

	ldr	r2, [r0, #GPCDAT_OFFSET]
	bic	r2, #1
	orr	r1, r2, #1
	str	r1, [r0, #GPCDAT_OFFSET]
#endif

	/* Set GPD port */
	/* Set GPE port */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, =0x400000
	str	r2, [r0, #GPECON_OFFSET]
	ldr	r2, =0x00
	str	r2, [r0, #GPEDAT_OFFSET]
	/* Set GPF port */
	/* Set GPG port */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, =0x00
	str	r2, [r0, #GPGCON_OFFSET]
	ldr	r2, =0x08
	str	r2, [r0, #GPGPU_OFFSET]

	/* Set GPH[13,14] output */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, =0x14000000
	str	r2, [r0, #GPHCON_OFFSET]

	/* Set GPK port when using x16 bus width. */
	ldr	r2, =GPKCON_REG
	ldr	r1, =0x00000000	@ unset Sdata[31:16]
	str	r1, [r2]

	/* set keyboard background led off (GPK6) */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r1, =0x14155505
	str	r1, [r0, #GPKCON_OFFSET]
	ldr	r2, [r0, #GPKDAT_OFFSET]
	ldr	r2, =0x0
	str	r2, [r0, #GPKDAT_OFFSET]

	/* Set GPL port */
	/* Set GPM port */

	/* Disable Watchdog */
	ldr	r0, =ELFIN_WATCHDOG_BASE
	mov	r1, #0
	str	r1, [r0]

	/* Disable main and sub interrupts */
	ldr	r0, =ELFIN_INTERRUPT_BASE
	mvn	r1, #0x0
	str	r1, [r0, #INTMSK_OFFSET]
	str	r1, [r0, #INTSUBMSK_OFFSET]

	/* Set all interrupts as IRQ */
	mov	r1, #0x0
	str	r1, [r0, #INTMOD_OFFSET]

	/* init system clock */
	bl system_clock_init

#ifdef CONFIG_PM
	bl power_on_detect_asm
#endif

	/* for UART */
	bl uart_asm_init

	/* simple init for NAND */
	bl nand_asm_init

	/* set ddr2 power on */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, =0x0000
	str	r2, [r0, #GPGCON_OFFSET]
	str	r2, [r0, #GPGDAT_OFFSET]
	ldr 	r2, =0x0008
	str	r2, [r0, #GPGPU_OFFSET]

	/* wait at least 800us to stablize ddr2 power */
	mov	r3, #0x40000
10:	subs	r3, r3, #1
	bne	10b

	/* when we already run in ram, we don't need to relocate U-Boot.
	 * and actually, memory controller must be configured before U-Boot
	 * is running in ram.
	 */
	ldr	r0, =0xff000fff
	bic	r1, pc, r0		/* r0 <- current base addr of code */
	ldr	r2, _TEXT_BASE		/* r1 <- original base addr in ram */
	bic	r2, r2, r0		/* r0 <- current base addr of code */
	cmp     r1, r2                  /* compare r0, r1                  */
	beq     1f			/* r0 == r1 then skip sdram init   */

	bl sdr_ctrl_asm_init

1:	ldr	r0, =0x4f
	bl uart_asm_putc

#ifdef CONFIG_PM
	/* PM check */
	@ Check if this is a wake-up from sleep
        ldr     r0, =INFORM0_REG	/* INFORM0 register */
        ldr     r1, [r0]
        ldr     r2, =0x2BED
        cmp     r2, r1

	ldreq 	r0, =INFORM1_REG	/* INFORM1 register */
        ldreq 	r1, [r0]
        moveq 	pc, r1 			 /* end PM check */
#endif

	mov	lr, ip
	mov	pc, lr

	.globl green_LED_on
green_LED_on:
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, [r0, #GPCCON_OFFSET]
	bic	r2, #3
	orr	r1, r2, #1
	str	r1, [r0, #GPCCON_OFFSET]

	ldr	r2, [r0, #GPCDAT_OFFSET]
	orr	r1, r2, #1
	str	r1, [r0, #GPCDAT_OFFSET]
	mov	pc, lr

	.globl green_LED_off
green_LED_off:
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, [r0, #GPCCON_OFFSET]
	bic	r2, #3
	orr	r1, r2, #1
	str	r1, [r0, #GPCCON_OFFSET]

	ldr	r2, [r0, #GPCDAT_OFFSET]
	bic	r2, #1
	str	r1, [r0, #GPCDAT_OFFSET]
	mov	pc, lr

/*
 * system_clock_init: Initialize core clock and bus clock.
 * void system_clock_init(void)
 */
system_clock_init:

	ldr	r0, =ELFIN_CLOCK_POWER_BASE

	ldr	r1, [r0, #CLKDIV0CON_OFFSET]
	bic	r1, r1, #0x37	/* clear HCLKDIV, PREDIV, PCLKDIV */
	bic	r1, r1, #(0xf<<9) /* clear ARMCLKDIV */
	ldr	r2, =CLK_DIV_VAL
	orr	r1, r1, r2
	str	r1, [r0, #CLKDIV0CON_OFFSET]

	/*Set MPLL Locktime*/
	ldr	r1, =0xe10
	str	r1, [r0, #LOCKCON0_OFFSET]

	ldr	r1, =MPLL_VAL
	str	r1, [r0, #MPLLCON_OFFSET]

#if 1
	ldr	r1, =0x1780
	str	r1, [r0, #LOCKCON1_OFFSET]

	ldr	r1, =EPLL_VAL		/*Set EPLL*/
	str	r1, [r0, #EPLLCON_OFFSET]

	ldr	r1, [r0, #CLKSRCCON_OFFSET]
	orr	r1, r1, #0x40
	str	r1, [r0, #CLKSRCCON_OFFSET]

#endif

	/* set CLKSRC to fit MPLL and USB */
	ldr	r1, [r0, #CLKSRCCON_OFFSET]
	orr	r1, r1, #0x10
	str	r1, [r0, #CLKSRCCON_OFFSET]
#if 0
	/* wait at least 200us to stablize all clock */
	mov	r2, #0x10000
1:	subs	r1, r1, #1
	bne	1b
#endif

	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, r0, #0xc0000000	/* clock setting in MMU */
	mcr	p15, 0, r0, c1, c0, 0

	mov	pc, lr

	.globl power_on_detect_asm
power_on_detect_asm:

        ldr     r0, =INFORM0_REG	/* INFORM0 register */
        ldr     r1, [r0]
        ldr     r2, =0xEEEE		/* system reboot from kernel panic */
        cmp     r2, r1
	beq	1024f

        ldr     r0, =WKUPSTAT_REG	/* Wake-up status register */
        ldr     r1, [r0]
	tst	r1, #(1<<1)
	beq	1023f
	/* rtc wakeup, set inform0 & inform2 to 0xEEEE, and close ddr2 power */
	ldr     r0, =INFORM0_REG	/* INFORM0 register */
	ldr     r1, =INFORM2_REG	/* INFORM2 register */
	ldr     r2, =0x0000 		/* clear inform register */
	str     r2, [r0]
	str     r2, [r1]
	/* disable rtc alarm interrupt */
	ldr     r0, =0x57000050 	/* RTC alarm control register */
	ldr     r1, =0x00
	str     r1, [r0]

1023:
	/*
	 * initializ timer 3
	 * for 3 s clock period @ PCLK with 4 bit divider = 1/16
	 * (default) and prescaler = 256. Should be 10390
	 * @33.25MHz and 15625 @ 50 MHz and 48340 @ 66 MHz
	 * get_PCLK() * 3 / (16 * 256)
	 */
	ldr	r0, =ELFIN_TIMER_BASE
	ldr	r2, =0xff00
	str	r2, [r0, #0x00]
	ldr	r2, =0x3000
	str	r2, [r0, #0x04]
	/* ldr	r2, =0xbcd4 */
	ldr	r2, =0x3f00
	str	r2, [r0, #0x30]
	ldr	r2, =0x00060000
	str	r2, [r0, #0x08]
	ldr	r2, =0x00010000
	str	r2, [r0, #0x08]

	/* initializa ddr2 power control, and power up button */
	/* configure wakeup source, etc. */
	/* power button GPF3(EINT3) */
#if 1
	ldr 	r1, =0x0080
	ldr 	r2, =0x0000
	ldr 	r3, =0x4080
#else
	/* Check if ddr2 power is off */
	ldr     r1, =INFORM2_REG	/* INFORM2 register */
	ldr     r1, [r1]
	ldr     r2, =0xDEE9
	cmp     r2, r1
	/* set ddr2 power on */
	ldreq 	r1, =0x0000
	ldreq 	r2, =0x0000
	ldreq 	r3, =0x0008
	/* set ddr2 power off */
	ldrne 	r1, =0x0000
	ldrne 	r2, =0x0000
	ldrne 	r3, =0x0008
#endif

	ldr	r0, =ELFIN_GPIO_BASE
	str	r1, [r0, #GPGCON_OFFSET]
	str	r2, [r0, #GPGDAT_OFFSET]
	str	r3, [r0, #GPGPU_OFFSET]
	ldr 	r1, =0x0080
	ldr 	r2, =0x0000
	ldr 	r3, =0x00A0
	str	r1, [r0, #GPFCON_OFFSET]
	str	r2, [r0, #GPFDAT_OFFSET]
	str	r3, [r0, #GPFPU_OFFSET]

	ldr	r0, =ELFIN_TIMER_BASE
	ldr	r1, =ELFIN_GPIO_BASE
	/* detection of power button for 3's */
1:	ldr	r3, [r0, #0x38]
	subs	r3, r3, #0
	beq	1024f

	/* hardware Watchdog reset */
	ldr	r3, [r1, #GPBDAT_OFFSET]
	eor	r3, r3, #0x04
	str	r3, [r1, #GPBDAT_OFFSET]

	ldr	r3, [r1, #GPFDAT_OFFSET]
	tst	r3, #(1<<3)
	beq	1b

	/* system enter into sleep mode */

	/* configure smc911x */
	/* configure wm97xx */

	/* disable hardware watchdog GPB2 */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r2, =0x140044
	str	r2, [r0, #GPBCON_OFFSET]

	ldr	r2, =0x2000
	str	r2, [r0, #EINTCON0_OFFSET]

	ldr	r2, =0xffffffff
	str	r2, [r0, #EINTMASK_OFFSET]
	ldr	r2, [r0, #EINTPEND_OFFSET]
	str	r2, [r0, #EINTPEND_OFFSET]

	ldr	r1, =ELFIN_INTERRUPT_BASE
	ldr	r2, =0xffffffff
	str	r2, [r1, #INTMSK_OFFSET]
	ldr	r2, [r1, #0x00]
	str	r2, [r1, #0x00]
	ldr	r2, [r1, #0x10]
	str	r2, [r1, #0x10]

	ldr	r0, =ELFIN_CLOCK_POWER_BASE
	ldr	r2, =0xfefe
	str	r2, [r0, #RSTCON_OFFSET]
	ldr	r2, =0xffff
	str	r2, [r0, #OSCSET_OFFSET]
	ldr	r2, =0x8080
	str	r2, [r0, #PWRCFG_OFFSET]

	/* set our standby method to sleep */
	ldr	r2, =0x2bed
	str	r2, [r0, #PWRMODECON_OFFSET]

1024:
	mov	pc, lr

/*
 * uart_asm_init: Initialize UART in asm mode, 115200bps fixed.
 * void uart_asm_init(void)
 */
uart_asm_init:
	/* set GPIO to enable UART */
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r1, =0x0000aaaa
	str	r1, [r0, #GPHCON_OFFSET]    @GPIO

	ldr	r0, =ELFIN_UART_BASE
	mov	r1, #0x0
	str	r1, [r0, #UFCON_OFFSET]
	str	r1, [r0, #UMCON_OFFSET]

	mov	r1, #0x3                     @was 0.
	str	r1, [r0, #ULCON_OFFSET]

	ldr	r1, =0x245
	str	r1, [r0, #UCON_OFFSET]

	ldr 	r1, =0x3

	ldr	r1, =0x23			/* PCLK Is Fixed to 66Mhz */
	str	r1, [r0, #UBRDIV_OFFSET]

	ldr	r1, =0x0888
	str	r1, [r0, #UDIVSLOT_OFFSET]

	ldr	r1, =0x4b
	str	r1, [r0, #UTXH_OFFSET]

	mov	pc, lr

	.globl uart_asm_putc
uart_asm_putc:
	ldr	r1, =ELFIN_UART_BASE
	str	r0, [r1, #UTXH_OFFSET]

1:
	ldr     r0, [r1, #UTRSTAT_OFFSET]
	tst	r0, #(1<<2)
	beq	1b

	mov	pc, lr

/*
 * Nand Interface Init for smdk2416
 */

nand_asm_init:
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r1, [r0]
	orr	r1, r1, #(0x3f<<17)
	str     r1, [r0]
	/* EVT1 has modification in NAND */
#if 1
	ldr	r1, =0x19a8a
	str     r1, [r0, #GPADAT_OFFSET]
#endif
	ldr	r0, =ELFIN_NAND_BASE
	ldr	r1, [r0, #NFCONF_OFFSET]
	orr	r1, r1, #0x70
	orr	r1, r1, #0x7700
	str     r1, [r0, #NFCONF_OFFSET]

	ldr	r1, [r0, #NFCONT_OFFSET]
	orr	r1, r1, #0x03
	str     r1, [r0, #NFCONT_OFFSET]

	mov	pc, lr

	.ltorg
