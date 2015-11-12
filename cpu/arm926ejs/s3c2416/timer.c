/*
 * Copyright (C) Marvell International Ltd. and its affiliates
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
#include <s3c2416.h>
#include <div64.h>

extern ulong get_PCLK(void);

static int timer_load_val = 0;
static ulong timestamp;
static ulong lastdec;

static inline unsigned long long tick_to_time(unsigned long long tick)
{
	tick *= 1000;
	do_div(tick, CONFIG_SYS_HZ);
	return tick;
}

/* macro to read the 16 bit timer */
static inline ulong READ_TIMER(void)
{
	S3C24X0_TIMERS *const timers = S3C24X0_GetBase_TIMERS();

	return (timers->TCNTO4 & 0xffff);
}

void reset_timer_masked(void)
{
	/* reset time */
	lastdec = READ_TIMER();
	timestamp = 0;
}

ulong get_timer_masked(void)
{
	ulong now = READ_TIMER();

	if (lastdec >= now) {
		/* normal mode */
		timestamp += lastdec - now;
	}
	else {
		/* we have an overflow ... */
		timestamp += lastdec + timer_load_val - now;
	}
	lastdec = now;

	return timestamp;
}

void reset_timer(void)
{
	reset_timer_masked();
}

ulong get_timer(ulong base)
{
	return tick_to_time(get_ticks()) - base;
}

void set_timer(ulong t)
{
	timestamp = t;
}

void udelay(unsigned long usec)
{
	ulong tmo, tmp;

	if (usec >= 1000) {		/* if "big" number, spread normalization to seconds */
		tmo = usec / 1000;	/* start to normalize for usec to ticks per sec */
		tmo *= CONFIG_SYS_HZ;		/* find number of "ticks" to wait to achieve target */
		tmo /= 1000;		/* finish normalize. */
	} else {				/* else small number, don't kill it prior to HZ multiply */
		tmo = usec * CONFIG_SYS_HZ;
		tmo /= (1000 * 1000);
	}

	tmp = get_timer(0);		/* get current timestamp */
	if ((tmo + tmp + 1) < tmp)	/* if setting this fordward will roll time stamp */
		reset_timer_masked();	/* reset "advancing" timestamp to 0, set lastdec value */
	else
		tmo += tmp;		/* else, set advancing stamp wake up time */
	while (get_timer_masked()<tmo)	/* loop till event */
		 /*NOP*/;
}

/* waits specified delay value and resets timestamp */
void udelay_masked (unsigned long usec)
{
	ulong tmo;
	ulong endtime;
	signed long diff;

	if (usec >= 1000) {			/* if "big" number, spread normalization to seconds */
		tmo = usec / 1000;		/* start to normalize for usec to ticks per sec */
		tmo *= CONFIG_SYS_HZ;			/* find number of "ticks" to wait to achieve target */
		tmo /= 1000;			/* finish normalize. */
	} else {					/* else small number, don't kill it prior to HZ multiply */
		tmo = usec * CONFIG_SYS_HZ;
		tmo /= (1000*1000);
	}
	endtime = get_timer_masked () + tmo;

	do {
		ulong now = get_timer_masked ();
		diff = endtime - now;
	} while (diff >= 0);
}

/*
 * This function is derived from PowerPC code (read timebase as long long).
 * On ARM it just returns the timer value.
 */
unsigned long long get_ticks(void)
{
	return get_timer_masked();
}

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On ARM it returns the number of timer ticks per second.
 */
ulong get_tbclk(void)
{
	ulong tbclk;

	tbclk = CONFIG_SYS_HZ;
	return tbclk;
}

/*
 * init the counter
 */
int timer_init(void)
{
	S3C24X0_TIMERS *const timers = S3C24X0_GetBase_TIMERS();

	/* use PWM Timer 4 because it has no output */
	/* prescaler for Timer 4 is 16 */
	timers->TCFG0 = 0x0f00;
	if (timer_load_val == 0) {
		/*
		 * for 10 ms clock period @ PCLK with 4 bit divider = 1/2
		 * (default) and prescaler = 16. Should be
		 * 20625 @ 66 MHz
		 */
		timer_load_val = get_PCLK() / (2 * 16 * 100);
	}

	/* load value for 10 ms timeout */
	lastdec = timers->TCNTB4 = timer_load_val;
	/* auto load, manual update of Timer 4 */
	timers->TCON = (timers->TCON & ~0x00700000) | 0x00600000;
	/* auto load, start Timer 4 */
	timers->TCON = (timers->TCON & ~0x00700000) | 0x00500000;
	timestamp = 0;

	return (0);
}
