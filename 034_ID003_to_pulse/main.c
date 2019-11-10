#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

volatile uint8_t sec = 0, m = 0, start = 1, swieci = 0;
volatile uint8_t p = 1, j = 0, pintka = 0, i = 0;
volatile uint16_t min = 1, pom = 0, pomo = 0, przerwa = 0, czas = 0, punkty = 0,
		licznik = 0, time = 1600, punktyb = 0;



#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51



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
	while (!(UCSRA & (1 << UDRE)))
		;

	// Wys³anie danych
	UDR = data;
}
//
uint8_t uart_ischar() {
	// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc() {
	// Czy w buforze s¹ dane?
	while (!uart_ischar())
		;

	// Dane z bufora
	return UDR;
}
volatile int poszlo = 1;

int main(void) {
	_delay_ms(2000);
	DDR_dwojka_wy;
	PORT_dwojka_wy_1;

	uart_init(RS_UBRR);
	_delay_ms(2000);

	uart_putc(252);
	uart_putc(5);
	uart_putc(17);
	uart_putc(39);
	uart_putc(86);

	_delay_ms(100);

	uart_putc(252);
	uart_putc(5);
	uart_putc(136);
	uart_putc(111);
	uart_putc(95);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(5);
	uart_putc(64); // reset devaice
	uart_putc(43);
	uart_putc(21);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(6);
	uart_putc(195); // reset devaice
	uart_putc(0);
	uart_putc(4);
	uart_putc(214);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(6);
	uart_putc(199); // reset devaice
	uart_putc(252);
	uart_putc(135);
	uart_putc(140);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(5);
	uart_putc(17); // request sttusa
	uart_putc(39);
	uart_putc(86);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(6);
	uart_putc(195); // reset devaice
	uart_putc(0);
	uart_putc(4);
	uart_putc(214);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(6);
	uart_putc(199); // reset devaice
	uart_putc(252);
	uart_putc(135);
	uart_putc(140);
	_delay_ms(100);

	while (1) {

		uart_putc(252);
		uart_putc(5);
		uart_putc(17); // request sttusa
		uart_putc(39);
		uart_putc(86);

		min = uart_getc();

		_delay_ms(150);
		if (min == 232) { //ukladarka reset
			uart_putc(252);
			uart_putc(5);
			uart_putc(17);
			uart_putc(39);
			uart_putc(86);

			_delay_ms(100);

			uart_putc(252);
			uart_putc(5);
			uart_putc(136);
			uart_putc(111);
			uart_putc(95);
			_delay_ms(100);

			uart_putc(252);
			uart_putc(5);
			uart_putc(64); // reset devaice
			uart_putc(43);
			uart_putc(21);
			_delay_ms(100);

			uart_putc(252);
			uart_putc(6);
			uart_putc(195); // reset devaice
			uart_putc(0);
			uart_putc(4);
			uart_putc(214);
			_delay_ms(100);

			uart_putc(252);
			uart_putc(6);
			uart_putc(199); // reset devaice
			uart_putc(252);
			uart_putc(135);
			uart_putc(140);
			_delay_ms(100);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(100);

			uart_putc(252);
			uart_putc(6);
			uart_putc(195); // reset devaice
			uart_putc(0);
			uart_putc(4);
			uart_putc(214);
			_delay_ms(100);

			uart_putc(252);
			uart_putc(6);
			uart_putc(199); // reset devaice
			uart_putc(252);
			uart_putc(135);
			uart_putc(140);
			_delay_ms(100);
		}
		if (min == 251) { //ten
			min = 0;

			uart_putc(252);
			uart_putc(5);
			uart_putc(65); // request sttusa
			uart_putc(162);
			uart_putc(4);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);

			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);

			min = 1;

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);

			_delay_ms(150);

			min = uart_getc();
			min = uart_getc();
			min = uart_getc();

		}

		if (min == 201) { // twenty
			min = 0;

			uart_putc(252);
			uart_putc(5);
			uart_putc(65); // request sttusa
			uart_putc(162);
			uart_putc(4);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);

			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);


			min = 1;

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);

			_delay_ms(150);

			min = uart_getc();
			min = uart_getc();
			min = uart_getc();

		}

		if (min == 216) {
			min = 0;

			uart_putc(252);
			uart_putc(5);
			uart_putc(65); // request sttusa
			uart_putc(162);
			uart_putc(4);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);


			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			min = 1;

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);

			_delay_ms(150);

			min = uart_getc();
			min = uart_getc();
			min = uart_getc();

		}

		if (min == 172) {
			min = 0;

			uart_putc(252);
			uart_putc(5);
			uart_putc(65); // request sttusa
			uart_putc(162);
			uart_putc(4);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);



			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;
			_delay_ms(100);
			PORT_dwojka_wy_0;
			_delay_ms(100);
			PORT_dwojka_wy_1;


			min = 1;

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);

			_delay_ms(150);

			min = uart_getc();
			min = uart_getc();
			min = uart_getc();

		}
		if (min == 16) {
			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			min = uart_getc();
			min = uart_getc();
			min = uart_getc();

		}

	}
}
