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

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
void uart_putc_s(uint8_t data);
int czytaj_bajt();

volatile int poszlo = 1;

int main(void) {
	uint16_t i;
	DDR_rxs_we;
	rxs_we_VCC;
	DDR_txs;
	PORT_txs_1;
	DDR_puls;
	PORT_puls_0;

	uart_init(RS_UBRR);
	_delay_ms(1000);
	// coin acceptor

	while (1) {
/*//===========================
		data_controler[0] = uart_getc();
		if (data_controler[0] == 252) {
			data_controler[1] = uart_getc();

			for (i = 2; i < data_controler[1]; i++) {
				data_controler[i] = uart_getc();
			}

			for (i = 0; i < data_controler[1]; i++) {
				uart_putc(data_controler[i]);

				if (data_controler[i] == 136) {
					FL_vr = 1;
				}

				if (i != 1) {
					data_controler[i] = 0;
				}
			}
			data_controler[1] = 0;
		}

		if (FL_vr == 1) {
			FL_vr = 0;
			for (i = 0; i < 46; i++) {
				uart_putc_s(version[i]);

			}
		} else {
			data_acceptor[0] = czytaj_bajt();
			data_acceptor[1] = czytaj_bajt();
			uart_putc_s(data_acceptor[0]);
			uart_putc_s(data_acceptor[1]);

			for (i = 2; i < data_acceptor[1]; i++) {
				data_acceptor[i] = czytaj_bajt();
			}
			for (i = 0; i < data_acceptor[1]; i++) {
				uart_putc_s(data_acceptor[i]);
				if (i != 1) {
					data_acceptor[i] = 0;
				}
			}
			data_acceptor[1] = 0;

		}*/
		for(i = data_controler[i]; i== 0 ;i--)
		{
			data_controler[i] = 0;
		}

		data_controler[0] = czytaj_bajt();
		data_controler[1] = czytaj_bajt();
		for (i = 2; i < data_controler[1]; i++) {
			data_controler[i] = czytaj_bajt();
		}

		for (i = 0; i < data_controler[1]; i++) {
			uart_putc(data_controler[i]);
		}


		//uart_putc(data_controler[0]);
		//uart_putc_s(data_controler[0]);

// ========================================= banknociarka nabijanie =======================================================
//  ====================================== koniec banknocarka nabijanie ===================================================
	}
}

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

// === cctalk

