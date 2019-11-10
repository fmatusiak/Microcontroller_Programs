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
void uartPut(uint8_t dataCount, uint8_t *data, uint8_t CRC_L, uint8_t CRC_H);
void uart_clear(void);
void init(void);

volatile uint8_t RUN = 1;

int main(void) {

	//uint16_t test = 0;
	//uint16_t time = 0;

	DDR_puls;
	PORT_puls_1;

	init();
	while (1) {
//===========================

	}
}

// FUNCTIONS

void init(void) {

	uint8_t dane[50];

	for (uint8_t i = 0; i < 5; i++) {
		dane[i] = uart_getc();
	}

	if ((dane[0] == 0xFC) && (dane[1] == 0x05) && (dane[2] == 0x11)
			&& (dane[3] == 0x27) && (dane[4] == 0x56)) {

		uartPut(0x05, (uint8_t[] ) { 0x40 }, 0x2B, 0x15);

	}

	for (uint8_t i = 0; i < 5; i++) {
		dane[i] = uart_getc();
	}

	if ((dane[0] == 0xFC) && (dane[1] == 0x05) && (dane[2] == 0x40)
			&& (dane[3] == 0x2B) && (dane[4] == 0x15)) {

		uartPut(0x05, (uint8_t[] ) { 0x50 }, 0xAA, 0x05);

	}

	for (uint8_t i = 0; i < 5; i++) {
		dane[i] = uart_getc();
	}

	while (RUN) {
		uart_clear();
		dane[0] = uart_getc();

		if (dane[0] == 0xFC) {
			dane[1] = uart_getc();
			for (uint8_t i = 2; i < dane[1]; i++) {
				dane[i] = uart_getc();
			}

			if ((dane[0] == 0xFC) && (dane[1] == 0x05) && (dane[2] == 0x11)
					&& (dane[3] == 0x27) && (dane[4] == 0x56)) {

				uartPut(0x05, (uint8_t[] ) { 0x1B }, 0x7D, 0xF9);
			}

			if ((dane[0] == 0xFC) && (dane[1] == 0x07) && (dane[2] == 0xC6)
					&& (dane[3] == 0x01) && (dane[4] == 0x12)) {

				uartPut(0x07, (uint8_t[] ) { 0xC6, 0x01, 0x12 }, 0xBF, 0x49);
			}

		}
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

void uartPut(uint8_t dataCount, uint8_t *data, uint8_t CRC_L, uint8_t CRC_H) {

	uart_putc(0xFC);
	uart_putc(dataCount);
	for (int i = 0; i < dataCount - 4; i++) {
		uart_putc(data[i]);
	}
	uart_putc(CRC_L);
	uart_putc(CRC_H);
}

// === CrC
