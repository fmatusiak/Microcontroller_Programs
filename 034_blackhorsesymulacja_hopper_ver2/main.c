/*
 Zabezpieczenie nv10 nri z kwarcem wersja finalana
 zegar kwarcowy 8 MHZ
 */

#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"

volatile uint16_t buffer[5], bufferOld[21], buffers[21], bank = 0, event = -1;
volatile uint16_t firstRun = 1, toPay = 0, paid = 0, d = 0, g = 0, i = 0,
		counter = 1;
volatile uint16_t n1 = 0, m1 = 0, n2 = 0, m2 = 0, n3 = 0, m3 = 0, n4 = 0,
		m4 = 0, n5 = 0;
volatile uint16_t firstgo = 1, payout = 0;
volatile uint16_t zmienna = 1, coinh = 0;
volatile uint16_t l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0, l7 = 0, l8 = 0,
		zmiennass = 0;
volatile uint16_t pomm = 0, f = 0, bezhoppera = 0, min = 0, start = 0, go = 0,
		unpaid = 0, starter = 0, unpay = 0, flaga_163= 1,bufferaddr[5],flaga_start = 0;



#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);

void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);


int main(void) {
	uint8_t x = 0;
	uart_init(RS_UBRR);




/*	while (x == 0) {

		buffer[0] = uart_getc();

		if (buffer[0] == 1) {
			buffer[1] = uart_getc();
			if (buffer[1] == 253) {
				_delay_ms(3);
				uart_putc(3);
				x = 1;
			}
		}

	}*/
/*		x = 0;
	while (x == 0) {

		buffer[0] = uart_getc();

		if (buffer[0] == 1) {
			buffer[1] = uart_getc();
			if (buffer[1] == 253) {
				_delay_ms(3);
				uart_putc(3);
				x = 1;
			}
		}

	}*/




	while (1) {

		for (int i = 0; i < 5; i++) {
			buffer[i] = uart_getc();
			bufferaddr[i] = buffer[i];

			if (buffer[i] == 3) {
				buffer[0] = 3;
				i = 0;
			}


			if ((bufferaddr[i-1] == 1) && (bufferaddr[i] == 253)  && (flaga_start < 4))
			{
			  	_delay_ms(3);
				uart_putc(3);
				flaga_start ++;
			}

		}

		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 1)) {

			_delay_ms(10);
			uartPut(1, 0, 3, 0, 0);
		}

		if ((buffer[0] == 3) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 164) && (buffer[4]) == 165) {

			_delay_ms(10);
			uartPut(1, 0, 3, 0, (uint8_t[]) {80,97,127,111,117,116});
				}

		if ((buffer[0] == 3) && (buffer[1] == 4) && (buffer[2] == 1)
				&& (buffer[3] == 167)) {

			for (int i = 0; i < 3; i++) {
				buffer[i] = uart_getc();
			}
			unpay = buffer[2];
				_delay_ms(10);
			uartPut(1, 0, 3, 0, 0);
		}

		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 245)) {

			_delay_ms(10);
			uartPut(1, 6, 3, 0, (uint8_t[]) {80,97,121,111,117,116});
				}

		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 246)) {
			_delay_ms(10);
			uartPut(1, 7, 3, 0, (uint8_t[]) {65,122,107,111,121,101,110});
				}

		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 244)) {
			_delay_ms(10);
			uartPut(1, 4, 3, 0, (uint8_t[]) {83,67,72,50});
				}

		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 160)) {

		}

		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 252)) {
			_delay_ms(80);
			uart_putc(3);
		}

		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 168)) {
			_delay_ms(10);
			uartPut(1, 3, 3, 0, (uint8_t[]) {0,0,0});
				}
		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 242)) {
			_delay_ms(10);
			uartPut(1, 3, 3, 0, (uint8_t[]) {15,131,16});
				}

		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 241)) {
			_delay_ms(10);
			uartPut(1, 2, 3, 0, (uint8_t[]) {7,2});
				}

		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 166)) {
			_delay_ms(10);
			uartPut(1, 4, 3, 0, (uint8_t[]) {1,0,0,unpay});
				}

		if ((buffer[0] == 3) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 163)) {
			_delay_ms(10);

			if (flaga_163 == 1)
			{
			uartPut(1, 1, 3, 0, (uint8_t[]) {128});
			flaga_163 = 0;
			}
			else {
				uartPut(1, 1, 3, 0, (uint8_t[]) {6});
			flaga_163 = 1;
			}

			}

			}
		}	//

// FUNCTIONS

void uart_init(uint16_t ubrr) {
// Ustawienie prêdkoœci transmisji
	UBRRH = (uint8_t) (ubrr >> 8);
	UBRRL = (uint8_t) ubrr;
	UCSRB = (0 << RXEN) | (0 << TXEN);
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
	;
	while (!uart_ischar()) {

		/*g += 1;
		 if (g == 500) {
		 i = 0;
		 g = 0;
		 break;
		 }*/

	};
	g = 0;
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

//======================================================================

// ========================================================================

// ==================================================================

