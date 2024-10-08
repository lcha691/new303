#include <system.h>
#include <sys/alt_irq.h>
#include <sys/alt_alarm.h>
#include <altera_avalon_pio_regs.h>

#include "sccharts_implementation.h"
#include "sccharts.h"
#include "uart.h"
#include "timing.h"

#define LRI_MASK (1 << 0)
#define URI_MASK (1 << 1)
#define AVI_MASK (1 << 2)
#define AEI_MASK (1 << 3)
#define PVARP_MASK (1 << 4)
#define VRP_MASK (1 << 5)

alt_u32 isrLRI(void *context);
alt_u32 isrURI(void *context);
alt_u32 isrAVI(void *context);
alt_u32 isrAEI(void *context);
alt_u32 isrVRP(void *context);
alt_u32 isrPVARP(void *context);

void startAlarm(alt_alarm *alarm);
void stopAlarm(alt_alarm *alarm);

volatile char pacemakerFlags = 0x00;

volatile alt_alarm LRIalarm, URIalarm, AVIalarm, AEIalarm, PVARPalarm, VRPalarm;
volatile char VS, VP, AS, AP;
volatile Mode currentMode;
char uartData;

void flashLEDs_C(double dt, char AS, char AP, char VS, char VP)
{
	static alt_u64 systemTime = 0;
	systemTime += dt;
	// Light up LEDs when VP or AP happens
	if (VP)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, 0x01);
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
	}
	else
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE) & ~0x01);
	}

	if (AS)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x02);
	}
	else
	{
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE) & ~0x02);
	}
}

void initC(void)
{
    alt_alarm_stop(&LRIalarm);
    alt_alarm_stop(&URIalarm);
    alt_alarm_stop(&AVIalarm);
    alt_alarm_stop(&AEIalarm);
    alt_alarm_stop(&PVARPalarm);
    alt_alarm_stop(&VRPalarm);
}
void execC(double dt, Mode mode, int *button)
{
    // Get input signals
	currentMode = mode;
    switch (currentMode)
    {
    case BUTTON:
        VS = (*button & (1 << 1)) ? 1 : 0;
        AS = (*button & (1 << 2)) ? 1 : 0;
        *button = 0;

        break;
    case UART:
    	uartData = getData();
        if (receiveFlag == 1)
        {
            VS = (uartData == 65) ? 1 : 0;
            AS = (uartData == 86) ? 1 : 0;
            rxIndex = 0;
            receiveFlag = 0;
        }
        break;
    }

    /********************************/
    /************ LOGIC *************/
    /********************************/

    if (AS || AP)
    {
    	if(AS)
    	{
    		if ((pacemakerFlags & AEI_MASK) && !(pacemakerFlags & PVARP_MASK))
			{
				stopAlarm(&AEIalarm);
			}
    	}
        if (!(pacemakerFlags & AVI_MASK))
        {
            startAlarm(&AVIalarm);
        }
        flashLEDs_C(dt, AS, AP, VS, VP);
        AP = 0;
    }


    if (VS || VP)
    {
        if ((pacemakerFlags & AVI_MASK) && !(pacemakerFlags & VRP_MASK))
        {
            stopAlarm(&AVIalarm);
        }

        if (!(pacemakerFlags & PVARP_MASK))
        {
            startAlarm(&PVARPalarm);
        }

        if (!(pacemakerFlags & AEI_MASK))
        {
            startAlarm(&AEIalarm);
        }

        if (!(pacemakerFlags & VRP_MASK))
        {
            startAlarm(&VRPalarm);
        }

        startAlarm(&URIalarm);
        startAlarm(&LRIalarm);

        flashLEDs_C(dt, AS, AP, VS, VP);
        VP = 0;
    }

    flashLEDs_C(dt, AS, AP, VS, VP);
}

void startAlarm(alt_alarm *alarm)
{
    /**
     * Starts the alarm and sets flag to HIGH.
     */

    void *flagsContext = (void *)pacemakerFlags;
    int timerTicks;
    alt_alarm_stop(alarm);

    if (alarm == &AVIalarm)
    {
        pacemakerFlags = pacemakerFlags | AVI_MASK;
        timerTicks = AVI_VALUE;
        alt_alarm_start(alarm, timerTicks, isrAVI, flagsContext);
    }
    else if (alarm == &AEIalarm)
    {
        pacemakerFlags = pacemakerFlags | AEI_MASK;
        timerTicks = AEI_VALUE;
        alt_alarm_start(alarm, timerTicks, isrAEI, flagsContext);
    }
    else if (alarm == &URIalarm)
    {
        pacemakerFlags = pacemakerFlags | URI_MASK;
        timerTicks = URI_VALUE;
        alt_alarm_start(alarm, timerTicks, isrURI, flagsContext);
    }
    else if (alarm == &LRIalarm)
    {
        pacemakerFlags = pacemakerFlags | LRI_MASK;
        timerTicks = LRI_VALUE;
        alt_alarm_start(alarm, timerTicks, isrLRI, flagsContext);
    }
    else if (alarm == &PVARPalarm)
    {
        pacemakerFlags = pacemakerFlags | PVARP_MASK;
        timerTicks = PVARP_VALUE;
        alt_alarm_start(alarm, timerTicks, isrPVARP, flagsContext);
    }
    else if (alarm == &VRPalarm)
    {
        pacemakerFlags = pacemakerFlags | VRP_MASK;
        timerTicks = VRP_VALUE;
        alt_alarm_start(alarm, timerTicks, isrVRP, flagsContext);
    }
}

void stopAlarm(alt_alarm *alarm)
{
    /**
     * Stops the alarm and puts flag to LOW.
     */
    alt_alarm_stop(alarm);

    if (alarm == &AVIalarm)
    {
        pacemakerFlags = pacemakerFlags & ~AVI_MASK;
    }
    else if (alarm == &AEIalarm)
    {
        pacemakerFlags = pacemakerFlags & ~AEI_MASK;
    }
    else if (alarm == &URIalarm)
    {
        pacemakerFlags = pacemakerFlags & ~URI_MASK;
    }
    else if (alarm == &LRIalarm)
    {
        pacemakerFlags = pacemakerFlags & ~LRI_MASK;
    }
    else if (alarm == &PVARPalarm)
    {
        pacemakerFlags = pacemakerFlags & ~PVARP_MASK;
    }
    else if (alarm == &VRPalarm)
    {
        pacemakerFlags = pacemakerFlags & ~VRP_MASK;
    }
}

alt_u32 isrLRI(void *context)
{
    VP = 1;
    pacemakerFlags = pacemakerFlags & ~LRI_MASK;
    if(currentMode == UART){
    	sendData('V');
    }
    alt_alarm_stop(&LRIalarm);
    return 0;
}

alt_u32 isrURI(void *context)
{
    pacemakerFlags = pacemakerFlags & ~URI_MASK;
    alt_alarm_stop(&URIalarm);
    return 0;
}

alt_u32 isrPVARP(void *context)
{
    pacemakerFlags = pacemakerFlags & ~PVARP_MASK;
    alt_alarm_stop(&PVARPalarm);
    return 0;
}

alt_u32 isrAVI(void *context)
{
    if (pacemakerFlags & URI_MASK)
    {
        return 1; // Extend alarm
    }
    pacemakerFlags = pacemakerFlags & ~AVI_MASK;
    VP = 1;
    if(currentMode == UART){
    	sendData('V');
    }
    alt_alarm_stop(&AVIalarm);
    return 0;
}

alt_u32 isrVRP(void *context)
{
    pacemakerFlags = pacemakerFlags & ~VRP_MASK;
    alt_alarm_stop(&VRPalarm);
    return 0;
}

alt_u32 isrAEI(void *context)
{
    pacemakerFlags = pacemakerFlags & ~AEI_MASK;
    AP = 1;
    if(currentMode == UART){
    	sendData('A');
    }
    alt_alarm_stop(&AEIalarm);
    return 0;
}
