/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
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

#include <common.h>
#include <net.h>
#include <s3c2416.h>

DECLARE_GLOBAL_DATA_PTR;

#define FCLK_SPEED 1

#if FCLK_SPEED==0		/* Fout = 203MHz, Fin = 12MHz for Audio */
#define M_MDIV	0xC3
#define M_PDIV	0x4
#define M_SDIV	0x1
#elif FCLK_SPEED==1		/* Fout = 202.8MHz */
#define M_MDIV	0xA1
#define M_PDIV	0x3
#define M_SDIV	0x1
#endif

#define USB_CLOCK 1

#if USB_CLOCK==0
#define U_M_MDIV	0xA1
#define U_M_PDIV	0x3
#define U_M_SDIV	0x1
#elif USB_CLOCK==1
#define U_M_MDIV	0x48
#define U_M_PDIV	0x3
#define U_M_SDIV	0x2
#endif

static inline void delay (unsigned long loops)
{
	__asm__ volatile ("1:\n"
	  "subs %0, %1, #1\n"
	  "bne 1b":"=r" (loops):"0" (loops));
}

/*
 * Miscellaneous platform dependent initialisations
 */

int board_init (void)
{
	S3C24X0_CLOCK_POWER * const clk_power = S3C24X0_GetBase_CLOCK_POWER();
	S3C24X0_GPIO * const gpio = S3C24X0_GetBase_GPIO();
	S3C24X0_REG32 con;
	S3C24X0_REG32 dat;
	S3C24X0_REG32 up;

	/* set up the I/O ports */
	/* set front pannel state led on */
	con = gpio->GPKCON;
	con &= ~(0x03 << (15 * 2));
	con |= (0x01 << (15 * 2));
	gpio->GPKCON = con;
	gpio->GPKDAT |= (0x01 << 15);

	/* set externed chips power on */
	con = gpio->GPGCON;
	con &= ~(0x03 << (5 * 2));
	con |= (0x01 << (5 * 2));
	gpio->GPGCON = con;
	gpio->GPGDAT |= (0x01 << 5);

	/* enable SN75LVDS84A */
	gpio->GPACON &= ~(0x01 << 16);
	gpio->GPADAT |= (0x01 << 16);

	/* set sm502 power on */
	con = gpio->GPFCON;
	con &= ~(0x03 << (2 * 2));
	con |= (0x01 << (2 * 2));
	gpio->GPFCON = con;
	gpio->GPFDAT |= (0x01 << 2);

	/* mute nurse call */
	con = gpio->GPBCON;
	con &= ~(0x03 << (3 * 2));
	con |= (0x01 << (3 * 2));
	gpio->GPBCON = con;
	gpio->GPBDAT &= ~(0x01 << 3);

	/* Set keyboard backlight on */
	con = gpio->GPKCON;
	con &= ~(0x03 << (6 * 2));
	con |= (0x01 << (6 * 2));
	gpio->GPKCON = con;
	gpio->GPKDAT |= (0x01 << 6);

	/* Set fan power on */
	con = gpio->GPHCON;
	con &= ~(0x03 << (13 * 2));
	con |= (0x01 << (13 * 2));
	gpio->GPHCON = con;
	gpio->GPHDAT |= (0x01 << 13);

	/* alarm LED all on (GPK7,8,9) */
	con = gpio->GPKCON;
	con &= ~((0x03 << (7 * 2)) | (0x03 << (8 * 2)) | (0x03 << (9 * 2)));
	con |= ((0x01 << (7 * 2)) | (0x01 << (8 * 2)) | (0x01 << (9 * 2)));
	gpio->GPKCON = con;
	gpio->GPKDAT |= ((0x01 << 7) | (0x01 << 8) | (0x01 << 9));

	/* nRSTOUT */
	gpio->GPACON &= ~(0x01 << 21);
	gpio->GPADAT &= ~(0x01 << 21);
	delay(1000000);
	delay(1000000);
	delay(1000000);
	delay(1000000);
	gpio->GPADAT |= (0x01 << 21);

	/* arch number of Vitas2-Board */
	gd->bd->bi_arch_number = MACH_TYPE_SMDK2416;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = (PHYS_SDRAM_1 + 0x100);

	icache_enable();
	dcache_enable();

	green_LED_on();

	return 0;
}

int dram_init (void)
{
	volatile int result;
	volatile int *address = (volatile int *)PHYS_SDRAM_2;
	int sample = 0x24564236;

	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	*address = sample;
	asm ("nop;nop;nop;nop;nop;nop");
	result = *address;
	asm ("nop;nop;nop;nop;nop;nop");
	if (sample == result) {
		gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
		gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
	} else {
		gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
		gd->bd->bi_dram[1].size = 0;
	}

	return 0;
}

#ifdef CONFIG_NET_MULTI
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_SMC911X
	rc = smc911x_initialize(0, CONFIG_SMC911X_BASE);
#endif
	return rc;
}
#endif
