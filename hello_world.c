/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <system.h>
#include <sys/alt_alarm.h>
#include <sys/alt_irq.h>
#include <altera_avalon_pio_regs.h>
#include <altera_avalon_uart_regs.h>

#include "sccharts.h"
#include "timing.h"
#include "uart.h"
#include "util.h"
#include "sccharts_implementation.h"

volatile char rx_buffer[BUFFER_SIZE]; // Buffer for received data
volatile int rx_index = 0;			  // Index for the received buffer
volatile char receive_flag = 0;

alt_u32 timerLRI(void *context);
alt_u32 timerURI(void *context);
alt_u32 timerAVI(void *context);
alt_u32 timerAEI(void *context);
alt_u32 timerVRP(void *context);
alt_u32 timerPVARP(void *context);

void flashLEDs(double dt, TickData *data);

alt_u32 timerISR(void *context)
{
	int *timeCount = (int *)context;
	(*timeCount)++;
	return 1; // next time out is 1ms
}

void buttonISR(void *context, alt_u32 id)
{
	volatile int *temp = (volatile int *)context;
	(*temp) = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE, 0);
}

int main()
{
	printf("STARTING\n");
	// Button init
	int button = 0;
	void *buttonContext = (void *)&button;
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE, 0);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEYS_BASE, 0x7);
	alt_irq_register(KEYS_IRQ, buttonContext, buttonISR);

	// SC Chart Init
	TickData data;
	reset(&data);
	tick(&data); // init tick

	// Timer Init
	alt_alarm ticker;
	uint64_t systemTime = 0;
	void *timerContext = (void *)&systemTime;
	alt_alarm_start(&ticker, 1, timerISR, timerContext);
	uint64_t prevTime = 0;

	// Timer
	alt_alarm LRIticker;
	uint64_t LRItime = 0;
	void *LRItimerContext = (void *)&LRItime;
	alt_alarm_start(&LRItime, 1, timerISR, LRItimerContext);

	initUART();

	// Reset LED
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, 0x00);
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x00);

	// Initialize modes
	Implementation implementation = NOT_A_IMP;
	Mode mode = NOT_A_MODE;
	double dt = 0;
	while (1)
	{
		// Get dT
		dt = systemTime - prevTime;
		prevTime = systemTime;

		// Check switches
		if (IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE) & (1 << 0))
		{
			implementation = C;
		}
		else if (!(IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE) & ~(1 << 0)))
		{
			implementation = SCCHART;
		}

		if (IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE) & (1 << 1))
		{
			mode = BUTTON;
		}
		else if (!(IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE) & ~(1 << 1)))
		{
			mode = UART;
		}

		switch (implementation)
		{
		case C:
			break;
		case SCCHART:
			// execScchart(dt, mode, &data, button);
			break;
		default:;
		}

		flashLEDs(dt, &data);
		button = 0;
	}
	return 0;
}

void flashLEDs(double dt, TickData *data)
{
	static alt_64 systemTime = 0;
	systemTime += dt;
	// Light up LEDs when VP or AP happens
	if (data->VP)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, 0x01);
		printf("VP\r\n");
	}
	else
	{
		if (systemTime % 100 == 0)
		{
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) & ~0x01);
		}
	}

	if (data->AP)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, 0x02);
		printf("AP\r\n");
	}
	else
	{
		if (systemTime % 100 == 0)
		{
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) & ~0x02);
		}
	}

	// Light up LEDs when VS or AS happens
	if (data->VS)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x01);
		printf("VS\r\n");
	}
	else
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE) & ~0x01);
	}

	if (data->AS)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x02);
		printf("AS\r\n");
	}
	else
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE) & ~0x02);
	}
}

void execC(double dt);

/***********  TIMERS ****************/
alt_u32 timerLRI(void *context)
{
	int *timeCount = (int *)context;
	(*timeCount)++;
	return LRI_VALUE; // next time out is 100ms
}

alt_u32 timerURI(void *context)
{
	int *timeCount = (int *)context;
	(*timeCount)++;
	return URI_VALUE; // next time out is 100ms
}

alt_u32 timerPVARP(void *context)
{
	int *timeCount = (int *)context;
	(*timeCount)++;
	return PVARP_VALUE; // next time out is 100ms
}

alt_u32 timerAVI(void *context)
{
	int *timeCount = (int *)context;
	(*timeCount)++;
	return AVI_VALUE; // next time out is 100ms
}

alt_u32 timerVRP(void *context)
{
	int *timeCount = (int *)context;
	(*timeCount)++;
	return VRP_VALUE; // next time out is 100ms
}

alt_u32 timerAEI(void *context)
{
	int *timeCount = (int *)context;
	(*timeCount)++;
	return AEI_VALUE; // next time out is 100ms
}
