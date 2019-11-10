#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"
#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600// ok
#define RS_UBRR 51

volatile uint8_t sec = 0, m = 0, start = 1, swieci = 0, starter = 0;
volatile uint8_t p = 1, j = 0, pintka = 0, c = 0, d = 0;
volatile uint16_t min = 1, pom = 0, pomo = 0, przerwa = 0, czas = 0, punkty = 0,
		licznik = 0, time = 1600, punktyb = 0, bufor = 0, pi = 0;

volatile uint16_t dlugosc = 90, dopelnienie = 30, rp = 1, starto = 0, kredytrp =
		0, trilogyrp = 0, trilogyrpb = 0, i = 0, stop = 0, zen = 0, licznikk =
		200, block = 0, sequence = 0, zmiennaw = 0, dw = 0, dw2 = 0, stopw = 0,
		zmiennab = 0, zmiennab1 = 0, step = 0, dalej = 0;

volatile uint16_t buffer[21], bufferOld[21], bank = 0, event = -1, firstRun = 1;
volatile uint16_t bufferC[21], bufferOldC[21], bankC = 0, eventC = -1,
		firstRunC = 1;

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
	int i = 0;
	while (!uart_ischar()) {
		i++;
		if (i == 10000) {
			break;
		}
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
volatile int poszlo = 1;

int main(void) {
//

	DDR_kanal_1_we;
	kanal_1_we_VCC;




	_delay_ms(100);


	uart_init(RS_UBRR);

	_delay_ms(2000);

	uart_putc(127);
	uart_putc(128);
	uart_putc(1);
	uart_putc(17);
	uart_putc(101);
	uart_putc(130);
	_delay_ms(242);

	uart_putc(127);
	uart_putc(128);
	uart_putc(1);
	uart_putc(7);
	uart_putc(18);
	uart_putc(2);
	_delay_ms(242);

	uart_putc(127);
	uart_putc(0);
	uart_putc(1);
	uart_putc(10);
	uart_putc(60);
	uart_putc(8);
	_delay_ms(242);

	uart_putc(127);
	uart_putc(128);
	uart_putc(3);
	uart_putc(2);
	uart_putc(31);
	uart_putc(0);
	uart_putc(43);
	uart_putc(230);
	_delay_ms(242);
	pi = 0;

	while (1) {
		// banknociarka
		if (rp == 1) {
			uart_putc(127);
			uart_putc(128);
			uart_putc(1);
			uart_putc(7);
			uart_putc(18);
			uart_putc(2);

			c = uart_getc();
			c = uart_getc();
			c = uart_getc();
			c = uart_getc();
			c = uart_getc();
			c = uart_getc();
			//	c = uart_getc();
			//c = uart_getc();

			//c = uart_getc();
			//	napisz(3);

			if (c == 4) {
				//punkty = punkty + 1;

				d = uart_getc();
				d = uart_getc();
				d = uart_getc();
				d = uart_getc();
				kredytrp = kredytrp + 10;
				//napisz(3);
				if (d == 1) {
					kredytrp = kredytrp + 10;
					kredytrp = kredytrp - 10;

				}
				if (d == 2) {
					kredytrp = kredytrp + 20;
					kredytrp = kredytrp - 10;

				}
				if (d == 3) {
					kredytrp = kredytrp + 30;
					kredytrp = kredytrp - 10;

				}
				if (d == 4) {
					kredytrp = kredytrp + 40;
					kredytrp = kredytrp - 10;

				}

			}

			_delay_ms(50);


			uart_putc(127);
			uart_putc(0);
			uart_putc(1);
			uart_putc(7);
			uart_putc(17);
			uart_putc(136);
			_delay_ms(50);

			_delay_ms(50);
		}

		// ==================================================

		// ============================ koniec banknociarka ardac ========================================



	}
}
