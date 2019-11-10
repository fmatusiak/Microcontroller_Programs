//DOUBLE

#include <avr/io.h>
#include <util/delay.h>

#include "config.h"

void uart_flush(void){
	unsigned char dummy;
	while(UCSR0A & (1<<RXC0)) dummy = UDR0;
}
void uart_init(){
	UBRR0L = (unsigned char)BP;
	UBRR0H = (unsigned char)(BP>>8);
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1 << RXCIE0);
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}
void uart_putc(uint8_t data){
	// distable rx
	UCSR0B &= ~(1<< RXEN0);
	UCSR0B &= ~(1 << RXCIE0);

	while(!(UCSR0A) & (1<<UDRE0));
	UDR0 = data;
	// wait and enable rx
	_delay_ms(1);
	UCSR0B |= (1<<RXEN0) | (1<<RXCIE0);
}
uint8_t uart_rx(void){
	return UDR0;
}
