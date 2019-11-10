#include <avr/io.h>
#include <util/delay.h>
//#include "HD44780.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

volatile uint8_t start = 1, stak = 0;
volatile uint16_t punkty = 0;
volatile uint16_t buffer[21], bufferOld[21], bank = 0, event = -1, firstRun = 1;
volatile uint16_t bufferC[21], bufferOldC[21], bankC = 0, eventC = -1,
		firstRunC = 1;
volatile uint16_t dopelnienie = 12, wrz = 0, zmienna = 0, d = 0, stop = 0,
		zmiennaw = 0, dw = 0, stopw = 0, dw2 = 256, i, db = 0, db2 = 256;

volatile uint16_t time_out = 40000, tmp_time = 0, FL_time = 0;

#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
void uart_clear(void);

volatile int poszlo = 1;

int main(void) {

	//uint16_t test = 0;
	//uint16_t time = 0;

	DDR_puls;
	PORT_puls_1;
	_delay_ms(4000);
	_delay_ms(4000);
	_delay_ms(4000);
	_delay_ms(4000);
	_delay_ms(4000);
	uart_init(RS_UBRR);
	_delay_ms(1000);
	// coin acceptor

	uartPut(40, 2, 1, 231, (uint8_t[] ) { 255, 255 });
	_delay_ms(100);
	uartPut(40, 8, 1, 231,
			(uint8_t[] ) { 255, 255, 255, 255, 255, 255, 255, 255 });
	_delay_ms(50);
	uartPut(40, 1, 1, 228, (uint8_t[] ) { 1 });
	_delay_ms(50);
	_delay_ms(100);
	while (1) {
//===========================
		uart_clear();
		_delay_ms(100);
		uartPut(40, 0, 1, 159, 0);

		for (uint8_t i = 0; i < 21; i++) {
			if (i == 10) {
				zmienna = uart_getc();
				d = uart_getc();
				i++;
			} else {
				uart_getc();
			}
		}

		if (d == 0) {
			stop = 0;
		}

		if ((stop == 0)
				&& ((zmienna == 1) || (zmienna == 2) || (zmienna == 3)
						|| (zmienna == 4) || (zmienna == 6) || (zmienna == 7)
						|| (zmienna == 8) || (zmienna == 9)) && (d == 1)) {

			if (zmienna == 1 || zmienna == 6) {
				punkty += 1;
				stop = 1;
			}
			if (zmienna == 2 || zmienna == 7) {

				punkty += 2;
				stop = 1;
			}
			if (zmienna == 3 || zmienna == 8) {

				punkty += 5;
				stop = 1;
			}
			if (zmienna == 4 || zmienna == 9) {

				punkty += 10;
				stop = 1;
			}
			_delay_ms(100);
			uart_putc(40);
			uart_putc(1);
			uart_putc(1);
			uart_putc(154);
			uart_putc(1);
			uart_putc(59);
			for (int i = 0; i < 10; i++) {
				uart_getc();
			}

		}

		if (punkty) {
			PORT_puls_0;
			_delay_ms(50);
			PORT_puls_1;
			punkty--;
		}

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
// 8 bitów danych, 1 b it stopu, brak parzystoœci
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
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
	while (!uart_ischar())
		;
	return UDR;
}

void uart_clear(void) {
	uint8_t clr;
	while ( UCSRA & (1 << RXC)) {
		clr = UDR;
	}
}

//uint8_t uart_getc() {
//// Czy w buforze s¹ dane?
//	uint16_t i = 0;
//	while (!uart_ischar()) {
//
//		if (i >= 45000) {
//
//			break;
//		}
//		i++;
//	}
//
//	return UDR;
//}

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

