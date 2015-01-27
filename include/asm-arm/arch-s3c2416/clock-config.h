/*
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CLOCK_CONFIG_H_
#define __CLOCK_CONFIG_H_

/*-----------------------------------------------------------------------
 * Clock Configuration
 */

//#define CONFIG_CLK_534_133_66
#define CONFIG_CLK_400_133_66
//#define CONFIG_CLK_400_66_66
//#define CONFIG_CLK_267_133_66

#if defined(CONFIG_CLK_400_133_66)/* Output CLK 800MHz 2:4:8*/
#define	Startup_MDIV		400
#define	Startup_PDIV		3
#define	Startup_SDIV		1
#define Startup_EPLLSTOP	0
#define	Startup_ARMCLKdiv	1
#define	Startup_PREdiv		0x2
#define	Startup_HCLKdiv		0x1
#define	Startup_PCLKdiv		1
#elif defined(CONFIG_CLK_400_66_66)
#define	Startup_MDIV		400
#define	Startup_PDIV		3
#define	Startup_SDIV		1
#define Startup_EPLLSTOP	0
#define	Startup_ARMCLKdiv	1
#define	Startup_PREdiv		0x2
#define	Startup_HCLKdiv		0x3
#define	Startup_PCLKdiv		0
#elif defined (CONFIG_CLK_534_133_66)
#define	Startup_MDIV		267
#define	Startup_PDIV		3
#define	Startup_SDIV		1
#define Startup_EPLLSTOP	0
#define	Startup_ARMCLKdiv	0
#define	Startup_PREdiv		0x1
#define	Startup_HCLKdiv		0x1
#define	Startup_PCLKdiv		1
#elif defined (CONFIG_CLK_267_133_66)
#define	Startup_MDIV		267
#define	Startup_PDIV		3
#define	Startup_SDIV		1
#define Startup_EPLLSTOP	0
#define	Startup_ARMCLKdiv	1
#define	Startup_PREdiv		0x1
#define	Startup_HCLKdiv		0x1
#define	Startup_PCLKdiv		1
#else
# error Must define CONFIG_CLK_534_133_66 or CONFIG_CLK_400_133_66
#endif

#define CLK_DIV_VAL	((Startup_ARMCLKdiv<<9)|(Startup_PREdiv<<4)|(Startup_PCLKdiv<<2)|(Startup_HCLKdiv)|(1<<3))
#define MPLL_VAL	((Startup_EPLLSTOP<<24)|(Startup_MDIV<<14)|(Startup_PDIV<<5)|(Startup_SDIV))
#define EPLL_VAL	(32<<16)|(1<<8)|(2<<0)

#define CFG_BANK_CFG_VAL	0x0004920d
#define CFG_BANK_CON1_VAL	0x04000040
#define CFG_BANK_CFG_VAL_ALT	0x00048904
#define CFG_BANK_CON1_VAL_ALT	0x04000040
#define CFG_BANK_CFG_VAL_DDR2	0x00049253
#define CFG_BANK_CON1_VAL_DDR2	0x44000040

#define CFG_BANK_CON2_VAL	0x0057003a
#define CFG_BANK_CON2_VAL_DDR2	0x005D0035
#define CFG_BANK_CON3_VAL	0x80000030
#define CFG_BANK_REFRESH_VAL	0x00000313

#endif /* __CLOCK_CONFIG_H_ */
