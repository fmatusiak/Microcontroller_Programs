/*
 Zabezpieczenie nv10 nri z kwarcem wersja finalana
 zegar kwarcowy 8 MHZ
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"

volatile uint16_t buffer[21], bufferOld[21], bank = 0, event = -1, firstRun = 1,
		d = 0, g = 0, i = 0, counter = 0, n1 = 0, m1 = 0, n2 = 0, m2 = 0,
		n3 = 0, m3 = 0, n4 = 0, m4 = 0, n5 = 0, m5 = 0, stop = 0, coin = 0,
		coinh = 0, buffers[21], j = 0, monety = 0, l1 = 0, l2 = 0, l3 = 0, l4 =
				0, l5 = 0, l6 = 0, l7 = 0, l8 = 0, bezwrzutnika = 0, start = 0,
		dawaj = 1, czascoin = 0;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
void uart_putc(uint8_t);
void uart_putc_s(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
void uartPutS(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
int bufferEq(void);
void wyj1Flash(int count);

int main(void) {
	DDR_rxs_we;
	rxs_we_VCC;

	DDR_coin_we;
	coin_we_VCC;

	DDR_txs;
	PORT_txs_1;

	uart_init(RS_UBRR);
	_delay_ms(2000);

	while (1) {
		/*	if (!(PIN_coin_we)) {
		 counter += 1;
		 if (counter == 256)
		 counter = 1;
		 n5 = n4;
		 m5 = m4;
		 n4 = n3;
		 m4 = m3;
		 n3 = n2;
		 m3 = m2;
		 n2 = m1;
		 n2 = n1;
		 n1 = 1;
		 m1 = 1;
		 start = 1;

		 }*/
		// ok
		// =================== koniec dodanej banknociarki
		// ================= banknociarka czeska software uart =====
		while (buffer[i] != 40) {
			buffer[i] = uart_getc();
		}
		for (i = 1; i < 5; i++) {
			buffer[i] = uart_getc();

		}
		//_delay_ms(50);
		// ================= sprzetowa banknociarka=================

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 245) && (buffer[4] == 226)) {
			uartPut(
					1,
					14,
					40,
					0,
					(uint8_t[]) {66,105,108,108,32,86,97,108,105,100,97,116,111,114});
							_delay_ms(2);
						}

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 1) && (buffer[4] == 214)) {
			uartPut(1, 0, 40, 0, 0);
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 213) && (buffer[4] == 2)) {
			uartPut(1, 1, 40, 0, (uint8_t[]) {3});
					_delay_ms(2);
				}

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
	 			&& (buffer[3] == 249) && (buffer[4] == 222)) {
			uartPut(1, 2, 40, 0, (uint8_t[]) {2,20});
					_delay_ms(2);
				}

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 246) && (buffer[4] == 225)) {
			uartPut(1, 3, 40, 01, (uint8_t[]) {73,84,76});
					_delay_ms(2);
				}

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 244) && (buffer[4] == 227)) {
			uartPut(1, 4, 40, 0, (uint8_t[]) {78,86,49,48});
					_delay_ms(2);
				}

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 192) && (buffer[4] == 23)) {
			uartPut(1, 8, 40, 0, (uint8_t[]) {83,116,97,110,100,97,114,100});
					_delay_ms(2);
				}

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 241) && (buffer[4] == 230)) {
			uartPut(1, 9, 40, 0, (uint8_t[]) {78,86,49,48,51,51,55,48,53});
					_delay_ms(2);
				}

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 242) && (buffer[4] == 229)) {
			uartPut(1, 4, 40, 0, (uint8_t[]) {0,56,207,75});
					_delay_ms(2);
				}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 1)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {67,90,48,49,48,48,65});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 2) && (buffer[2] == 1)
				&& (buffer[3] == 156) && (buffer[4] == 67)) {
			uart_getc();
			uart_getc();
			uartPut(1, 3, 40, 0, (uint8_t[]) {100,0,2});
			_delay_ms(2);
		}
		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 2)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {67,90,48,50,48,48,65});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 3)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {67,90,48,53,48,48,65});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 4)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {67,90,49,48,48,48,65});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 5)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {67,90,50,48,48,48,65});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 6)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {67,90,53,48,48,48,65});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 7)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {0,0,0,0,0,0,0});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 2) && (buffer[2] == 1)
				&& (buffer[3] == 156) && (buffer[4] == 0)) {
			uart_getc();
			uart_getc();
			uartPut(1, 3, 40, 0, (uint8_t[]) {0,0,0});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 8)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {0,0,0,0,0,0,0});
			_delay_ms(2);
		}
		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 9)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {0,0,0,0,0,0,0});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 10)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {0,0,0,0,0,0,0});
			_delay_ms(2);
		}
		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 11)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {0,0,0,0,0,0,0});
			_delay_ms(2);
		}
		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 12)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {0,0,0,0,0,0,0});
			_delay_ms(2);
		}
		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 13)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {0,0,0,0,0,0,0});
			_delay_ms(2);
		}
		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 14)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {0,0,0,0,0,0,0});
			_delay_ms(2);
		}
		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 15)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {0,0,0,0,0,0,0});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 157) && (buffer[4] == 16)) {
			uart_getc();
			uartPut(1, 7, 40, 0, (uint8_t[]) {0,0,0,0,0,0,0});
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 232) && (buffer[4] == 239)) {
			uartPut(1, 1, 40, 0, (uint8_t[]) {0});
					_delay_ms(2);
				}

		if ((buffer[0] == 40) && (buffer[1] == 2) && (buffer[2] == 1)
				&& (buffer[3] == 231) && (buffer[4] == 63)) {
			uart_getc();
			uart_getc();
			uartPut(1, 0, 40, 0, 0);
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 0) && (buffer[2] == 1)
				&& (buffer[3] == 159) && (buffer[4] == 56)) {
			uartPut(1, 11, 40, 0,
					(uint8_t[]) {counter,n1,m1,n2,m2,n3,m3,n4,m4,n5,m5});
							_delay_ms(2);
						}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 228) && (buffer[4] == 0)) {
			//	_delay_ms(2);
		//	counter += 1;
		//n1 = 0;
		//	m1 = 0;
			uart_getc();
			uartPut(1, 0, 40, 0, 0);
			_delay_ms(2);
		}

		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 228) && (buffer[4] == 1)) {
			//_delay_ms(2);
		//	counter += 1;
		//	n1 = 0;
		//	m1 = 0;
			uart_getc();
			uartPut(1, 0, 40, 0, 0);
			_delay_ms(2);
		}
		if ((buffer[0] == 40) && (buffer[1] == 1) && (buffer[2] == 1)
				&& (buffer[3] == 154) && (buffer[4] == 1)) {
			uart_getc();
			/*if (start) {
			 counter += 1;
			 if (counter == 256)
			 counter = 1;
			 n5 = n4;
			 m5 = m4;
			 n4 = n3;
			 m4 = m3;
			 n3 = n2;
			 m3 = m2;
			 n2 = m1;
			 n2 = n1;
			 n1 = 1;
			 m1 = 0;
			 start = 0;
			 }*/
			uartPut(1, 0, 40, 0, 0);
			_delay_ms(2);
		}
		// ==========================================================

		//uartPutS(40, 1, 1, 154, (uint8_t[]) {1});
		//_delay_ms(50);

	} //

// =================================== koniec nri cctalk wrzutnik ==========================================

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
	while (!uart_ischar()) {
		if (!(PIN_coin_we)) {

			if (dawaj == 1) {
				counter += 1;
				if (counter == 256)
					counter = 1;
				n5 = n4;
				m5 = m4;
				n4 = n3;
				m4 = m3;
				n3 = n2;
				m3 = m2;
				n2 = m1;
				n2 = n1;
				n1 = 1;
				m1 = 0;
				//while (!(PIN_coin_we)) {
				//	}
				start = 1;
				dawaj = 0;

			}
		} else {

			dawaj = 1;
		}
	}
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

void uartPutS(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,
		uint8_t *data) {
	uart_putc_s(from);
	uart_putc_s(dataCount);
	uart_putc_s(to);
	uart_putc_s(command);
	uint8_t checkSum = from + to + command + dataCount;
	for (int i = 0; i < dataCount; i++) {
		uart_putc_s(data[i]);
		checkSum += data[i];
	}
	checkSum %= 256;
	checkSum = 256 - checkSum;
	uart_putc_s(checkSum);
}
// ========================================================================

// ========================================================================
void uart_putc_s(uint8_t data) {
	int c, k;

	PORT_txs_0;
	_delay_us(104);
	for (c = 0; c <= 7; c++) {
		k = data >> c;

		if (k & 1) {
			PORT_txs_1;
			_delay_us(104);
		}

		else {
			PORT_txs_0;
			_delay_us(104);
		}

	}

	PORT_txs_1;
	_delay_us(104);

}

