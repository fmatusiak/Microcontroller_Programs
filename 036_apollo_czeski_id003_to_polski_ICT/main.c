#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

volatile uint8_t version[] = { 0xFC, 0x2E, 0x88, 0x55, 0x28, 0x43, 0x5A, 0x45,
		0x29, 0x2D, 0x31, 0x30, 0x2D, 0x53, 0x53, 0x20, 0x49, 0x44, 0x30, 0x30,
		0x33, 0x2D, 0x30, 0x33, 0x56, 0x32, 0x38, 0x30, 0x2D, 0x35, 0x32, 0x20,
		0x31, 0x37, 0x53, 0x45, 0x50, 0x31, 0x38, 0x20, 0x33, 0x31, 0x37, 0x33,
		0xD9, 0x4A };

volatile uint8_t currency_version[] = { 0xFC, 0x25, 0x8A, 0x61, 0x00, 0x00,
		0x00, 0x62, 0x2C, 0x0A, 0x01, 0x63, 0x2C, 0x14, 0x01, 0x64, 0x2C, 0x32,
		0x01, 0x65, 0x2C, 0x64, 0x01, 0x66, 0x2C, 0x14, 0x02, 0x67, 0x2C, 0x32,
		0x02, 0x68, 0x00, 0x00, 0x00, 0xEE, 0x63 };
volatile uint8_t data_controler[25] = { 0 }, data_acceptor[25] = { 0 };

volatile uint8_t l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0, l7 = 0, l8 = 0;

volatile uint8_t FL_vr = 0, FL_cur = 0, FL_C0H = 0;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t ubrr);
void uart_putc_s(uint8_t data);
uint8_t uart_ischar(void);
uint8_t czytaj_bajt(void);
void uart_putc(uint8_t data);
int uart_getc(void);

///UWAGA
//////////////////////////////////////////////////////////////////////////////
///ODWRÓCONY UART
///////////////////////////////////////////////////////////////////////////////
//Banknociarka UART SPRZETOWY
//KOMPUTER PROGRAMOWY


int main(void) {
	uint16_t i;
	DDR_rxs_we;
	rxs_we_VCC;

	DDR_txs;
	PORT_txs_1;

	uart_init(RS_UBRR);
	_delay_ms(2000);

	while (0) {
		data_controler[0] = uart_getc();
		if (data_controler[0] == 252) {
			data_controler[1] = uart_getc();
			for (i = 2; i < data_controler[1]; i++) {
				data_controler[i] = uart_getc();

			}
			for (i = 2; i < data_controler[1]; i++) {
				if (data_controler[i] == 0xC0) {
					FL_C0H = 1;
				}
			}

			for (i = 0; i < data_controler[1]; i++) {
				uart_putc_s(data_controler[i]);

				if (i != 1) {
					data_controler[i] = 0;
				}
			}
		}

		data_acceptor[0] = czytaj_bajt();
		if (data_acceptor[0] == 252) {
			data_acceptor[1] = czytaj_bajt();
			for (i = 2; i < data_acceptor[1]; i++) {
				data_acceptor[i] = czytaj_bajt();
			}

			for (i = 0; i < data_acceptor[1]; i++) {
				uart_putc(data_acceptor[i]);

				if (i != 1) {
					data_acceptor[i] = 0;
				}
			}

		}
	}

	while (1) {
		data_controler[0] = uart_getc();
		if (data_controler[0] == 252) {
			data_controler[1] = uart_getc();

			for (i = 2; i < data_controler[1]; i++) {
				data_controler[i] = uart_getc();
			}

			for (i = 2; i < data_controler[1]; i++) {
				if (data_controler[i] == 0xC0) {
					FL_C0H = 1;
				}
			}

			if (FL_C0H == 1) {
				uart_putc_s(0xFC);
				uart_putc_s(0x07);
				uart_putc_s(0xC0);
				uart_putc_s(0x80);
				uart_putc_s(0xFF);
				uart_putc_s(0x99);
				uart_putc_s(0x36);

				uart_putc(0xFC);
				uart_putc(0x07);
				uart_putc(0xC0);
				uart_putc(0x81);
				uart_putc(0xFF);
				uart_putc(0x41);
				uart_putc(0x2F);

				for (i = 0; i < data_controler[1]; i++) {
					if (i != 1) {
						data_controler[i] = 0;
					}
				}

			} else {

				for (i = 0; i < data_controler[1]; i++) {
					uart_putc_s(data_controler[i]);

					if (data_controler[i] == 0x88) {
						FL_vr = 1;
					}

					if (data_controler[i] == 0x8A) {
						FL_cur = 1;
					}

					if (i != 1) {
						data_controler[i] = 0;
					}
				}
			}

			data_controler[1] = 0;
		}

		if ((FL_vr == 1) || (FL_cur == 1) || FL_C0H == 1) {

			if (FL_vr == 1) {
				FL_vr = 0;
				for (i = 0; i < 46; i++) {
					uart_putc(version[i]);
				}
			}
			if (FL_cur == 1) {
				FL_cur = 0;
				for (i = 0; i < 37; i++) {
					uart_putc(currency_version[i]);
				}
			}
			if (FL_C0H == 1) {
				FL_C0H = 0;
			}

		} else {
			data_acceptor[0] = czytaj_bajt();
			if (data_acceptor[0] == 252) {

				data_acceptor[1] = czytaj_bajt();

				for (i = 2; i < data_acceptor[1]; i++) {
					data_acceptor[i] = czytaj_bajt();
				}
				for (i = 2; i < data_acceptor[1]; i++) {
					if (data_acceptor[i] == 0x13) {
						if (data_acceptor[i + 1] == 0x61) {
							data_acceptor[i + 1] = 0x62;
							data_acceptor[i + 2] = 0x2B;
							data_acceptor[i + 3] = 0xC9;

						} else if (data_acceptor[i + 1] == 0x62) {
							data_acceptor[i + 1] = 0x63;
							data_acceptor[i + 2] = 0xA2;
							data_acceptor[i + 3] = 0xD8;
						}

						else if (data_acceptor[i + 1] == 0x63) {
							data_acceptor[i + 1] = 0x64;
							data_acceptor[i + 2] = 0x1D;
							data_acceptor[i + 3] = 0xAC;
						}

						else if (data_acceptor[i + 1] == 0x64) {
							data_acceptor[i + 1] = 0x65;
							data_acceptor[i + 2] = 0x94;
							data_acceptor[i + 3] = 0xBD;
						} else if (data_acceptor[i + 1] == 0x65) {
							data_acceptor[i + 1] = 0x66;
							data_acceptor[i + 2] = 0x0F;
							data_acceptor[i + 3] = 0x8F;
						} else if (data_acceptor[i + 1] == 0x66) {
							data_acceptor[i + 1] = 0x67;
							data_acceptor[i + 2] = 0x86;
							data_acceptor[i + 3] = 0x9E;
						}

					}
				}

				for (i = 0; i < data_acceptor[1]; i++) {
					uart_putc(data_acceptor[i]);

					if (i != 1) {
						data_acceptor[i] = 0;
					}
				}
				data_acceptor[1] = 0;
			}
		}
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

void uart_putc_s(uint8_t data) {
// Oczekiwanie na zakoñczenie nadawania
	while (!(UCSRA & (1 << UDRE)))
		;
// Wys³anie danych
	UDR = data;
}

uint8_t uart_ischar(void) {
// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t czytaj_bajt(void) {
	uint16_t x = 0;
	while (!uart_ischar()) {
		x++;
		if (x >= 60000) {
			return 0;
		}
	}

	return UDR;
}

void uart_putc(uint8_t data) {

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

int uart_getc(void) {
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

