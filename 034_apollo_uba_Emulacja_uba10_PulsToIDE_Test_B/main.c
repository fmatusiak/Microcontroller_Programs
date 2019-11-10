/*
 Zabezpieczenie nv10 nri z kwarcem wersja finalana
 zegar kwarcowy 8 MHZ
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"

volatile uint8_t data = 1;

volatile uint8_t test = 1;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);

#define Synch 0xFC

int main(void) {

	DDR_coin_we;
	coin_we_VCC;

	uart_init(RS_UBRR);
	_delay_ms(2000);


	while (1) {

		data = uart_getc();

		data++;
		uart_putc(data);
	}
}

// =================================== koniec nri cctalk wrzutnik ==========================================

// FUNCTIONS

void uart_init(uint16_t ubrr) {
// Ustawienie prêdkoœci transmisji
	UBRRH = (uint8_t) (ubrr >> 8);
	UBRRL = (uint8_t) ubrr;

// W³¹czenie nadajnika i odbiornika
	UCSRB = (1 << RXEN) | (1 << TXEN);

	// Ustawienie formatu ramki:
	// 8 bitów danych, 1 b it stopu, even bit
	UCSRC = (1 << URSEL) | (3 << UCSZ0) | (1 << UPM1);

}

void uart_putc(uint8_t data) {

// Oczekiwanie na zakoñczenie nadawania
	while (!(UCSRA & (1 << UDRE))) {

	}

// Wys³anie danych
	UDR = data;
}

uint8_t uart_ischar(void) {
// Czy w buforze s¹ dane?

	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc(void) {
// Czy w buforze s¹ dane?

	while (!uart_ischar()) {

	}

	return UDR;
}

