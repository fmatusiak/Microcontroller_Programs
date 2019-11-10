#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

// software

// =======================
volatile uint8_t data_controler[25] = { 0 }, data_acceptor[25] = { 0 };

volatile uint8_t nabij = 0, FL_88 = 0, FL_89 = 0, FL_8F = 0, FL_8A = 0;
volatile uint8_t l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0, l7 = 0, l8 = 0;
//0x88
volatile uint8_t v0x88h[] = { 0xFC, 0x30, 0x88, 0x45, 0x28, 0x45, 0x55, 0x52,
		0x35, 0x29, 0x2D, 0x33, 0x30, 0x2D, 0x53, 0x44, 0x33, 0x20, 0x49, 0x44,
		0x30, 0x30, 0x33, 0x2D, 0x30, 0x35, 0x76, 0x35, 0x33, 0x32, 0x2D, 0x32,
		0x33, 0x20, 0x32, 0x37, 0x4F, 0x43, 0x54, 0x31, 0x37, 0x20, 0x46, 0x32,
		0x38, 0x39, 0xEA, 0x96 };

//0x89
volatile uint8_t v0x89h[] = { 0xFC, 0x09, 0x89, 0x42, 0x30, 0x34, 0x20, 0x26,
		0x81 };

//0x8F
volatile uint8_t v0x8Fh[] = { 0xFC, 0x08, 0x8F, 0x48, 0x98, 0x8A, 0x9B, 0x08 };

//0x8A
volatile uint8_t v0x8Ah[] = { 0xFC, 0x25, 0x8A, 0x61, 0x00, 0x00, 0x00, 0x62,
		0xE0, 0x05, 0x00, 0x63, 0xE0, 0x0A, 0x00, 0x64, 0xE0, 0x14, 0x00, 0x65,
		0xE0, 0x32, 0x00, 0x66, 0xE0, 0x0A, 0x01, 0x67, 0xE0, 0x14, 0x01, 0x68,
		0xE0, 0x32, 0x01, 0x05, 0xC1 };

//

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t ubrr);
void uart_putc(uint8_t data);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);

void uart_putc_s(uint8_t data);
int czytaj_bajt(void);

int main(void) {
	DDR_rxs_we;
	rxs_we_VCC;
	DDR_txs;
	PORT_txs_1;

	_delay_ms(2000);

	uart_init(RS_UBRR);
	_delay_ms(2000);


	while (1) {
		data_controler[0] = uart_getc();
		if (data_controler[0] == 252) {
			data_controler[1] = uart_getc();

			for (uint8_t i = 2; i < data_controler[1]; i++) {
				data_controler[i] = uart_getc();
			}

			for (uint8_t i = 0; i < data_controler[1]; i++) {
				uart_putc_s(data_controler[i]);

				if (data_controler[i] == 136) {
					FL_88 = 1;
				}

				if (data_controler[i] == 136) {
					FL_89 = 1;
				}

				if (data_controler[i] == 136) {
					FL_8F = 1;
				}
				if (data_controler[i] == 136) {
					FL_8A = 1;
				}

				if (i != 1) {
					data_controler[i] = 0;
				}
			}
			data_controler[1] = 0;
		}

		if (FL_88 == 1) {
			FL_88 = 0;
			for (uint8_t i = 0; i < 48; i++) {
				uart_putc(v0x88h[i]);
			}
		}

		else if ((FL_89 == 1)) {
			FL_89 = 0;
			for (uint8_t i = 0; i < 9; i++) {
				uart_putc(v0x89h[i]);
			}

		}

		else if ((FL_8F == 1)) {
			FL_8F = 0;
			for (uint8_t i = 0; i < 8; i++) {
				uart_putc(v0x8Fh[i]);
			}

		}

		else if ((FL_8A == 1)) {
			FL_8A = 0;
			for (uint8_t i = 0; i < 37; i++) {
				uart_putc(v0x8Ah[i]);
			}

		}

		else {
			data_acceptor[0] = czytaj_bajt();
			data_acceptor[1] = czytaj_bajt();

			for (uint8_t i = 2; i < data_acceptor[1]; i++) {
				data_acceptor[i] = czytaj_bajt();
			}

			if ((data_acceptor[2] == 0x13) && (data_acceptor[3] == 0x64)) {//100
				data_acceptor[3] = 0x63;
				data_acceptor[4] = 0xA2;
				data_acceptor[5] = 0xD8;

			}

			if ((data_acceptor[2] == 0x13) && (data_acceptor[3] == 0x65)) {//200
				data_acceptor[3] = 0x64;
				data_acceptor[4] = 0x1D;
				data_acceptor[5] = 0xAC;
			}

			if ((data_acceptor[2] == 0x13) && (data_acceptor[3] == 0x66)) {//500
				data_acceptor[3] = 0x65;
				data_acceptor[4] = 0x94;
				data_acceptor[5] = 0xBD;
			}

			if ((data_acceptor[2] == 0x13) && (data_acceptor[3] == 0x67)) {//1000
				data_acceptor[3] = 0x66;
				data_acceptor[4] = 0x0F;
				data_acceptor[5] = 0x8F;
			}
			if ((data_acceptor[2] == 0x13) && (data_acceptor[3] == 0x68)) {//2000
				data_acceptor[3] = 0x67;
				data_acceptor[4] = 0x86;
				data_acceptor[5] = 0x9E;
			}

			if ((data_acceptor[2] == 0x13) && (data_acceptor[3] == 0x69)) {//5000
				data_acceptor[3] = 0x68;
				data_acceptor[4] = 0x71;
				data_acceptor[5] = 0x66;
			}

			for (uint8_t i = 0; i < data_acceptor[1]; i++) {
				uart_putc(data_acceptor[i]);

				if (i != 1) {
					data_acceptor[i] = 0;
				}
			}
			data_acceptor[1] = 0;

		}

	}
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

int czytaj_bajt(void) {
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
uint8_t uart_ischar(void) {
	// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc(void) {
	// Czy w buforze s¹ dane?
	while (!uart_ischar())
		;

	return UDR;
}
