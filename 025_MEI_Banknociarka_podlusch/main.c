#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

//volatile uint8_t sec = 0, m = 0, start = 1, swieci = 0, starter = 0;
volatile uint8_t start = 1,starter = 0,c = 0, d = 0;

//volatile uint8_t p = 1, j = 0, pintka = 0, c = 0, d = 0;
//volatile uint16_t min = 1, pom = 0, pomo = 0, przerwa = 100, czas = 100,
//		punkty = 0, i = 0;

volatile uint16_t i = 0;


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
	// 7 bitów danych, 1 b it stopu, even bit
	UCSRC = (1 << URSEL) | (2 << UCSZ0) | (1 << UPM1);

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
	while (!uart_ischar()) {
		if (start == 1) {

			_delay_ms(240);
			uart_putc(2);
			uart_putc(8);
			uart_putc(17);
			uart_putc(0);
			uart_putc(28);
			uart_putc(4);
			uart_putc(3);
			uart_putc(1);
		}
	}

	// Dane z bufora
	return UDR;
}
volatile int poszlo = 1;

int main(void) {
	//LCD_Initalize();
	//LCD_Clear();
	//LCD_WriteText("   ");
//	LCD_GoTo(0, 1);
	//LCD_WriteText("    ");

	_delay_ms(2000);

	DDR_jedynka_wy;

	PORT_jedynka_wy_0;

	uart_init(RS_UBRR);
	//_delay_ms(2000);

	uart_putc(2);
	uart_putc(8);
	uart_putc(97);
	uart_putc(127);
	uart_putc(127);
	uart_putc(127);
	uart_putc(3);
	uart_putc(22);

	uart_getc();
	start = 0;

	_delay_ms(226);

	uart_putc(2);
	uart_putc(8);
	uart_putc(16);
	uart_putc(0);
	uart_putc(28);
	uart_putc(4);
	uart_putc(3);
	uart_putc(0);

	_delay_ms(529);

	uart_putc(2);
	uart_putc(8);
	uart_putc(17);
	uart_putc(0);
	uart_putc(28);
	uart_putc(4);
	uart_putc(3);
	uart_putc(1);

	_delay_ms(226);

	uart_putc(2);
	uart_putc(8);
	uart_putc(16);
	uart_putc(0);
	uart_putc(28);
	uart_putc(4);
	uart_putc(3);
	uart_putc(0);

	_delay_ms(740);

	uart_putc(2);
	uart_putc(8);
	uart_putc(17);
	uart_putc(0);
	uart_putc(28);
	uart_putc(4);
	uart_putc(3);
	uart_putc(1);

	_delay_ms(226);

	uart_putc(2);
	uart_putc(8);
	uart_putc(16);
	uart_putc(0);
	uart_putc(28);
	uart_putc(4);
	uart_putc(3);
	uart_putc(0);

	_delay_ms(226);

	uart_putc(2);
	uart_putc(8);
	uart_putc(17);
	uart_putc(0);
	uart_putc(28);
	uart_putc(4);
	uart_putc(3);
	uart_putc(1);

	_delay_ms(226);

	uart_putc(2);
	uart_putc(8);
	uart_putc(16);
	uart_putc(0);
	uart_putc(28);
	uart_putc(4);
	uart_putc(3);
	uart_putc(0);

	_delay_ms(226);

	uart_putc(2);
	uart_putc(8);
	uart_putc(17);
	uart_putc(0);
	uart_putc(28);
	uart_putc(4);
	uart_putc(3);
	uart_putc(1);

	_delay_ms(226);

	uart_putc(2);
	uart_putc(8);
	uart_putc(16);
	uart_putc(127);
	uart_putc(28);
	uart_putc(4);
	uart_putc(3);
	uart_putc(127);

	_delay_ms(226);

	uart_putc(2);
	uart_putc(8);
	uart_putc(17);
	uart_putc(127);
	uart_putc(28);
	uart_putc(4);
	uart_putc(3);
	uart_putc(126);

	_delay_ms(226);

	uart_putc(2);
	uart_putc(17);
	uart_putc(112);
	uart_putc(8);
	uart_putc(127);
	uart_putc(92);
	uart_putc(4);
	uart_putc(0);
	uart_putc(0);
	uart_putc(0);
	uart_putc(0);
	uart_putc(0);
	uart_putc(14);
	uart_putc(86);
	uart_putc(26);
	uart_putc(3);
	uart_putc(12);

	while (1) {

		_delay_ms(226);

		uart_putc(2);
		uart_putc(8);
		uart_putc(17);
		uart_putc(127);
		uart_putc(28);
		uart_putc(4);
		uart_putc(3);
		uart_putc(126);
		c = uart_getc();
		c = uart_getc();
		c = uart_getc();
		c = uart_getc();
		c = uart_getc();
		c = uart_getc();
		c = uart_getc();

		d = uart_getc();
		d = uart_getc();
		//c = uart_getc();

		//napisz(2);

		_delay_ms(226);

		uart_putc(2);
		uart_putc(8);
		uart_putc(16);
		uart_putc(127);
		uart_putc(28);
		uart_putc(4);
		uart_putc(3);
		uart_putc(127);
		c = uart_getc();
		c = uart_getc();
		c = uart_getc();
		c = uart_getc();
		c = uart_getc();
		c = uart_getc();
		c = uart_getc();

		d = uart_getc();
		d = uart_getc();
		//	c = uart_getc();

		//napisz(2);
		if (c == 4) {
			_delay_ms(226);

			uart_putc(2);
			uart_putc(8);
			uart_putc(17);
			uart_putc(127);
			uart_putc(60);
			uart_putc(4);
			uart_putc(3);
			uart_putc(94);
			starter = 1;

		}
		if (starter) {

			if (d == 8) {
				for (i = 0; i < 1; i++) {
					PORT_jedynka_wy_1;
					_delay_ms(100);
					PORT_jedynka_wy_0;
					_delay_ms(100);
				}
				starter = 0;
			}

			if (d == 16) {
				for (i = 0; i < 2; i++) {
					PORT_jedynka_wy_1;
					_delay_ms(100);
					PORT_jedynka_wy_0;
					_delay_ms(100);
				}
				starter = 0;
			}

			if (d == 24) {
				for (i = 0; i < 5; i++) {
					PORT_jedynka_wy_1;
					_delay_ms(100);
					PORT_jedynka_wy_0;
					_delay_ms(100);
				}
				starter = 0;
			}

			if (d == 32) {
				for (i = 0; i < 10; i++) {
					PORT_jedynka_wy_1;
					_delay_ms(100);
					PORT_jedynka_wy_0;
					_delay_ms(100);
				}
				starter = 0;
			}
		}
	}
}
