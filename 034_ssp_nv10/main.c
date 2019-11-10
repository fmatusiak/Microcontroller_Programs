#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

// oscyloscope view

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

volatile uint8_t start = 0, bit = 1, pozycja = 0, liczba = 0, bilet = 5,
		parzysty = 0, i = 0;
volatile int e, f, g, h, j = 0, pomoc = 0, banknot = 0, l = 0, pomocna = 0,
		punkty = 0;

volatile uint8_t a, b, c, d;

volatile uint16_t time_out = 2, tmp_time = 0, FL_time = 0, FL_timeout = 0;

void uart_init(uint16_t ubrr) {
	// Ustawienie prêdkoœci transmisji
	UBRRH = (uint8_t) (ubrr >> 8);
	UBRRL = (uint8_t) ubrr;

	// W³¹czenie nadajnika i odbiornika
	UCSRB = (1 << RXEN) | (1 << TXEN);

	// Ustawienie formatu ramki:
	// 8 bitów danych, 2 b it stopu, brak parzystosci
	UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
}

void uart_putc(uint8_t data) {
	// Oczekiwanie na zakoñczenie nadawania
	while (!(UCSRA & (1 << UDRE)))
		;

	// Wys³anie danych
	UDR = data;
}

uint8_t uart_ischar() {
	// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc() {
	// Czy w buforze s¹ dane?
	uint16_t tmp_time_out = 0;
	while (!uart_ischar()) {

		tmp_time_out++;
		if (tmp_time_out >= 10000) {
			return 0;
		}

	};

	// Dane z bufora
	return UDR;
}

void uart_clear(void) {
	uint8_t flu;
	while ( UCSRA & (1 << RXC)) {
		flu = UDR;
	}
}

void uart_get_date(void) {
	for (uint8_t i = 0; i < 8; i++) {
		c = uart_getc();
		if (c == 0xEE) {
			return;
		}

	}
}

volatile int poszlo = 1;

int main(void) {

	_delay_ms(5000);
	DDR_w_gry;
	PORT_w_gry_1;
	DDR_IN6_IN;
	IN6_IN_VCC;

	uart_init(RS_UBRR);

	uart_putc(127);
	uart_putc(128);
	uart_putc(1);
	uart_putc(17);
	uart_putc(101);
	uart_putc(130);
	_delay_ms(242);

	uart_putc(127);
	uart_putc(128);
	uart_putc(1);
	uart_putc(7);
	uart_putc(18);
	uart_putc(2);
	_delay_ms(242);

	uart_putc(127);
	uart_putc(0);
	uart_putc(1);
	uart_putc(10);
	uart_putc(60);
	uart_putc(8);
	_delay_ms(242);

	uart_putc(127);
	uart_putc(128);
	uart_putc(3);
	uart_putc(2);
	uart_putc(31);
	uart_putc(0);
	uart_putc(43);
	uart_putc(230);
	_delay_ms(242);

	while (1) {
		//uart_clear();

		uart_putc(127);
		uart_putc(128);
		uart_putc(1);
		uart_putc(7);
		uart_putc(18);
		uart_putc(2);
		uart_get_date();
		if (c == 0xEE) {
			//punkty = punkty + 1;

			d = uart_getc();

			if (d == 1) {
				punkty = punkty + 1;
			}

			if (d == 2) {
				punkty = punkty + 2;
			}

			if (d == 3) {
				punkty = punkty + 5;
			}

			if (d == 4) {
				punkty = punkty + 10;
			}
			if (d == 5) {
				punkty = punkty + 20;
			}
		}

		_delay_ms(250);

		uart_putc(127);
		uart_putc(0);
		uart_putc(1);
		uart_putc(7);
		uart_putc(17);
		uart_putc(136);
		uart_get_date();

		if (c == 0xEE) {
			//punkty = punkty + 1;

			d = uart_getc();

			if (d == 1) {
				punkty = punkty + 1;
			}

			if (d == 2) {
				punkty = punkty + 2;
			}

			if (d == 3) {
				punkty = punkty + 5;
			}

			if (d == 4) {
				punkty = punkty + 10;
			}
			if (d == 5) {
				punkty = punkty + 20;
			}
		}

		if (punkty) {	//_delay_ms(20);
			PORT_w_gry_0;
			_delay_ms(50);
			PORT_w_gry_1;
			punkty--;
		}

		_delay_ms(250);
		uart_clear();
	}

}

