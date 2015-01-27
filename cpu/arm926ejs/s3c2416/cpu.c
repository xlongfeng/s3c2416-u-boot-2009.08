/*
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#include <common.h>
#include <netdev.h>
#include <asm/cache.h>
#include <s3c2416.h>

/* See also ARM926EJ-S Technical Reference Manual */
#define C1_MMU		(1<<0)		/* mmu off/on */
#define C1_ALIGN	(1<<1)		/* alignment faults off/on */
#define C1_DC		(1<<2)		/* dcache off/on */

#define C1_BIG_ENDIAN	(1<<7)		/* big endian off/on */
#define C1_SYS_PROT	(1<<8)		/* system protection */
#define C1_ROM_PROT	(1<<9)		/* ROM protection */
#define C1_IC		(1<<12)		/* icache off/on */
#define C1_HIGH_VECTORS	(1<<13)		/* location of vectors: low/high addresses */

extern void cleanFlushDCache(void);

/* read co-processor 15, register #1 (control register) */
static unsigned long read_p15_c1 (void)
{
	unsigned long value;

	__asm__ __volatile__(
		"mrc	p15, 0, %0, c1, c0, 0   @ read control reg\n"
		: "=r" (value)
		:
		: "memory");

#ifdef MMU_DEBUG
	printf ("p15/c1 is = %08lx\n", value);
#endif
	return value;
}

/* write to co-processor 15, register #1 (control register) */
static void write_p15_c1 (unsigned long value)
{
#ifdef MMU_DEBUG
	printf ("write %08lx to p15/c1\n", value);
#endif
	__asm__ __volatile__(
		"mcr	p15, 0, %0, c1, c0, 0   @ write it back\n"
		:
		: "r" (value)
		: "memory");

	read_p15_c1 ();
}

static void cp_delay (void)
{
	volatile int i;

	/* copro seems to need some delay between reading and writing */
	for (i = 0; i < 100; i++);
}

void reset_cpu(unsigned long ignored)
{
	printf("reset... \n\n\n");

	INFORM0_REG = 0xeeee;
	WTCON_REG = 0x00000000;
	WTCNT_REG = 0x00000001;
	WTDAT_REG = 0x0;
	WTCON_REG = 0x00000021;

	/* loop forever and wait for reset to happen */
	while (1) {
		if (serial_tstc()) {
			serial_getc();
			break;
		}
	}
 	/*NOTREACHED*/
}

void icache_enable (void)
{
	ulong reg;

	reg = read_p15_c1 ();		/* get control reg. */
	cp_delay ();
	write_p15_c1 (reg | C1_IC);
}

void icache_disable (void)
{
	ulong reg;

	reg = read_p15_c1 ();
	cp_delay ();
	write_p15_c1 (reg & ~C1_IC);
}

int icache_status (void)
{
	return (read_p15_c1 () & C1_IC) != 0;
}

void dcache_enable (void)
{
	ulong reg;

	reg = read_p15_c1 ();		/* get control reg. */
	cp_delay ();
	write_p15_c1 (reg | C1_DC);
}

void dcache_disable (void)
{
	ulong reg;

	cleanFlushDCache();

	reg = read_p15_c1 ();
	cp_delay ();
	write_p15_c1 (reg & ~C1_DC);
}

int dcache_status (void)
{
	return (read_p15_c1 () & C1_DC) != 0;
}

#define MPLL 0
#define UPLL 1

/* ------------------------------------------------------------------------- */
/* NOTE: This describes the proper use of this file.
 *
 * CONFIG_SYS_CLK_FREQ should be defined as the input frequency of the PLL.
 *
 * get_FCLK(), get_HCLK(), get_PCLK() and get_UCLK() return the clock of
 * the specified bus in HZ.
 */
/* ------------------------------------------------------------------------- */

static ulong get_PLLCLK(int pllreg)
{
	ulong r, m, p, s;

	if (pllreg == MPLL)
		r = MPLLCON_REG;
#if 0
	else if (pllreg == UPLL)
		r = UPLLCON_REG;
#endif
	else
		hang();

	m = ((r>>14) & 0x3ff);
	p = ((r>>5) & 0x3f);
	s = r & 0x7;

	/* XXX: To Do calculate UPLL */

	return (m * (CONFIG_SYS_CLK_FREQ / (p << s)));
}

/* return FCLK frequency */
ulong get_FCLK(void)
{
	return(get_PLLCLK(MPLL));
}

/* return HCLK frequency */
ulong get_HCLK(void)
{
	uint hclk_div = (CLKDIV0CON_REG & 0x3) + 1;
	uint pre_div = ((CLKDIV0CON_REG>>4) & 0x3) + 1;

	return get_FCLK()/(hclk_div * pre_div);
}

/* return PCLK frequency */
ulong get_PCLK(void)
{
	return ((CLKDIV0CON_REG & 0x4) ? get_HCLK()/2 : get_HCLK());
}

/* return UCLK frequency */
ulong get_UCLK(void)
{
	return (get_PLLCLK(UPLL));
}

/* return ARMCORE frequency */
ulong get_ARMCLK(void)
{
	uint div_val = CLKDIV0CON_REG;
	uint fclk = get_FCLK();
	uint arm_clk = 0;

	switch((div_val >> 9) & 0xf) {
	case 0:
		arm_clk = fclk;
		break;

	case 1:
		arm_clk = fclk/2;
		break;

	case 2:
		arm_clk = fclk/3;
		break;

	case 3:
		arm_clk = fclk/4;
		break;

	case 5:
		arm_clk = fclk/6;
		break;

	case 7:
		arm_clk = fclk/8;
		break;

	case 13:
		arm_clk = fclk/12;
		break;

	case 15:
		arm_clk = fclk/16;
		break;

	}

	return arm_clk;
}

#if defined(CONFIG_DISPLAY_CPUINFO)
int print_cpuinfo(void)
{
	printf("CPU:   S3C2416@%dMHz, Fclk = %dMHz, Hclk = %dMHz, Pclk = %dMHz\n",
			get_ARMCLK()/1000000, get_FCLK()/1000000,
			get_HCLK()/1000000, get_PCLK()/1000000);

	return 0;
}
#endif /* CONFIG_DISPLAY_CPUINFO */

#ifdef CONFIG_ARCH_CPU_INIT
int arch_cpu_init(void)
{
	return 0;
}
#endif /* CONFIG_ARCH_CPU_INIT */

/*
 * SOC specific misc init
 */
#if defined(CONFIG_ARCH_MISC_INIT)
int arch_misc_init(void)
{
	/* sm502 smc controller initialize  */
	/* Bank2 Idle cycle ctrl. */
	SMBIDCYR2_REG = 0xf;
	/* Read Wait State cont. = 14 clk          Tacc? */
	SMBWSTRDR2_REG = 0x14;
	/* Write Wait State ctrl. */
	SMBWSTWRR2_REG = 0x14;
	/* Output Enable Assertion Delay ctrl.     Tcho? */
	SMBWSTOENR2_REG = 2;
	/* Write Enable Assertion Delay ctrl. */
	SMBWSTWENR2_REG = 2;
	/* SMWAIT active High, Read Byte Lane Enabl      WS1? */
	SMBCR2_REG = (0x2<<22)|(1<<17)|(1<<15)|(1<<9)|(1<<7)|(1<<4)|(1<<2)|(1<< 0)|(1<<21)|(1<<13);

	/* smc911x smc controller initialize */
        /* Idle cycle ctrl. */
	SMBIDCYR3_REG = 0xf;
        /* Read Wait State cont. = 14 clk          Tacc? */
	SMBWSTRDR3_REG = 12;
        /* Write Wait State ctrl. */
	SMBWSTWRR3_REG = 12;
        /* Output Enable Assertion Delay ctrl.     Tcho? */
	SMBWSTOENR3_REG = 2;
        /* Write Enable Assertion Delay ctrl. */
	SMBWSTWENR3_REG = 2;
        /* SMWAIT active High, Read Byte Lane Enabl      WS1? */
	SMBCR3_REG = (1<<17)|(1<<15)|(1<<7)|(1<<4)|(1<<21)|(1<<13);

	return 0;
}
#endif /* CONFIG_ARCH_MISC_INIT */
