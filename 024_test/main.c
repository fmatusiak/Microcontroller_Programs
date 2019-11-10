#include <avr/io.h>
#include <util/delay.h>
//#include "HD44780.h"
#include "stdlib.h"
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

volatile uint8_t start = 1, stak = 0;
volatile uint16_t punkty = 0, punktyb = 0;
volatile uint16_t buffer[21], bufferOld[21], bank = 0, event = -1, firstRun = 1;
volatile uint16_t bufferC[21], bufferOldC[21], bankC = 0, eventC = -1,
		firstRunC = 1;

#define F_CPU 16000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 103

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
void convert_m(uint16_t);
int bufferEq(void);
int bufferEqC(void);

volatile int poszlo = 1;

int main(void) {
	int i;


	uart_init(RS_UBRR);


	while (1) {


		for (i = 0; i < 15; i++) {
			 uart_putc(i);
		}

	_delay_ms(1000);

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

