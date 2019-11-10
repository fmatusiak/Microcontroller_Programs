
#include <avr/io.h>
#include <util/delay.h>

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

volatile int poszlo = 1;

int main(void) {
	int i;

	DDR_dwojka_wy;
		PORT_dwojka_wy_1;



	_delay_ms(4000);

//	LCD_Initalize();
//	LCD_Clear();

	uart_init(RS_UBRR);
	_delay_ms(1000);
	// coin acceptor
	uartPut(2, 0, 1, 254, 0);
	_delay_ms(100);
	uartPut(2, 0, 1, 245, 0);
	_delay_ms(100);
	uartPut(2, 0, 1, 244, 0);
	_delay_ms(100);
	uartPut(2, 0, 1, 192, 0);

	_delay_ms(100);

	uartPut(2, 0, 1, 246, 0);
	_delay_ms(100);
	uartPut(2, 0, 1, 242, 0);
	_delay_ms(100);
	uartPut(2, 0, 1, 241, 0);
	_delay_ms(100);
	uartPut(2, 0, 1, 4, 0);
	_delay_ms(100);
					uartPut(2, 1, 1, 184, (uint8_t[]) {1});
	_delay_ms(100);
	uartPut(2, 1, 1, 184, (uint8_t[]) {2});
	_delay_ms(100);
	uartPut(2, 1, 1, 184, (uint8_t[]) {3});
	_delay_ms(100);
	uartPut(2, 1, 1, 184, (uint8_t[]) {4});
	_delay_ms(100);
	uartPut(2, 1, 1, 184, (uint8_t[]) {5});
	_delay_ms(100);
	uartPut(2, 1, 1, 184, (uint8_t[]) {6});
	_delay_ms(100);
	uartPut(2, 1, 1, 184, (uint8_t[]) {7});
	_delay_ms(100);
	uartPut(2, 1, 1, 184, (uint8_t[]) {8});
	_delay_ms(100);
	uartPut(2, 2, 1, 231, (uint8_t[]) {255,255});
	_delay_ms(100);
	// coin i

	while (1) {
//===========================

		uartPut(2, 0, 1, 229, 0);
		for (i = 0; i < 21; i++) {
			bufferC[i] = uart_getc();
			if (firstRunC == 1) {
				bufferOldC[i] = bufferC[i];
				firstRunC = 0;
			}
		}

		if (bufferC[10] == 1 || bufferC[10] == 2 || bufferC[10] == 3
				|| bufferC[10] == 4 || bufferC[10] == 5 || bufferC[10] == 6
				|| bufferC[10] == 7 || bufferC[10] == 8 || bufferC[10] == 9
				|| bufferC[10] == 10) {

			if (eventC != bufferC[9]) {
				eventC = bufferC[9];

				if (bufferEqC() == 1) {
					if ((bufferC[11] == 1) || (bufferC[11] == 2)
							|| (bufferC[11] == 3) || (bufferC[11] == 4)
							|| (bufferC[11] == 5) || (bufferC[11] == 6)) {

						// PENDING CREDIT
						if (bufferC[10] == 1) {
							punkty++;
						}
						if (bufferC[10] == 2) {
							punkty++;
						}
						if (bufferC[10] == 3) {
							punkty++;
						}
						if (bufferC[10] == 4) {
							punkty++;
						}
						if (bufferC[10] == 5) {
							punkty++;
						}
						if (bufferC[10] == 6) {
							punkty++;
						}
						if (bufferC[10] == 7) {
							punkty++;
						}
						if (bufferC[10] == 8) {
							punkty++;
						}
						if (bufferC[10] == 9) {
							punkty++;
						}
					}
				}
			}
		}
	for (i = 0; i < 21; i++) {
		bufferOldC[i] = bufferC[i];
	}
	_delay_ms(20);
	if (punkty) {
		PORT_dwojka_wy_0;
		_delay_ms(50);
		PORT_dwojka_wy_1;
		punkty--;

	}

//============================

//==========================

//=============================================

// ========================================= banknociarka nabijanie =======================================================

//  ====================================== koniec banknocarka nabijanie ================================================

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

