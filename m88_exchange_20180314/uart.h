//DOUBLE

#ifndef UART_H_
#define UART_H_

void uart_flush(void);
void uart_init(void);
void uart_putc(uint8_t data);
uint8_t uart_rx(void);

#endif /* UART_H_ */
