#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>



#define F_CPU 3686400UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 23

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);



int main(void) {
	int i;


	uart_init(RS_UBRR);
	DDR_RESET_OUT;
	PORT_RESET_OUT_0;
	_delay_ms(250);
	PORT_RESET_OUT_1;

	while (1) {



	_delay_ms(1000);

}

}

// FUNCTIONS

void uart_init(uint16_t ubrr) {
// Ustawienie prêdkoœci transmisji
UBRR0H = (uint8_t) (ubrr >> 8);
UBRR0L = (uint8_t) ubrr;

// W³¹czenie nadajnika i odbiornika
UCSR0B = (1 << RXEN0) | (1 << TXEN0);

// Ustawienie formatu ramki:
// 8 bitów danych, 1 b it stopu, brak parzystoœci
UCSR0C = (0 << USBS0) | (3 << UCSZ00);
}

void uart_putc(uint8_t data) {
// Oczekiwanie na zakoñczenie nadawania
while (!(UCSR0A & (1 << UDRE0)))
	;

// Wys³anie danych
UDR0 = data;
}

uint8_t uart_ischar() {
// Czy w buforze s¹ dane?
return (UCSR0A & (1 << RXC0));
}

uint8_t uart_getc() {
// Czy w buforze s¹ dane?
while (!uart_ischar())
	;
return UDR0;
}






// === cctalk

