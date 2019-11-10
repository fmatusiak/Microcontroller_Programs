#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

volatile uint8_t value_one = 0, value_two = 0, value_three = 0, value_four = 0,
		FL_vr = 0;

volatile uint8_t version[] = { 252, 46, 136, 85, 40, 80, 79, 76, 41, 45, 49, 48,
		45, 83, 83, 32, 73, 68, 48, 48, 51, 45, 48, 51, 86, 50, 51, 48, 45, 52,
		51, 32, 49, 48, 83, 69, 80, 49, 50, 32, 53, 54, 52, 56, 38, 164 };
volatile uint8_t data_controler[25] = { 0 }, data_acceptor[25] = { 0 };

volatile uint8_t l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0, l7 = 0, l8 = 0;
volatile uint8_t tmp_automat = 0, nabij = 0, FL_time = 1, test = 1, min = 0,
		FL_IN6 = 0;
volatile uint16_t time_out, tmp_time = 0, impuls_time = 5;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
uint8_t uart_ischar(void);
void uart_putc_s(uint8_t data);
uint8_t czytaj_bajt(void);
void nabij_impuls(void);
void init_device(void);
void request_status(void);

volatile int poszlo = 1;

int main(void) {
	uint16_t i;

	DDR_puls;
	PORT_puls_0;
	time_out = 0;
	uart_init(RS_UBRR);
	_delay_ms(3000);
	// coin acceptor
	init_device();
	while (1) {
		//===========================

		request_status();

		data_acceptor[0] = czytaj_bajt();
		data_acceptor[1] = czytaj_bajt();

		for (i = 2; i < data_acceptor[1]; i++) {
			data_acceptor[i] = czytaj_bajt();

			if ((data_acceptor[i]) == (0x1A) || (data_acceptor[i]) == (251)
					|| (data_acceptor[i]) == (16) || (data_acceptor[i]) == (172)
					|| (data_acceptor[i]) == (201)
					|| (data_acceptor[i]) == (216)) {
				min = data_acceptor[i];
			}
		}

		_delay_ms(20);

		if (min == 0x1A) { //ukladarka reset
			min = 0;

			for (i = 0; i < 10; i++)
				_delay_ms(500);

			_delay_ms(100);
			init_device();

		}
		if (min == 251) { //ten
			min = 0;

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(65); // request sttusa
			uart_putc_s(162);
			uart_putc_s(4);
			_delay_ms(20);

			for (uint8_t i = 0; i < 10; i++) {
				request_status();
				_delay_ms(20);
			}

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(80); // request sttusa
			uart_putc_s(170);
			uart_putc_s(5);
			_delay_ms(20);

			request_status();
			_delay_ms(20);
			nabij += 1;

			min = 1;

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(80); // request sttusa
			uart_putc_s(170);
			uart_putc_s(5);
			_delay_ms(20);

			request_status();
			_delay_ms(20);

		}

		if (min == 201) { // twenty
			min = 0;

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(65); // request sttusa
			uart_putc_s(162);
			uart_putc_s(4);
			_delay_ms(20);

			for (uint8_t i = 0; i < 10; i++) {
				request_status();
				_delay_ms(20);
			}

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(80); // request sttusa
			uart_putc_s(170);
			uart_putc_s(5);
			_delay_ms(20);

			request_status();
			_delay_ms(20);
			nabij += 2;
			min = 1;

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(80); // request sttusa
			uart_putc_s(170);
			uart_putc_s(5);
			_delay_ms(20);

			request_status();

			_delay_ms(20);
		}

		if (min == 216) {
			min = 0;

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(65); // request sttusa
			uart_putc_s(162);
			uart_putc_s(4);
			_delay_ms(20);

			for (uint8_t i = 0; i < 10; i++) {
				request_status();
				_delay_ms(20);
			}

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(80); // request sttusa
			uart_putc_s(170);
			uart_putc_s(5);
			_delay_ms(20);

			request_status();
			_delay_ms(20);
			nabij += 5;
			min = 1;

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(80); // request sttusa
			uart_putc_s(170);
			uart_putc_s(5);
			_delay_ms(20);

			request_status();

			_delay_ms(20);

		}

		if (min == 172) {
			min = 0;

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(65); // request sttusa
			uart_putc_s(162);
			uart_putc_s(4);
			_delay_ms(20);

			for (uint8_t i = 0; i < 10; i++) {
				request_status();
				_delay_ms(20);
			}

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(80); // request sttusa
			uart_putc_s(170);
			uart_putc_s(5);
			_delay_ms(20);

			request_status();
			_delay_ms(20);
			nabij += 10;

			min = 1;

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(80); // request sttusa
			uart_putc_s(170);
			uart_putc_s(5);
			_delay_ms(20);

			request_status();

			_delay_ms(20);

		}

		if (min == 16) {
			min = 0;
			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(80); // request sttusa
			uart_putc_s(170);
			uart_putc_s(5);
			_delay_ms(20);

			uart_putc_s(252);
			uart_putc_s(5);
			uart_putc_s(17); // request sttusa
			uart_putc_s(39);
			uart_putc_s(86);
			_delay_ms(20);
		}

		nabij_impuls();

	}

}

// FUNCTIONS

void nabij_impuls() {
	if (nabij) {
		PORT_puls_1;
		_delay_ms(100);
		PORT_puls_0;
		nabij--;
	}
}

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

void uart_putc_s(uint8_t data) {
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

uint8_t czytaj_bajt() {
// Czy w buforze s¹ dane?
	int i = 0;
	while (!uart_ischar()) {
		if (i >= 15000) {

			return 0;
		}
		i++;
	}

	return UDR;
}

void init_device() {
	request_status();

	_delay_ms(100);

	request_status();
	_delay_ms(100);

	request_status();
	_delay_ms(100);

	uart_putc_s(252);
	uart_putc_s(5);
	uart_putc_s(136);
	uart_putc_s(111);
	uart_putc_s(95);
	_delay_ms(100);

	uart_putc_s(252);
	uart_putc_s(5);
	uart_putc_s(64); // reset devaice
	uart_putc_s(43);
	uart_putc_s(21);
	_delay_ms(100);

	uart_putc_s(252);
	uart_putc_s(6);
	uart_putc_s(195); // reset devaice
	uart_putc_s(0);
	uart_putc_s(4);
	uart_putc_s(214);
	_delay_ms(100);

	uart_putc_s(252);
	uart_putc_s(6);
	uart_putc_s(199); // reset devaice
	uart_putc_s(252);
	uart_putc_s(135);
	uart_putc_s(140);
	_delay_ms(100);

	uart_putc_s(252);
	uart_putc_s(5);
	uart_putc_s(17); // request sttusa
	uart_putc_s(39);
	uart_putc_s(86);
	_delay_ms(100);

	uart_putc_s(252);
	uart_putc_s(6);
	uart_putc_s(195); // reset devaice
	uart_putc_s(0);
	uart_putc_s(4);
	uart_putc_s(214);
	_delay_ms(100);

	uart_putc_s(252);
	uart_putc_s(6);
	uart_putc_s(199); // reset devaice
	uart_putc_s(252);
	uart_putc_s(135);
	uart_putc_s(140);
	_delay_ms(100);
}

void request_status() {
	uart_putc_s(252);
	uart_putc_s(5);
	uart_putc_s(17); // request sttusa
	uart_putc_s(39);
	uart_putc_s(86);
}

// === cctalk

