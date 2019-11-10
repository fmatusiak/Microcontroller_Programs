#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>




#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51



void uart_init(uint16_t ubrr) {
	// Ustawienie pr�dko�ci transmisji
	UBRRH = (uint8_t) (ubrr >> 8);
	UBRRL = (uint8_t) ubrr;

	// W��czenie nadajnika i odbiornika
	UCSRB = (1 << RXEN) | (1 << TXEN);

	// Ustawienie formatu ramki:
	// 8 bit�w danych, 1 b it stopu, even bit
	UCSRC = (1 << URSEL) | (3 << UCSZ0) | (1 << UPM1);
}

void uart_putc(uint8_t data) {
	// Oczekiwanie na zako�czenie nadawania
	while (!(UCSRA & (1 << UDRE)))
		;

	// Wys�anie danych
	UDR = data;
}
//
uint8_t uart_ischar() {
	// Czy w buforze s� dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc() {
	// Czy w buforze s� dane?
	while (!uart_ischar())
		;

	// Dane z bufora
	return UDR;
}

int main(void) {
	_delay_ms(2000);
	DDR_dwojka_wy;
	PORT_dwojka_wy_1;

	uart_init(RS_UBRR);

	while(1)
	{
		uart_putc(0xF1);

	}







}


void init(void )
{

}
