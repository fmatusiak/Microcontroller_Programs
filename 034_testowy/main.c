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
volatile uint8_t automat_on = 1, tmp_automat = 0, nabij = 0, FL_time = 1, test =
		1, min = 0, FL_IN6 = 0;
volatile uint16_t time_out, tmp_time = 0, impuls_time = 5;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
void uart_putc_s(uint8_t data);
int czytaj_bajt(void);
void nabij_impuls(void);
void init_device(void);
void request_status(void);

volatile int poszlo = 1;
void uart_clear(void) {
	uint8_t flu;
	while ( UCSRA & (1 << RXC)) {
		flu = UDR;
	}
}

int main(void) {
	uint16_t i;
	DDR_rxs_we;
	rxs_we_VCC;
	DDR_IN6_IN;
	IN6_IN_VCC;
	DDR_txs;
	PORT_txs_1;
	DDR_puls;
	PORT_puls_0;
	time_out = 0;
	uart_init(RS_UBRR);
	_delay_ms(200);
	// coin acceptor

	uint8_t x[10] = { 0 };
	while (1) {
		for (i = 0; i < 5; i++) {
			x[i] = uart_getc();
		}
		_delay_ms(20);
		for (i = 0; i < 5; i++) {
			uart_putc(x[i] + 1);
		}

		uart_clear();
	}


	init_device();
	while (automat_on) {
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


			for(i =0;i<10;i++)
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
	nabij = 0;
}

// FUNCTIONS

void nabij_impuls() {
	if (nabij) {
		tmp_time++;

		if (FL_time == 1) {
			PORT_puls_1;
			_delay_ms(100);
			PORT_puls_0;
			FL_time = 0;

		}
		if (((tmp_time) == (impuls_time)) && (FL_time == 0)) {
			FL_time = 1;
			tmp_time = 0;
			nabij--;
			time_out = impuls_time;
		}

	} else {
		PORT_puls_0;
	}
}

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

uint8_t uart_ischar() {
// Czy w buforze s� dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc() {
// Czy w buforze s� dane?
//int i = 0;
	while (!uart_ischar()) {
		/*		if (i == 1000) {
		 _delay_us(50);
		 break;
		 }
		 i++;*/
	}

	return UDR;
}

void uart_putc_s(uint8_t data) {

	int c, k, parity = 0;

	PORT_txs_0;
	_delay_us(103);
	for (c = 0; c <= 7; c++) {
		k = data >> c;

		if (k & 1) {
			PORT_txs_1;
			_delay_us(103);
			parity = parity + 1;
		}

		else {
			PORT_txs_0;
			_delay_us(103);
		}

	}
	if (parity % 2 == 0) {

		PORT_txs_0;
		_delay_us(103);
	} else {

		PORT_txs_1;
		_delay_us(103);
	}

	PORT_txs_1;
	_delay_us(103);

}

int czytaj_bajt() {
	int i = 0;
	while ((PIN_rxs_we)) {
		//if (automat_on == 0){

		i += 1;

		if (i == 10000) {
			return 0;
		}
		//}
	}
	i = 0;
	for (int i = 0; i < 117; i++) {

		if ((i > 11) && (i < 22)) {
			if (PIN_rxs_we) {
				l1 += 1;
			}
		}
		if ((i > 21) && (i < 32)) {
			if (PIN_rxs_we) {
				l2 += 1;
			}
		}
		if ((i > 31) && (i < 42)) {
			if (PIN_rxs_we) {
				l3 += 1;
			}
		}
		if ((i > 41) && (i < 52)) {
			if (PIN_rxs_we) {
				l4 += 1;
			}
		}
		if ((i > 51) && (i < 62)) {
			if (PIN_rxs_we) {
				l5 += 1;
			}
		}
		if ((i > 61) && (i < 72)) {
			if (PIN_rxs_we) {
				l6 += 1;
			}
		}
		if ((i > 71) && (i < 82)) {
			if (PIN_rxs_we) {
				l7 += 1;
			}
		}
		if ((i > 81) && (i < 92)) {
			if (PIN_rxs_we) {
				l8 += 1;
			}
		}
		_delay_us(2);
	}
	int liczba = 0;
	if (l1 > 4) {
		liczba += 1;
	}
	if (l2 > 4) {
		liczba += 2;
	}
	if (l3 > 4) {
		liczba += 4;
	}
	if (l4 > 4) {
		liczba += 8;
	}
	if (l5 > 4) {
		liczba += 16;
	}
	if (l6 > 4) {
		liczba += 32;
	}
	if (l7 > 4) {
		liczba += 64;
	}
	if (l8 > 4) {
		liczba += 128;
	}
	l1 = 0;
	l2 = 0;
	l3 = 0;
	l4 = 0;
	l5 = 0;
	l6 = 0;
	l7 = 0;
	l8 = 0;
	return liczba;

}

void uartPut(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,
		uint8_t *data) {
	uart_putc(from);
	uart_putc(dataCount);
	uart_putc(to);
	uart_putc(command);
	uint8_t checkSum = from + to + command + dataCount;
	for (int i = 0; i < dataCount; i++) {
		uart_putc(data[i]);
		checkSum += data[i];
	}
	checkSum %= 256;
	checkSum = 256 - checkSum;
	uart_putc(checkSum);
}

void init_device() {
	request_status();

	_delay_ms(100);

	request_status();
	_delay_ms(100);

	request_status();
	_delay_ms(100);

	uart_putc(252);
	uart_putc(5);
	uart_putc(136);
	uart_putc(111);
	uart_putc(95);
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

