#include <system.h>
#include <sys/alt_irq.h>
#include <altera_avalon_pio_regs.h>
#include <altera_avalon_uart_regs.h>

#include "uart.h"
#include "util.h"

#define UART_DIVISOR 433

volatile char rxBuffer[BUFFER_SIZE];
volatile int rxIndex;
volatile char receiveFlag = 0;

volatile char transmitFlag = 0;
volatile char dataToSend;

void uartISR(void *context, alt_u32 id)
{

    // Clear control register
    IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE, 0);

    // Check if the interrupt was for RX (data received)
    if (IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) & ALTERA_AVALON_UART_STATUS_RRDY_MSK)
    {

        // Get received data
        char data = IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
        if (rxIndex < BUFFER_SIZE - 1)
        {
            rxBuffer[rxIndex++] = data;
            rxBuffer[rxIndex] = '\0';
            receiveFlag = 1;
        }
        else
        {
            // Handle buffer overflow
            rxIndex = 0;
        }
    }

    if (IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) & ALTERA_AVALON_UART_STATUS_TRDY_MSK)
    {
        if (transmitFlag == 1)
        {
            IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE, dataToSend);
            transmitFlag = 0;
        }
    }

    // Enable interrupt
	IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE, (1 << 7));
}

void initUART(void)
{
    // Register the ISR for UART
    IOWR_ALTERA_AVALON_UART_DIVISOR(UART_BASE, UART_DIVISOR);
    alt_irq_register(UART_IRQ, NULL, uartISR);
}
void enableUART(void)
{
    IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE, ALTERA_AVALON_UART_CONTROL_RRDY_MSK | ALTERA_AVALON_UART_CONTROL_TRDY_MSK);
}
void disableUART(void)
{
    IOWR_ALTERA_AVALON_UART_CONTROL(UART_BASE, 0x00);
}
void sendData(char data)
{
	while (!(IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) & ALTERA_AVALON_UART_STATUS_TRDY_MSK))
	{
	}
	IOWR_ALTERA_AVALON_UART_TXDATA(UART_BASE, data);
}

char getData(void)
{
	if(receiveFlag == 1)
	{
		char d = rxBuffer[rxIndex - 1];
		rxIndex = 0;
		receiveFlag = 0;
		return d;
	}
	return 0;
}
