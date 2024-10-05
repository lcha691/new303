#include <system.h>
#include <sys/alt_irq.h>
#include <altera_avalon_pio_regs.h>

#include "sccharts_implementation.h"
#include "sccharts.h"
#include "uart.h"

TickData data;

void initScchart(void)
{
    // SC Chart Init
    reset(&data);
    tick(&data); // init tick
}
Heart execScchart(double dt, Mode mode, int button)
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
        data.AS = (button & (1 << 2)) ? 1 : 0;
        data.VS = (button & (1 << 1)) ? 1 : 0;

        tick(&data);
        flashLEDs(dt, data);
        break;
    case UART:
        /************
         *
         * UART MODE
         *
         * **********
         */

        // Read from buffer
        if (receiveFlag == 1)
        {
            data.VS = (rxBuffer[rxIndex - 1] == 65) ? 1 : 0;
            data.AS = (rxBuffer[rxIndex - 1] == 86) ? 1 : 0;
            rxIndex = 0;
            receiveFlag = 0;
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

    Heart heart = {data.VS, data.AS, data.VP, data.AP};
    return heart;
}