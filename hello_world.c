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

uint32_t uartDivisor = 433;

#define BUFFER_SIZE 100

volatile char rx_buffer[BUFFER_SIZE]; // Buffer for received data
volatile int rx_index = 0;			  // Index for the received buffer
volatile char receive_flag = 0;

typedef enum
{
	BUTTON,
	UART,
	NONE
} Mode;

	alt_u32
	timerISR(void *context)
{
	int *timeCount = (int *)context;
	(*timeCount)++;
	return 1; // next time out is 100ms
}

void buttonISR(void *context, alt_u32 id)
{
	volatile int *temp = (volatile int *)context;
	(*temp) = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE, 0);
}

void uartISR(void *context, alt_u32 id)
{

	// Clear control register
	IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE, 0);

	// Check if the interrupt was for RX (data received)
	if (IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) & ALTERA_AVALON_UART_STATUS_RRDY_MSK)
	{

		// Get received data
		char data = IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
		if (rx_index < BUFFER_SIZE - 1)
		{
			rx_buffer[rx_index++] = data;
			rx_buffer[rx_index] = '\0';
			receive_flag = 1;
		}
		else
		{
			// Handle buffer overflow
			rx_index = 0;
		}
	}

	// Enable interrupt
	IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE, (1 << 7));
}

Mode getMode()
{
	char choice[10];
	while (1)
	{
		printf("Select mode: Button, UART\r\n");
		scanf("%9s", &choice);

		// Convert string to lower
		for (int i = 0; i < strlen(choice); i++)
		{
			choice[i] = tolower((unsigned char)choice[i]);
		}

		if(strcmp(choice, "button") == 0)
		{
			printf("You have selected the BUTTON mode.\n");
			return BUTTON;
		}
		else if(strcmp(choice, "uart") == 0)
		{
			printf("You have selected the UART mode.\n");
			return UART;
		}

		printf("Invalid entry. Please try again.\n");
	}
}

int main()
{
	// Button init
	int button = 0;
	void *buttonContext = (void *)&button;
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE, 0);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEYS_BASE, 0x7);
	alt_irq_register(KEYS_IRQ, buttonContext, buttonISR);

	// Register the ISR for UART
	IOWR_ALTERA_AVALON_UART_DIVISOR(UART_BASE, uartDivisor);
	IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE, ALTERA_AVALON_UART_CONTROL_RRDY_MSK);
	alt_irq_register(UART_IRQ, NULL, uartISR);

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

	// Reset LED
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, 0x00);

	Mode mode = getMode();
	while (1)
	{
		// Get dT
		data.deltaT = systemTime - prevTime;
		prevTime = systemTime;

		/**
		 * ***********
		 *
		 * BUTTON MODE
		 *
		 * ***********
		 */
		switch (mode)
		{
		case BUTTON:
			// Update inputs from button clicks
			data.AS = (button & (1 << 2)) ? 1 : 0;
			data.VS = (button & (1 << 1)) ? 1 : 0;
			button = 0; // Bring back to 0

			tick(&data);

			// Light up LEDs when VP or AP happens
			if (data.VP)
			{
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, 0x01);
				printf("VP\r\n");
			}
			else
			{
				if(systemTime % 100 == 0)
				{
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) & ~0x01);
				}
			}

			if (data.AP)
			{
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, 0x02);
				printf("AP\r\n");
			}
			else
			{
				if(systemTime % 100 == 0)
				{
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) & ~0x02);
				}
			}

			// Light up LEDs when VS or AS happens
			if (data.VS)
			{
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x01);
				printf("VS\r\n");
			}
			else
			{
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE) & ~0x01);
			}

			if (data.AS)
			{
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x02);
				printf("AS\r\n");
			}
			else
			{
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE) & ~0x02);
			}
			break;
		case UART:
			/************
			 *
			 * UART MODE
			 *
			 * **********
			 */

			// Read from buffer
			if (receive_flag == 1)
			{
				data.VS = (rx_buffer[rx_index - 1] == 65) ? 1 : 0;
				data.AS = (rx_buffer[rx_index - 1] == 86) ? 1 : 0;
				rx_index = 0;
				receive_flag = 0;
			}

			tick(&data);
			data.VS = 0;
			data.AS = 0;

			// Write to UART
			if (data.VP)
			{
				while (!(IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) & ALTERA_AVALON_UART_STATUS_TRDY_MSK))
				{
				}
				IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE, 'V');
			}

			if (data.AP)
			{
				while (!(IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) & ALTERA_AVALON_UART_STATUS_TRDY_MSK))
				{
				}
				IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE, 'A');
			}
		}
	}
	return 0;
}
