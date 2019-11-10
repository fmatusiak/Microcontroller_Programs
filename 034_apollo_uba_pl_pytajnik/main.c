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
		dawaj = 1, czascoin = 0, banknot = 0, step = 0, startnabij = 0,
		bandalej = 0, banknoty = 0;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);


int bufferEq(void);
void wyj1Flash(int count);

int main(void) {

	DDR_coin_we;
	coin_we_VCC;

	uart_init(RS_UBRR);
	_delay_ms(2000);

	while (1) {
		if (banknot == 0) {
			if (banknoty) {
				banknot = 1;
				banknoty = banknoty - 1;
			}

		}

		buffer[i] = uart_getc();

		if (banknot) {
			if ((buffer[i] == 105) && (bandalej > 20)) {
				_delay_ms(3);
				_delay_ms(3);
				uartPut(2, 11, 32, 2,
						(uint8_t[] ) { 16, 0, 0, 84, 30, 3, 115 });
				bandalej = bandalej + 1;
			}
			if ((buffer[i] == 104) && (bandalej > 20)) {
				_delay_ms(3);
				_delay_ms(3);
				if ((bandalej == 25) || (bandalej == 26)) {
					uartPut(2, 30, 112, 2, (uint8_t[] ) { 17, 16, 0, 0, 84, 30,
									0, 67, 90, 75, 48, 48, 49, 43, 48, 50, 0,
									67, 65, 66, 65, 0, 0, 0, 3, 108 });
					banknot = 0;
				} else {
					uartPut(2, 11, 33, 2, (uint8_t[] ) { 16, 0, 0, 84, 30, 3,
									114 });
					bandalej = bandalej + 1;

				}

			}

			if ((buffer[i] == 104) && (bandalej > 8) && (bandalej < 21)) {
				_delay_ms(3);
				_delay_ms(3);
				uartPut(2, 30, 113, 2, (uint8_t[] ) { 4, 16, 0, 0, 84, 30, 0,
								67, 90, 75, 48, 48, 49, 43, 48, 50, 0, 67, 65,
								66, 65, 0, 0, 0, 3, 120 });
				bandalej = 21;
			}

			if ((buffer[i] == 105) && (bandalej < 15)) {
				_delay_ms(3);
				_delay_ms(3);
				uartPut(2, 11, 32, 2,
						(uint8_t[] ) { 16, 0, 0, 84, 30, 3, 115 });
				bandalej = bandalej + 1;
			}
			if ((buffer[i] == 104) && (bandalej < 15)) {
				_delay_ms(3);
				_delay_ms(3);
				uartPut(2, 11, 33, 2,
						(uint8_t[] ) { 16, 0, 0, 84, 30, 3, 114 });
				bandalej = bandalej + 1;
			}
			if (buffer[i] == 73) {
				_delay_ms(3);
				uartPut(2, 30, 112, 2, (uint8_t[] ) { 4, 16, 0, 0, 84, 30, 0,
								67, 90, 75, 48, 48, 49, 43, 48, 50, 0, 67, 65,
								66, 65, 0, 0, 0, 3, 121 });
			}
			if (banknot == 0) {
				bandalej = 0;
			}
		} else {
			if (start == 1) {

				if (buffer[i] == 105) {
					_delay_ms(3);
					_delay_ms(3);
					uartPut(2, 11, 32, 1, (uint8_t[] ) { 16, 0, 0, 84, 30, 3,
									112 });
				}
				if (buffer[i] == 104) {
					_delay_ms(3);
					_delay_ms(3);
					uartPut(2, 11, 33, 1, (uint8_t[] ) { 16, 0, 0, 84, 30, 3,
									113 });

				}

				if (buffer[i] == 97) {
					_delay_ms(8);
					uartPut(2, 37, 97, 67, (uint8_t[] ) { 90, 75, 0, 0, 0, 0, 0,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 22 });

				}

				if (buffer[i] == 108) {
					_delay_ms(8);
					uartPut(2, 25, 96, 115, (uint8_t[] ) { 99, 56, 53, 48, 55,
									0, 127, 127, 127, 127, 127, 127, 127, 127,
									127, 127, 127, 127, 127, 3, 28 });

				}

				if (buffer[i] == 20) {
					_delay_ms(3);
					_delay_ms(3);

					uartPut(2, 11, 32, 1, (uint8_t[] ) { 16, 0, 0, 84, 30, 3,
									112 });
				}
				if (buffer[i] == 21) {
					_delay_ms(3);
					_delay_ms(3);

					uartPut(2, 11, 33, 1, (uint8_t[] ) { 16, 0, 0, 84, 30, 3,
									113 });

				}

			}
// ===================================================== start start == 0 ===============================================
			if (start == 0) {
				if (buffer[i] == 16) {
					buffer[i] = uart_getc();
					if (buffer[i] == 0) {
						_delay_ms(3);
						_delay_ms(3);
						uartPut(2, 11, 32, 0, (uint8_t[] ) { 16, 1, 0, 84, 30,
										3, 112 });
						_delay_ms(2);
					}
					if (buffer[i] == 1) {
						_delay_ms(3);

						uartPut(2, 30, 113, 2,
								(uint8_t[] ) { 0, 16, 1, 0, 84, 30, 1,
												67, 90, 75, 48, 48, 49, 43, 48,
												50, 0, 67, 65, 66, 65, 0, 0, 0,
												3, 124 });
						_delay_ms(2);
					}
					if (buffer[i] == 2) {
						_delay_ms(3);

						uartPut(2, 30, 112, 2,
								(uint8_t[] ) { 0, 16, 1, 0, 84, 30, 2,
												67, 90, 75, 48, 48, 50, 43, 48,
												50, 0, 66, 65, 66, 65, 0, 0, 0,
												3, 124 });
						_delay_ms(2);
					}
					if (buffer[i] == 3) {
						_delay_ms(3);

						uartPut(2, 30, 113, 2,
								(uint8_t[] ) { 0, 16, 1, 0, 84, 30, 3,
												67, 90, 75, 48, 48, 53, 43, 48,
												50, 0, 66, 65, 66, 66, 0, 0, 0,
												3, 120 });
						_delay_ms(2);
					}
					if (buffer[i] == 4) {
						_delay_ms(3);

						uartPut(2, 30, 112, 2,
								(uint8_t[] ) { 0, 16, 1, 0, 84, 30, 4,
												67, 90, 75, 48, 48, 53, 43, 48,
												50, 0, 68, 65, 66, 66, 0, 0, 0,
												3, 120 });
						_delay_ms(2);
					}
					if (buffer[i] == 5) {
						_delay_ms(3);

						uartPut(2, 30, 113, 2,
								(uint8_t[] ) { 0, 16, 1, 0, 84, 30, 5,
												67, 90, 75, 48, 48, 49, 43, 48,
												51, 0, 67, 65, 66, 66, 0, 0, 0,
												3, 122 });
						_delay_ms(2);
					}
					if (buffer[i] == 6) {
						_delay_ms(3);
						uartPut(2, 30, 112, 2,
								(uint8_t[] ) { 0, 16, 1, 0, 84, 30, 6,
												67, 90, 75, 48, 48, 50, 43, 48,
												51, 0, 65, 65, 66, 66, 0, 0, 0,
												3, 121 });
						_delay_ms(2);
					}
					if (buffer[i] == 7) {
						_delay_ms(3);

						uartPut(2, 30, 113, 2,
								(uint8_t[] ) { 0, 16, 1, 0, 84, 30, 7,
												67, 90, 75, 48, 48, 50, 43, 48,
												51, 0, 66, 65, 66, 66, 0, 0, 0,
												3, 122 });
						_delay_ms(2);
					}
					if (buffer[i] == 8) {
						_delay_ms(3);
						start = 1;
						_delay_ms(3);

						uartPut(2, 30, 112, 2, (uint8_t[] ) { 0, 16, 1, 0, 84,
										30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										0, 0, 0, 0, 0, 0, 3, 55 });
						_delay_ms(2);

					}

				}
			}

			// ================================================== end start == 0 ========================================

		}
	}
} //

// =================================== koniec nri cctalk wrzutnik ==========================================

// FUNCTIONS

void uart_init(uint16_t ubrr) {
// Ustawienie prêdkoœci transmisji
	UBRRH = (uint8_t) (ubrr >> 8);
	UBRRL = (uint8_t) ubrr;

// W³¹czenie nadajnika i odbiornika
	UCSRB = (1 << RXEN) | (1 << TXEN);

	// Ustawienie formatu ramki:
	// 7 bitów danych, 1 b it stopu, even bit
	UCSRC = (1 << URSEL) | (2 << UCSZ0) | (1 << UPM1);

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
		/*if (!(PIN_coin_we)) {
		 banknot =1;
		 }*/
		if (!(PIN_coin_we)) {
			startnabij = 1;
			step = 0;
			if (dawaj == 1) {
				banknoty = banknoty + 1;
				dawaj = 0;

			}
		} else {
			startnabij = 0;
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
	for (int i = 0; i < dataCount - 4; i++) {
		uart_putc(data[i]);
		checkSum += data[i];
	}
	checkSum %= 256;
	checkSum = 256 - checkSum;
	//uart_putc(checkSum);
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


// ========================================================================

// ========================================================================


void wyj1Flash(int count) {
	for (int i = 0; i < count; i++) {

	}
}

