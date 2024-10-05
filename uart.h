#ifndef UART_H
#define UART_H

#define BUFFER_SIZE 256

extern volatile char rxBuffer[BUFFER_SIZE];
extern volatile int rxIndex;
extern volatile char receiveFlag;

void initUART(void);
void enableUART(void);
void disableUART(void);
void sendData(char data);

#endif /* !UART_H */
