#ifndef UART_H
#define UART_H

#define BUFFER_SIZE 256

void initUART(void);
void enableUART(void);
void disableUART(void);
void sendData(char data);

#endif /* !UART_H */