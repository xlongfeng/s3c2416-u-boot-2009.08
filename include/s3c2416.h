/*
 * (C) Copyright 2003
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

/************************************************
 * NAME	    : s3c2416.h
 *
 * Based on S3C2410X User's manual Rev 1.1
 ************************************************/

#ifndef __S3C2416_H__
#define __S3C2416_H__

#include <asm/hardware.h>

#define S3C24X0_UART_CHANNELS	3
#define S3C24X0_SPI_CHANNELS	2

/* S3C2410 only supports 512 Byte HW ECC */
#define S3C2410_ECCSIZE		512
#define S3C2410_ECCBYTES	3

/* S3C2410 device base addresses */
#define S3C24X0_MEMCTL_BASE		0x48000000
#define S3C24X0_USB_HOST_BASE		0x49000000
#define S3C24X0_INTERRUPT_BASE		0x4A000000
#define S3C24X0_DMA_BASE		0x4B000000
#define S3C24X0_CLOCK_POWER_BASE	0x4C000000
#define S3C24X0_LCD_BASE		0x4D000000
#define S3C2410_NAND_BASE		0x4E000000
#define S3C24X0_UART_BASE		0x50000000
#define S3C24X0_TIMER_BASE		0x51000000
#define S3C24X0_USB_DEVICE_BASE		0x52000140
#define S3C24X0_WATCHDOG_BASE		0x53000000
#define S3C24X0_I2C_BASE		0x54000000
#define S3C24X0_I2S_BASE		0x55000000
#define S3C24X0_GPIO_BASE		0x56000000
#define S3C24X0_RTC_BASE		0x57000000
#define S3C2410_ADC_BASE		0x58000000
#define S3C24X0_SPI_BASE		0x59000000
#define S3C2410_SDI_BASE		0x5A000000


/* include common stuff */
#include <s3c24x0.h>

#ifndef __ASSEMBLY__

typedef enum {
	S3C24X0_UART0,
	S3C24X0_UART1,
	S3C24X0_UART2
} S3C24X0_UARTS_NR;

static inline S3C24X0_MEMCTL * S3C24X0_GetBase_MEMCTL(void)
{
	return (S3C24X0_MEMCTL * const)S3C24X0_MEMCTL_BASE;
}
static inline S3C24X0_USB_HOST * S3C24X0_GetBase_USB_HOST(void)
{
	return (S3C24X0_USB_HOST * const)S3C24X0_USB_HOST_BASE;
}
static inline S3C24X0_INTERRUPT * S3C24X0_GetBase_INTERRUPT(void)
{
	return (S3C24X0_INTERRUPT * const)S3C24X0_INTERRUPT_BASE;
}
static inline S3C24X0_DMAS * S3C24X0_GetBase_DMAS(void)
{
	return (S3C24X0_DMAS * const)S3C24X0_DMA_BASE;
}
static inline S3C24X0_CLOCK_POWER * S3C24X0_GetBase_CLOCK_POWER(void)
{
	return (S3C24X0_CLOCK_POWER * const)S3C24X0_CLOCK_POWER_BASE;
}
static inline S3C24X0_LCD * S3C24X0_GetBase_LCD(void)
{
	return (S3C24X0_LCD * const)S3C24X0_LCD_BASE;
}
static inline S3C2410_NAND * S3C2410_GetBase_NAND(void)
{
	return (S3C2410_NAND * const)S3C2410_NAND_BASE;
}
static inline S3C24X0_UART * S3C24X0_GetBase_UART(S3C24X0_UARTS_NR nr)
{
	return (S3C24X0_UART * const)(S3C24X0_UART_BASE + (nr * 0x4000));
}
static inline S3C24X0_TIMERS * S3C24X0_GetBase_TIMERS(void)
{
	return (S3C24X0_TIMERS * const)S3C24X0_TIMER_BASE;
}
static inline S3C24X0_USB_DEVICE * S3C24X0_GetBase_USB_DEVICE(void)
{
	return (S3C24X0_USB_DEVICE * const)S3C24X0_USB_DEVICE_BASE;
}
static inline S3C24X0_WATCHDOG * S3C24X0_GetBase_WATCHDOG(void)
{
	return (S3C24X0_WATCHDOG * const)S3C24X0_WATCHDOG_BASE;
}
static inline S3C24X0_I2C * S3C24X0_GetBase_I2C(void)
{
	return (S3C24X0_I2C * const)S3C24X0_I2C_BASE;
}
static inline S3C24X0_I2S * S3C24X0_GetBase_I2S(void)
{
	return (S3C24X0_I2S * const)S3C24X0_I2S_BASE;
}
static inline S3C24X0_GPIO * S3C24X0_GetBase_GPIO(void)
{
	return (S3C24X0_GPIO * const)S3C24X0_GPIO_BASE;
}
static inline S3C24X0_RTC * S3C24X0_GetBase_RTC(void)
{
	return (S3C24X0_RTC * const)S3C24X0_RTC_BASE;
}
static inline S3C2410_ADC * S3C2410_GetBase_ADC(void)
{
	return (S3C2410_ADC * const)S3C2410_ADC_BASE;
}
static inline S3C24X0_SPI * S3C24X0_GetBase_SPI(void)
{
	return (S3C24X0_SPI * const)S3C24X0_SPI_BASE;
}
static inline S3C2410_SDI * S3C2410_GetBase_SDI(void)
{
	return (S3C2410_SDI * const)S3C2410_SDI_BASE;
}

#endif

/* ISR */
#define pISR_RESET		(*(unsigned *)(_ISR_STARTADDRESS+0x0))
#define pISR_UNDEF		(*(unsigned *)(_ISR_STARTADDRESS+0x4))
#define pISR_SWI		(*(unsigned *)(_ISR_STARTADDRESS+0x8))
#define pISR_PABORT		(*(unsigned *)(_ISR_STARTADDRESS+0xC))
#define pISR_DABORT		(*(unsigned *)(_ISR_STARTADDRESS+0x10))
#define pISR_RESERVED		(*(unsigned *)(_ISR_STARTADDRESS+0x14))
#define pISR_IRQ		(*(unsigned *)(_ISR_STARTADDRESS+0x18))
#define pISR_FIQ		(*(unsigned *)(_ISR_STARTADDRESS+0x1C))

#define pISR_EINT0		(*(unsigned *)(_ISR_STARTADDRESS+0x20))
#define pISR_EINT1		(*(unsigned *)(_ISR_STARTADDRESS+0x24))
#define pISR_EINT2		(*(unsigned *)(_ISR_STARTADDRESS+0x28))
#define pISR_EINT3		(*(unsigned *)(_ISR_STARTADDRESS+0x2C))
#define pISR_EINT4_7		(*(unsigned *)(_ISR_STARTADDRESS+0x30))
#define pISR_EINT8_23		(*(unsigned *)(_ISR_STARTADDRESS+0x34))
#define pISR_BAT_FLT		(*(unsigned *)(_ISR_STARTADDRESS+0x3C))
#define pISR_TICK		(*(unsigned *)(_ISR_STARTADDRESS+0x40))
#define pISR_WDT		(*(unsigned *)(_ISR_STARTADDRESS+0x44))
#define pISR_TIMER0		(*(unsigned *)(_ISR_STARTADDRESS+0x48))
#define pISR_TIMER1		(*(unsigned *)(_ISR_STARTADDRESS+0x4C))
#define pISR_TIMER2		(*(unsigned *)(_ISR_STARTADDRESS+0x50))
#define pISR_TIMER3		(*(unsigned *)(_ISR_STARTADDRESS+0x54))
#define pISR_TIMER4		(*(unsigned *)(_ISR_STARTADDRESS+0x58))
#define pISR_UART2		(*(unsigned *)(_ISR_STARTADDRESS+0x5C))
#define pISR_NOTUSED		(*(unsigned *)(_ISR_STARTADDRESS+0x60))
#define pISR_DMA0		(*(unsigned *)(_ISR_STARTADDRESS+0x64))
#define pISR_DMA1		(*(unsigned *)(_ISR_STARTADDRESS+0x68))
#define pISR_DMA2		(*(unsigned *)(_ISR_STARTADDRESS+0x6C))
#define pISR_DMA3		(*(unsigned *)(_ISR_STARTADDRESS+0x70))
#define pISR_SDI		(*(unsigned *)(_ISR_STARTADDRESS+0x74))
#define pISR_SPI0		(*(unsigned *)(_ISR_STARTADDRESS+0x78))
#define pISR_UART1		(*(unsigned *)(_ISR_STARTADDRESS+0x7C))
#define pISR_USBD		(*(unsigned *)(_ISR_STARTADDRESS+0x84))
#define pISR_USBH		(*(unsigned *)(_ISR_STARTADDRESS+0x88))
#define pISR_IIC		(*(unsigned *)(_ISR_STARTADDRESS+0x8C))
#define pISR_UART0		(*(unsigned *)(_ISR_STARTADDRESS+0x90))
#define pISR_SPI1		(*(unsigned *)(_ISR_STARTADDRESS+0x94))
#define pISR_RTC		(*(unsigned *)(_ISR_STARTADDRESS+0x98))
#define pISR_ADC		(*(unsigned *)(_ISR_STARTADDRESS+0xA0))


/* PENDING BIT */
#define BIT_EINT0		(0x1)
#define BIT_EINT1		(0x1<<1)
#define BIT_EINT2		(0x1<<2)
#define BIT_EINT3		(0x1<<3)
#define BIT_EINT4_7		(0x1<<4)
#define BIT_EINT8_23		(0x1<<5)
#define BIT_BAT_FLT		(0x1<<7)
#define BIT_TICK		(0x1<<8)
#define BIT_WDT			(0x1<<9)
#define BIT_TIMER0		(0x1<<10)
#define BIT_TIMER1		(0x1<<11)
#define BIT_TIMER2		(0x1<<12)
#define BIT_TIMER3		(0x1<<13)
#define BIT_TIMER4		(0x1<<14)
#define BIT_UART2		(0x1<<15)
#define BIT_LCD			(0x1<<16)
#define BIT_DMA0		(0x1<<17)
#define BIT_DMA1		(0x1<<18)
#define BIT_DMA2		(0x1<<19)
#define BIT_DMA3		(0x1<<20)
#define BIT_SDI			(0x1<<21)
#define BIT_SPI0		(0x1<<22)
#define BIT_UART1		(0x1<<23)
#define BIT_USBD		(0x1<<25)
#define BIT_USBH		(0x1<<26)
#define BIT_IIC			(0x1<<27)
#define BIT_UART0		(0x1<<28)
#define BIT_SPI1		(0x1<<29)
#define BIT_RTC			(0x1<<30)
#define BIT_ADC			(0x1<<31)
#define BIT_ALLMSK		(0xFFFFFFFF)

#define ClearPending(bit) {\
		 rSRCPND = bit;\
		 rINTPND = bit;\
		 rINTPND;\
		 }
/* Wait until rINTPND is changed for the case that the ISR is very short. */

/*
 * Memory controller
 */

#define ELFIN_SROM_BASE		0x40c20000

#define SROM_BW_REG		__REG(0x40C20000)
#define SROM_BC0_REG		__REG(0x40C20004)
#define SROM_BC1_REG		__REG(0x40C20008)
#define SROM_BC2_REG		__REG(0x40C2000C)

/*
 * Clock and power management
 */
#define ELFIN_CLOCK_POWER_BASE	0x4c000000

/* Clock & Power Controller */
#define LOCKCON0_OFFSET		0x00
#define LOCKCON1_OFFSET		0x04
#define OSCSET_OFFSET		0x08
#define MPLLCON_OFFSET		0x10
#define EPLLCON_OFFSET		0x18
#define CLKSRCCON_OFFSET	0x20
#define CLKDIV0CON_OFFSET	0x24
#define CLKDIV1CON_OFFSET	0x28
#define HCLKCON_OFFSET		0x30
#define PCLKCON_OFFSET		0x34
#define SCLKCON_OFFSET		0x38
#define PWRMODECON_OFFSET	0x40
#define SWRSTCON_OFFSET		0x44
#define BUSPRI0_OFFSET		0x50
#define BUS_MISC_OFFSET		0x58
#define SYSID_OFFSET		0x5c
#define PWRCFG_OFFSET		0x60
#define RSTCON_OFFSET		0x64
#define RSTSTAT_OFFSET		0x68
#define WKUPSTAT_OFFSET		0x6c
#define INFORM0_OFFSET		0x70
#define INFORM1_OFFSET		0x74
#define INFORM2_OFFSET		0x78
#define INFORM3_OFFSET		0x7c
#define USB_PHYCTRL_OFFSET	0x80
#define USB_PHYPWR_OFFSET	0x84
#define USB_RSTCON_OFFSET	0x88
#define USB_CLKCON_OFFSET	0x8c
#define USB_TESTTI_OFFSET	0x90
#define USB_TESTTO_OFFSET	0x94

#define LOCKCON0_REG		__REG(0x4c000000)
#define LOCKCON1_REG		__REG(0x4c000004)
#define OSCSET_REG		__REG(0x4c000008)
#define MPLLCON_REG		__REG(0x4c000010)
#define EPLLCON_REG		__REG(0x4c000018)
#define CLKSRCCON_REG		__REG(0x4c000020)
#define CLKDIV0CON_REG		__REG(0x4c000024)
#define CLKDIV1CON_REG		__REG(0x4c000028)
#define HCLKCON_REG		__REG(0x4c000030)
#define PCLKCON_REG		__REG(0x4c000034)
#define SCLKCON_REG		__REG(0x4c000038)
#define PWRMODECON_REG		__REG(0x4c000040)
#define SWRSTCON_REG		__REG(0x4c000044)
#define BUSPRI0_REG		__REG(0x4c000050)
#define BUS_MISC_REG		__REG(0x4c000058)
#define SYSID_REG		__REG(0x4c00005c)
#define PWRCFG_REG		__REG(0x4c000060)
#define RSTCON_REG		__REG(0x4c000064)
#define RSTSTAT_REG		__REG(0x4c000068)
#define WKUPSTAT_REG		__REG(0x4c00006c)
#define INFORM0_REG		__REG(0x4c000070)
#define INFORM1_REG		__REG(0x4c000074)
#define INFORM2_REG		__REG(0x4c000078)
#define INFORM3_REG		__REG(0x4c00007c)
#define USB_PHYCTRL_REG		__REG(0x4c000080)
#define USB_PHYPWR_REG		__REG(0x4c000084)
#define USB_RSTCON_REG		__REG(0x4c000088)
#define USB_CLKCON_REG		__REG(0x4c00008c)
#define USB_TESTTI_REG		__REG(0x4c000090)
#define USB_TESTTO_REG		__REG(0x4c000094)

/*
 * SSMC
 */
#define SMBIDCYR0_REG		__REG(0x4F000000)
#define SMBIDCYR1_REG		__REG(0x4F000020)
#define SMBIDCYR2_REG		__REG(0x4F000040)
#define SMBIDCYR3_REG		__REG(0x4F000060)
#define SMBIDCYR4_REG		__REG(0x4F000080)
#define SMBIDCYR5_REG		__REG(0x4F0000A0)

#define SMBWSTRDR0_REG		__REG(0x4F000004)
#define SMBWSTRDR1_REG		__REG(0x4F000024)
#define SMBWSTRDR2_REG		__REG(0x4F000044)
#define SMBWSTRDR3_REG		__REG(0x4F000064)
#define SMBWSTRDR4_REG		__REG(0x4F000084)
#define SMBWSTRDR5_REG		__REG(0x4F0000A4)

#define SMBWSTWRR0_REG		__REG(0x4F000008)
#define SMBWSTWRR1_REG		__REG(0x4F000028)
#define SMBWSTWRR2_REG		__REG(0x4F000048)
#define SMBWSTWRR3_REG		__REG(0x4F000068)
#define SMBWSTWRR4_REG		__REG(0x4F000088)
#define SMBWSTWRR5_REG		__REG(0x4F0000A8)

#define SMBWSTOENR0_REG 	__REG(0x4F00000C)
#define SMBWSTOENR1_REG 	__REG(0x4F00002C)
#define SMBWSTOENR2_REG 	__REG(0x4F00004C)
#define SMBWSTOENR3_REG 	__REG(0x4F00006C)
#define SMBWSTOENR4_REG 	__REG(0x4F00008C)
#define SMBWSTOENR5_REG 	__REG(0x4F0000AC)

#define SMBWSTWENR0_REG		__REG(0x4F000010)
#define SMBWSTWENR1_REG		__REG(0x4F000030)
#define SMBWSTWENR2_REG		__REG(0x4F000050)
#define SMBWSTWENR3_REG 	__REG(0x4F000070)
#define SMBWSTWENR4_REG 	__REG(0x4F000090)
#define SMBWSTWENR5_REG 	__REG(0x4F0000B0)

#define SMBCR0_REG		__REG(0x4F000014)
#define SMBCR1_REG		__REG(0x4F000034)
#define SMBCR2_REG		__REG(0x4F000054)
#define SMBCR3_REG		__REG(0x4F000074)
#define SMBCR4_REG		__REG(0x4F000094)
#define SMBCR5_REG		__REG(0x4F0000B4)

#define SMBSR0_REG		__REG(0x4F000018)
#define SMBSR1_REG		__REG(0x4F000038)
#define SMBSR2_REG		__REG(0x4F000058)
#define SMBSR3_REG		__REG(0x4F000078)
#define SMBSR4_REG		__REG(0x4F000098)
#define SMBSR5_REG		__REG(0x4F0000B8)

#define SMBWSTBDR0_REG		__REG(0x4F00001C)
#define SMBWSTBDR1_REG		__REG(0x4F00003C)
#define SMBWSTBDR2_REG		__REG(0x4F00005C)
#define SMBWSTBDR3_REG		__REG(0x4F00007C)
#define SMBWSTBDR4_REG		__REG(0x4F00009C)
#define SMBWSTBDR5_REG		__REG(0x4F0000BC)

#define SSMCSR_REG		__REG(0x4F000200)
#define SSMCCR_REG		__REG(0x4F000204)

/*
 * SDRAM Controller
 */

#define ELFIN_MEMCTL_BASE	0x48000000
#define BANKCFG_OFFSET		0x00
#define BANKCON1_OFFSET		0x04
#define BANKCON2_OFFSET		0x08
#define BANKCON3_OFFSET		0x0c
#define REFRESH_OFFSET		0x10
#define TIMEOUT_OFFSET		0x14

#define INIT_NORMAL		0x0
#define INIT_PALL		0x1
#define INIT_MRS		0x2
#define INIT_EMRS		0x3
#define INIT_MASK		0x3

/*
 * EBI(External Bus Interface)
 */
#define EBIPR_REG		__REG(0x48800000)
#define BANK_CFG_REG		__REG(0x48800004)

/*
 * Interrupt
 */
#define ELFIN_INTERRUPT_BASE	0x4a000000

#define INTMSK_OFFSET		0x08
#define INTSUBMSK_OFFSET	0x1c
#define INTMOD_OFFSET		0x04

#define SRCPND_REG		__REG(0x4a000000)
#define INTMOD_REG		__REG(0x4a000004)
#define INTMSK_REG		__REG(0x4a000008)
#define INTPND_REG		__REG(0x4a000010)
#define INTOFFSET_REG		__REG(0x4a000014)
#define SUBSRCPND_REG		__REG(0x4a000018)
#define INTSUBMSK_REG		__REG(0x4a00001C)
#define SUBSRCPND2_REG		__REG(0x4a000030)
#define INTSUBMSK2_REG		__REG(0x4a000034)
#define PRIORITY_MODE_REG	__REG(0x4a000038)
#define PRIORITY_UPDATE_REG	__REG(0x4a00003c)

/*
 * Nand flash controller
 */

#define ELFIN_NAND_BASE		0x4e000000

#define NFCONF_OFFSET		0x00
#define NFCONT_OFFSET		0x04
#define NFCMMD_OFFSET		0x08
#define NFADDR_OFFSET		0x0c
#define NFDATA_OFFSET		0x10
#define NFMECCDATA0_OFFSET	0x14
#define NFMECCDATA1_OFFSET	0x18
#define NFSECCDATA0_OFFSET	0x1c
#define NFSBLK_OFFSET		0x20
#define NFEBLK_OFFSET		0x24
#define NFSTAT_OFFSET		0x28
#define NFESTAT0_OFFSET		0x2c
#define NFESTAT1_OFFSET		0x30
#define NFMECC0_OFFSET		0x34
#define NFMECC1_OFFSET		0x38
#define NFSECC_OFFSET		0x3c

#define NFCONF			(ELFIN_NAND_BASE + NFCONF_OFFSET)
#define NFCONT			(ELFIN_NAND_BASE + NFCONT_OFFSET)
#define NFCMMD			(ELFIN_NAND_BASE + NFCMMD_OFFSET)
#define NFADDR			(ELFIN_NAND_BASE + NFADDR_OFFSET)
#define NFDATA			(ELFIN_NAND_BASE + NFDATA_OFFSET)
#define NFMECCDATA0		(ELFIN_NAND_BASE + NFMECCDATA0_OFFSET)
#define NFMECCDATA1		(ELFIN_NAND_BASE + NFMECCDATA1_OFFSET)
#define NFSECCDATA0		(ELFIN_NAND_BASE + NFSECCDATA0_OFFSET)
#define NFSBLK			(ELFIN_NAND_BASE + NFSBLK_OFFSET)
#define NFEBLK			(ELFIN_NAND_BASE + NFEBLK_OFFSET)
#define NFSTAT			(ELFIN_NAND_BASE + NFSTAT_OFFSET)
#define NFESTAT0		(ELFIN_NAND_BASE + NFESTAT0_OFFSET)
#define NFESTAT1		(ELFIN_NAND_BASE + NFESTAT1_OFFSET)
#define NFMECC0			(ELFIN_NAND_BASE + NFMECC0_OFFSET)
#define NFMECC1			(ELFIN_NAND_BASE + NFMECC1_OFFSET)
#define NFSECC			(ELFIN_NAND_BASE + NFSECC_OFFSET)
#define NFMLCBITPT		(ELFIN_NAND_BASE + NFMLCBITPT_OFFSET)

#define NFCONF_REG		__REG(ELFIN_NAND_BASE + NFCONF_OFFSET)
#define NFCONT_REG		__REG(ELFIN_NAND_BASE + NFCONT_OFFSET)
#define NFCMD_REG		__REG(ELFIN_NAND_BASE + NFCMMD_OFFSET)
#define NFADDR_REG		__REG(ELFIN_NAND_BASE + NFADDR_OFFSET)
#define NFDATA_REG		__REG(ELFIN_NAND_BASE + NFDATA_OFFSET)
#define NFDATA8_REG		__REGb(ELFIN_NAND_BASE + NFDATA_OFFSET)
#define NFMECCDATA0_REG		__REG(ELFIN_NAND_BASE + NFMECCDATA0_OFFSET)
#define NFMECCDATA1_REG		__REG(ELFIN_NAND_BASE + NFMECCDATA1_OFFSET)
#define NFSECCDATA0_REG		__REG(ELFIN_NAND_BASE + NFSECCDATA0_OFFSET)
#define NFSBLK_REG		__REG(ELFIN_NAND_BASE + NFSBLK_OFFSET)
#define NFEBLK_REG		__REG(ELFIN_NAND_BASE + NFEBLK_OFFSET)
#define NFSTAT_REG		__REG(ELFIN_NAND_BASE + NFSTAT_OFFSET)
#define NFESTAT0_REG		__REG(ELFIN_NAND_BASE + NFESTAT0_OFFSET)
#define NFESTAT1_REG		__REG(ELFIN_NAND_BASE + NFESTAT1_OFFSET)
#define NFMECC0_REG		__REG(ELFIN_NAND_BASE + NFMECC0_OFFSET)
#define NFMECC1_REG		__REG(ELFIN_NAND_BASE + NFMECC1_OFFSET)
#define NFSECC_REG		__REG(ELFIN_NAND_BASE + NFSECC_OFFSET)
#define NFMLCBITPT_REG		__REG(ELFIN_NAND_BASE + NFMLCBITPT_OFFSET)

#define NFCONF_ECC_4BIT		(1<<24)

#define NFCONT_ECC_ENC		(1<<18)
#define NFCONT_WP		(1<<16)
#define NFCONT_MECCLOCK		(1<<7)
#define NFCONT_SECCLOCK		(1<<6)
#define NFCONT_INITMECC		(1<<5)
#define NFCONT_INITSECC		(1<<4)
#define NFCONT_INITECC		(NFCONT_INITMECC | NFCONT_INITSECC)
#define NFCONT_CS_ALT		(1<<2)
#define NFCONT_CS		(1<<1)
#define NFCONT_ENABLE		(1<<0)

#define NFSTAT_ECCENCDONE	(1<<7)
#define NFSTAT_ECCDECDONE	(1<<6)
#define NFSTAT_RnB		(1<<0)

#define NFESTAT0_ECCBUSY	(1<<31)

/*
 * UART
 */
#define ELFIN_UART_BASE	0x50000000

#define ULCON0_REG		__REG(0x50000000)
#define UCON0_REG		__REG(0x50000004)
#define UFCON0_REG		__REG(0x50000008)
#define UMCON0_REG		__REG(0x5000000C)
#define UTRSTAT0_REG		__REG(0x50000010)
#define UERSTAT0_REG		__REG(0x50000014)
#define UFSTAT0_REG		__REG(0x50000018)
#define UMSTAT0_REG		__REG(0x5000001C)
#define UTXH0_REG		__REG(0x50000020)
#define URXH0_REG		__REG(0x50000024)
#define UBRDIV0_REG		__REG(0x50000028)

#define ULCON1_REG		__REG(0x50004000)
#define UCON1_REG		__REG(0x50004004)
#define UFCON1_REG		__REG(0x50004008)
#define UMCON1_REG		__REG(0x5000400C)
#define UTRSTAT1_REG		__REG(0x50004010)
#define UERSTAT1_REG		__REG(0x50004014)
#define UFSTAT1_REG		__REG(0x50004018)
#define UMSTAT1_REG		__REG(0x5000401C)
#define UTXH1_REG		__REG(0x50004020)
#define URXH1_REG		__REG(0x50004024)
#define UBRDIV1_REG		__REG(0x50004028)

#define ULCON2_REG		__REG(0x50008000)
#define UCON2_REG		__REG(0x50008004)
#define UFCON2_REG		__REG(0x50008008)
#define UMCON2_REG		__REG(0x5000800C)
#define UTRSTAT2_REG		__REG(0x50008010)
#define UERSTAT2_REG		__REG(0x50008014)
#define UFSTAT2_REG		__REG(0x50008018)
#define UMSTAT2_REG		__REG(0x5000801C)
#define UTXH2_REG		__REG(0x50008020)
#define URXH2_REG		__REG(0x50008024)
#define UBRDIV2_REG		__REG(0x50008028)

#define ULCON_OFFSET		0x00
#define UCON_OFFSET		0x04
#define UFCON_OFFSET		0x08
#define UMCON_OFFSET		0x0C
#define UTRSTAT_OFFSET		0x10
#define UERSTAT_OFFSET		0x14
#define UFSTAT_OFFSET		0x18
#define UMSTAT_OFFSET		0x1C
#define UTXH_OFFSET		0x20
#define URXH_OFFSET		0x24
#define UBRDIV_OFFSET		0x28
#define UDIVSLOT_OFFSET		0x2c

#define UTRSTAT_TX_EMPTY	(1 << 2)
#define UTRSTAT_RX_READY	(1 << 0)
#define UART_ERR_MASK		0xF

/*
 * PWM timer
 */
#define ELFIN_TIMER_BASE	0x51000000

#define TCFG0_REG		__REG(0x51000000)
#define TCFG1_REG		__REG(0x51000004)
#define TCON_REG		__REG(0x51000008)
#define TCNTB0_REG		__REG(0x5100000C)
#define TCMPB0_REG		__REG(0x51000010)
#define TCNTO0_REG		__REG(0x51000014)
#define TCNTB1_REG		__REG(0x51000018)
#define TCMPB1_REG		__REG(0x5100001C)
#define TCNTO1_REG		__REG(0x51000020)
#define TCNTB2_REG		__REG(0x51000024)
#define TCMPB2_REG		__REG(0x51000028)
#define TCNTO2_REG		__REG(0x5100002C)
#define TCNTB3_REG		__REG(0x51000030)
#define TCMPB3_REG		__REG(0x51000034)
#define TCNTO3_REG		__REG(0x51000038)
#define TCNTB4_REG		__REG(0x5100003C)
#define TCNTO4_REG		__REG(0x51000040)

/* Fields */
#define fTCFG0_DZONE		Fld(8,16)       /* the dead zone length (= timer 0) */
#define fTCFG0_PRE1		Fld(8,8)        /* prescaler value for time 2,3,4 */
#define fTCFG0_PRE0		Fld(8,0)        /* prescaler value for time 0,1 */
#define fTCFG1_MUX4		Fld(4,16)
/* bits */
#define TCFG0_DZONE(x)		FInsrt((x), fTCFG0_DZONE)
#define TCFG0_PRE1(x)		FInsrt((x), fTCFG0_PRE1)
#define TCFG0_PRE0(x)		FInsrt((x), fTCFG0_PRE0)
#define TCON_4_AUTO		(1 << 22)       /* auto reload on/off for Timer 4 */
#define TCON_4_UPDATE		(1 << 21)       /* manual Update TCNTB4 */
#define TCON_4_ONOFF		(1 << 20)       /* 0: Stop, 1: start Timer 4 */
#define COUNT_4_ON		(TCON_4_ONOFF*1)
#define COUNT_4_OFF		(TCON_4_ONOFF*0)
#define TCON_3_AUTO		(1 << 19)       /* auto reload on/off for Timer 3 */
#define TIMER3_ATLOAD_ON	(TCON_3_AUTO*1)
#define TIMER3_ATLAOD_OFF	FClrBit(TCON, TCON_3_AUTO)
#define TCON_3_INVERT		(1 << 18)       /* 1: Inverter on for TOUT3 */
#define TIMER3_IVT_ON		(TCON_3_INVERT*1)
#define TIMER3_IVT_OFF		(FClrBit(TCON, TCON_3_INVERT))
#define TCON_3_MAN		(1 << 17)       /* manual Update TCNTB3,TCMPB3 */
#define TIMER3_MANUP		(TCON_3_MAN*1)
#define TIMER3_NOP		(FClrBit(TCON, TCON_3_MAN))
#define TCON_3_ONOFF		(1 << 16)       /* 0: Stop, 1: start Timer 3 */
#define TIMER3_ON		(TCON_3_ONOFF*1)
#define TIMER3_OFF		(FClrBit(TCON, TCON_3_ONOFF))
/* macros */
#define GET_PRESCALE_TIMER4(x)	FExtr((x), fTCFG0_PRE1)
#define GET_DIVIDER_TIMER4(x)	FExtr((x), fTCFG1_MUX4)

/*
 * Watchdog timer
 */
#define ELFIN_WATCHDOG_BASE	0x53000000

#define WTCON_REG		__REG(0x53000000)
#define WTDAT_REG		__REG(0x53000004)
#define WTCNT_REG		__REG(0x53000008)

/*
 * GPIO
 */
#define ELFIN_GPIO_BASE		0x56000000

#define GPACON_OFFSET		0x00
#define GPADAT_OFFSET		0x04

#define GPBCON_OFFSET		0x10
#define GPBDAT_OFFSET		0x14
#define GPBPU_OFFSET		0x18

#define GPCCON_OFFSET		0x20
#define GPCDAT_OFFSET		0x24
#define GPCPU_OFFSET		0x28

#define GPDCON_OFFSET		0x30
#define GPDDAT_OFFSET		0x34
#define GPDPU_OFFSET		0x38

#define GPECON_OFFSET		0x40
#define GPEDAT_OFFSET		0x44
#define GPEPU_OFFSET		0x48

#define GPFCON_OFFSET		0x50
#define GPFDAT_OFFSET		0x54
#define GPFPU_OFFSET		0x58

#define GPGCON_OFFSET		0x60
#define GPGDAT_OFFSET		0x64
#define GPGPU_OFFSET		0x68

#define GPHCON_OFFSET		0x70
#define GPHDAT_OFFSET		0x74
#define GPHPU_OFFSET		0x78

#define GPJCON_OFFSET		0xd0
#define GPJDAT_OFFSET		0xd4
#define GPJPU_OFFSET		0xd8

#define GPKCON_OFFSET		0xe0
#define GPKDAT_OFFSET		0xe4
#define GPKPU_OFFSET		0xe8

#define GPLCON_OFFSET		0xf0
#define GPLDAT_OFFSET		0xf4
#define GPLPU_OFFSET		0xf8

#define GPMCON_OFFSET		0x100
#define GPMDAT_OFFSET		0x104
#define GPMPU_OFFSET		0x108

#define MISCCR_OFFSET		0x80
#define DCLKCON_OFFSET		0x84

#define EINTCON0_OFFSET		0x88
#define EINTCON1_OFFSET		0x8c
#define EINTCON2_OFFSET		0x90

#define EINTFLT0_OFFSET		0x94
#define EINTFLT1_OFFSET		0x98
#define EINTFLT2_OFFSET		0x9c
#define EINTFLT3_OFFSET		0xa0

#define EINTMASK_OFFSET		0xa4
#define EINTPEND_OFFSET		0xa8

#define GSTATUS0_OFFSET		0xac
#define GSTATUS1_OFFSET		0xb0
#define GSTATUS3_OFFSET		0xb8
#define GSTATUS4_OFFSET		0xbc

#define DSC0_OFFSET		0xc0
#define DSC1_OFFSET		0xc4
#define DSC2_OFFSET		0xc8

#define MSLCON_OFFSET		0xcc

#define GPACON_REG		__REG(0x56000000)
#define GPADAT_REG		__REG(0x56000004)

#define GPBCON_REG		__REG(0x56000010)
#define GPBDAT_REG		__REG(0x56000014)
#define GPBPU_REG		__REG(0x56000018)

#define GPCCON_REG		__REG(0x56000020)
#define GPCDAT_REG		__REG(0x56000024)
#define GPCPU_REG		__REG(0x56000028)

#define GPDCON_REG		__REG(0x56000030)
#define GPDDAT_REG		__REG(0x56000034)
#define GPDPU_REG		__REG(0x56000038)

#define GPECON_REG		__REG(0x56000040)
#define GPEDAT_REG		__REG(0x56000044)
#define GPEPU_REG		__REG(0x56000048)

#define GPFCON_REG		__REG(0x56000050)
#define GPFDAT_REG		__REG(0x56000054)
#define GPFPU_REG		__REG(0x56000058)

#define GPGCON_REG		__REG(0x56000060)
#define GPGDAT_REG		__REG(0x56000064)
#define GPGPU_REG		__REG(0x56000068)

#define GPHCON_REG		__REG(0x56000070)
#define GPHDAT_REG		__REG(0x56000074)
#define GPHPU_REG		__REG(0x56000078)

#define GPJCON_REG		__REG(0x560000d0)
#define GPJDAT_REG		__REG(0x560000d4)
#define GPJPU_REG		__REG(0x560000d8)

#define GPKCON_REG		__REG(0x560000e0)
#define GPKDAT_REG		__REG(0x560000e4)
#define GPKPU_REG		__REG(0x560000e8)

#define GPLCON_REG		__REG(0x560000f0)
#define GPLDAT_REG		__REG(0x560000f4)
#define GPLPU_REG		__REG(0x560000f8)

#define GPMCON_REG		__REG(0x56000100)
#define GPMDAT_REG		__REG(0x56000104)
#define GPMPU_REG		__REG(0x56000108)

#define MISCCR_REG		__REG(0x56000080)
#define DCLKCON_REG		__REG(0x56000084)

#define EINTCON0_REG		__REG(0x56000088)
#define EINTCON1_REG		__REG(0x5600008c)
#define EINTCON2_REG		__REG(0x56000090)

#define EINTFLT0_REG		__REG(0x56000094)
#define EINTFLT1_REG		__REG(0x56000098)
#define EINTFLT2_REG		__REG(0x5600009c)
#define EINTFLT3_REG		__REG(0x560000a0)

#define EINTMASK_REG		__REG(0x560000a4)
#define EINTPEND_REG		__REG(0x560000a8)

#define GSTATUS0_REG		__REG(0x560000ac)
#define GSTATUS1_REG		__REG(0x560000b0)
#define GSTATUS3_REG		__REG(0x560000b8)
#define GSTATUS4_REG		__REG(0x560000bc)

#define DSC0_REG		__REG(0x560000c0)
#define DSC1_REG		__REG(0x560000c4)
#define DSC2_REG		__REG(0x560000c8)

#define MSLCON_REG		__REG(0x560000cc)

/*
 * RTC Controller
 */
#define ELFIN_RTC_BASE		0x57000000
#define RTCCON_REG		__REG(0x57000040)
#define TICNT_REG		__REG(0x57000044)
#define RTCALM_REG		__REG(0x57000050)
#define ALMSEC_REG		__REG(0x57000054)
#define ALMMIN_REG		__REG(0x57000058)
#define ALMHOUR_REG		__REG(0x5700005c)
#define ALMDATE_REG		__REG(0x57000060)
#define ALMMON_REG		__REG(0x57000064)
#define ALMYEAR_REG		__REG(0x57000068)
#define BCDSEC_REG		__REG(0x57000070)
#define BCDMIN_REG		__REG(0x57000074)
#define BCDHOUR_REG		__REG(0x57000078)
#define BCDDATE_REG		__REG(0x5700007c)
#define BCDDAY_REG		__REG(0x57000080)
#define BCDMON_REG		__REG(0x57000084)
#define BCDYEAR_REG		__REG(0x57000088)

#endif /*__S3C2416_H__*/
