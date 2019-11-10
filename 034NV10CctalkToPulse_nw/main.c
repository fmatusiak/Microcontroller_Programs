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

volatile uint8_t BillEvent = 0;
#define BILL_ACCEPTOR 40

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
int bufferEq(void);
int bufferEqC(void);
void Bill_Check_Buffor(void);
void ccTalk_send(uint8_t from, uint8_t dataCount, uint8_t command,
		uint8_t *data);

void uart_clear(void);
uint8_t ccTalk_recive(uint8_t *datarecive, uint8_t from);
volatile int poszlo = 1;

int main(void) {
	DDR_puls;
	PORT_puls_1;
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

	while (1) {
//===========================
		_delay_ms(100);
		Bill_Check_Buffor();
		uart_clear();

		if (punkty) {
			punkty--;
			PORT_puls_0;
			_delay_ms(30);
			PORT_puls_1;

		}

// ========================================= banknociarka nabijanie =======================================================
//  ====================================== koniec banknocarka nabijanie ===================================================
	}
}
void ccTalk_send(uint8_t from, uint8_t dataCount, uint8_t command,
		uint8_t *data) {
	_delay_ms(1);
	uart_clear();
	uart_putc(from);
	uart_putc(dataCount);
	uart_putc(1);
	uart_putc(command);
	uint8_t checkSum = from + 1 + command + dataCount;

	for (uint8_t i = 0; i < dataCount; i++) {
		uart_putc(data[i]);
		checkSum += data[i];
	}
	checkSum = 256 - checkSum;

	uart_putc(checkSum);
}

void uart_clear(void) {
	uint8_t clr;
	while ( UCSRA & (1 << RXC)) {
		clr = UDR;
	}
}

void Bill_Check_Buffor(void) {
	uint8_t datarecive[30] = { 0 };
	ccTalk_send(BILL_ACCEPTOR, 0, 159, (uint8_t[] ) { 0 });

	if (ccTalk_recive(datarecive, BILL_ACCEPTOR)) {
		if (*(datarecive + 4) != BillEvent) {
			BillEvent = *(datarecive + 4);
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 1)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 1 });
				_delay_ms(50);
				punkty += 1;

			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 2)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 1 });
				_delay_ms(50);
				punkty += 2;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 3)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 1 });
				_delay_ms(50);
				punkty += 5;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 4)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 1 });
				_delay_ms(50);
				punkty += 10;

			}
		}
	}
}

// FUNCTIONS
uint8_t ccTalk_recive(uint8_t *datarecive, uint8_t from) {
	uint8_t tmp[30] = { 0 };

	for (uint8_t i = 0; i < 10; i++) {
		tmp[i] = uart_getc();
	}

	for (uint8_t i = 0; i < (tmp[1] + tmp[6 + tmp[1]]); i++) {
		tmp[i + 10] = uart_getc();
	}

	if ((tmp[5 + tmp[1]] == 1) && (tmp[7 + tmp[1]] == from)) {
		for (uint8_t i = 0; i < 5 + tmp[6 + tmp[1]]; i++) {
			datarecive[i] = tmp[i + 5 + tmp[1]];
		}
		_delay_ms(50);
		uart_clear();
		return 1;
	}
	_delay_ms(50);
	uart_clear();

	return 1;

}

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

uint8_t uart_getc(void) {
	// Czy w buforze s¹ dane?'
	uint16_t timie_out = 64000;
	while (!uart_ischar()) {

		if (!(--timie_out))
			return 0;
	};
	return UDR;
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

int bufferEq() {
	int bufferEq = -1;
	int i;
	if (firstRun == 1)
		return 1;
	for (i = 10; i < 18; i++) {
		if (buffer[i + 2] == bufferOld[i]) {
			bufferEq = 1;
		} else {
			bufferEq = -1;
			break;
		}
	}
	return bufferEq;
}

int bufferEqC() {
	int bufferEqC = -1;
	int i;
	if (firstRunC == 1)
		return 1;
	for (i = 10; i < 18; i++) {
		if (bufferC[i + 2] == bufferOldC[i]) {
			bufferEqC = 1;
		} else {
			bufferEqC = -1;
			break;
		}
	}
	return bufferEqC;
}

// === cctalk

