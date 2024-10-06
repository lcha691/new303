#include <system.h>
#include <sys/alt_irq.h>
#include <altera_avalon_pio_regs.h>

#include "sccharts_implementation.h"
#include "sccharts.h"
#include "uart.h"

TickData data;
char uartData;

void initScchart(void)
{
    // SC Chart Init
    reset(&data);
    tick(&data); // init tick
    uartData = 0;
}

void flashLEDs(double dt, char AS, char AP, char VS, char VP)
{
	static alt_u64 systemTime = 0;
	systemTime += dt;
	// Light up LEDs when VP or AP happens
	if (VP)
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

	if (AP)
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
	if (VS)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x01);
		printf("VS\r\n");
	}
	else
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE) & ~0x01);
	}

	if (AS)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x02);
		printf("AS\r\n");
	}
	else
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE) & ~0x02);
	}
}

void execScchart(double dt, Mode mode, int *button)
{
    /**
     * ***********
     *
     * BUTTON MODE
     *
     * ***********
     */

    static systemTime = 0;
    systemTime += dt;
    data.deltaT = dt;

    switch (mode)
    {
    case BUTTON:
        // Update inputs from button clicks
        data.AS = (*button & (1 << 2)) ? 1 : 0;
        data.VS = (*button & (1 << 1)) ? 1 : 0;
        *button = 0;

        tick(&data);

        break;
    case UART:
        /************
         *
         * UART MODE
         *
         * **********
         */

        // Read from buffer

    	uartData = getData();
        if (uartData)
        {
            data.VS = (uartData == 65) ? 1 : 0;
            data.AS = (uartData == 86) ? 1 : 0;
        }

        tick(&data);
        data.VS = 0;
        data.AS = 0;

        // Write to UART
        if (data.VP)
        {
            sendData('V');
        }

        if (data.AP)
        {
            sendData('A');
        }
    }

    flashLEDs(dt, data.AS, data.AP, data.VS, data.VP);
}
