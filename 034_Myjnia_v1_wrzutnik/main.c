#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

volatile uint8_t data_controler[25] = { 0 }, data_acceptor[25] = { 0 };
volatile uint8_t data_buffor_coin[20] = { 0 };
volatile uint8_t event = 0, event_coin = 0;
volatile uint8_t a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
volatile uint8_t b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0;

volatile uint8_t l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0, l7 = 0, l8 = 0;
volatile uint8_t i = 0, FL_buffor = 0, tmp_val_in = 0, money = 0,
		buff_event = 0, money_buff = 0, FL_nabite = 0;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
void uart_putc_s(uint8_t data);

void check_impuls(void);
void coin_in_acceptor_bufffor(void);
void uart_clear(void);
uint8_t read_byte(void);

int main(void) {
	DDR_IN1;
	DDR_txs;
	DDR_rxs_we;
	IN1_VCC;
	PORT_txs_1;
	rxs_we_VCC;

	uart_init(RS_UBRR);
	_delay_ms(200);

	while (1) {
		uart_clear();
		data_controler[0] = uart_getc();

		if (data_controler[0] == 2) {
			data_controler[1] = uart_getc();
			data_controler[2] = uart_getc();

			if (data_controler[2] == 1) {
				for (i = 3; i < data_controler[1] + 5; i++) {
					data_controler[i] = uart_getc();
				}

				for (i = 0; i < data_controler[1] + 5; i++) {
					uart_putc_s(data_controler[i]);

					if (data_controler[i] == 229) {
						if (data_controler[i + 1] == 24) {
							FL_buffor = 1;
						}
					}
					if (data_controler[i] == 254) {
						if (data_controler[i + 1] == 255) {
							event = 0;
							a5 = 0;
							a4 = 0;
							a3 = 0;
							a2 = 0;
							a1 = 0;

							b5 = 0;
							b4 = 0;
							b3 = 0;
							b2 = 0;
							b1 = 0;

						}

					}

					if (i != 1) {
						data_controler[i] = 0;
					}
				}
				data_controler[1] = 0;

				if (FL_buffor == 1) {
					FL_buffor = 0;
					coin_in_acceptor_bufffor();
				} else {
					data_acceptor[0] = read_byte();
					data_acceptor[1] = read_byte();

					for (i = 2; i < data_acceptor[1] + 5; i++) {
						data_acceptor[i] = read_byte();
					}

					for (i = 0; i < data_acceptor[1] + 5; i++) {
						uart_putc(data_acceptor[i]);

						if (i != 1) {
							data_acceptor[i] = 0;
						}
					}
					data_acceptor[1] = 0;

				}

				check_impuls();

			} else {
				data_controler[0] = 0;
				data_controler[1] = 0;
				data_controler[2] = 0;
			}
		}

	}
}

// FUNCTIONS
void uart_clear(void) {
	uint8_t flu;
	while ( UCSRA & (1 << RXC)) {
		flu = UDR;
	}
}

void coin_in_acceptor_bufffor(void) {

	data_acceptor[0] = read_byte();
	data_acceptor[1] = read_byte();

	for (i = 2; i < 16; i++) {
		data_acceptor[i] = read_byte();
	}

	if (data_acceptor[4] != buff_event) {
		buff_event = data_acceptor[4];
		money_buff++;

	}

	if ((money) && (money_buff == 0)) {
		money--;
		event++;

		a5 = a4;
		a4 = a3;
		a3 = a2;
		a2 = a1;
		a1 = 1;

		b5 = b4;
		b4 = b3;
		b3 = b2;
		b2 = b1;
		b1 = 0;

	}

	if (money_buff) {
		money_buff--;
		event++;

		a5 = a4;
		a4 = a3;
		a3 = a2;
		a2 = a1;
		a1 = data_acceptor[5];

		b5 = b4;
		b4 = b3;
		b3 = b2;
		b2 = b1;
		b1 = data_acceptor[6];

	}

	data_buffor_coin[0] = data_acceptor[0];
	data_buffor_coin[1] = data_acceptor[1];
	data_buffor_coin[2] = data_acceptor[2];
	data_buffor_coin[3] = data_acceptor[3];
	data_buffor_coin[4] = event;
	data_buffor_coin[5] = a1;
	data_buffor_coin[6] = b1;
	data_buffor_coin[7] = a2;
	data_buffor_coin[8] = b2;
	data_buffor_coin[9] = a3;
	data_buffor_coin[10] = b3;
	data_buffor_coin[11] = a4;
	data_buffor_coin[12] = b4;
	data_buffor_coin[13] = a5;
	data_buffor_coin[14] = b5;

	for (uint8_t i = 0; i < 15; i++) {
		data_buffor_coin[15] += data_buffor_coin[i];
	}
	data_buffor_coin[15] = 256 - data_buffor_coin[15];

	for (i = 0; i < 16; i++) {

		uart_putc(data_buffor_coin[i]);

		if (i != 1) {
			data_acceptor[i] = 0;
			data_buffor_coin[i] = 0;
		}
	}
	data_buffor_coin[1] = 0;
	data_acceptor[1] = 0;
}

void check_impuls(void) {

	if (!(PIN_IN1)) {
		if (FL_nabite == 0) {
			_delay_ms(1);
			if (!(PIN_IN1)) {
				_delay_ms(1);
				if (!(PIN_IN1)) {

					_delay_ms(1);
					if (!(PIN_IN1)) {

						FL_nabite = 1;
						money++;

					}
				}
			}
		}

	} else {
		tmp_val_in = 0;
		FL_nabite = 0;
	}

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

uint8_t uart_getc() {
	// Czy w buforze s¹ dane?'

	while (!uart_ischar()) {

	};

	return UDR;
}
void uart_putc_s(uint8_t data) {

	int c, k = 0;

	PORT_txs_0;
	_delay_us(103);
	for (c = 0; c < 8; c++) {
		k = data >> c;

		if (k & 1) {
			PORT_txs_1;
			_delay_us(103);

		}

		else {
			PORT_txs_0;
			_delay_us(103);
		}

	}
	/*if (parity % 2 == 0) {

	 PORT_txs_0;
	 _delay_us(103);
	 } else {

	 PORT_txs_1;
	 _delay_us(103);
	 }*/

	PORT_txs_1;
	_delay_us(103);

}

uint8_t read_byte(void) {
	//uint16_t i = 0;
	while ((PIN_rxs_we)) {
		//if (automat_on == 0){

		//	i += 1;

		//	if (i == 60000) {
		//		return 0;
		//}

	}

	_delay_us(100);

	for (uint8_t zy = 0; zy < 4; zy++) {
		if (PIN_rxs_we) {
			l1 += 1;
		}
		_delay_us(25);

	}
	for (uint8_t zy = 0; zy < 4; zy++) {
		if (PIN_rxs_we) {
			l2 += 1;
		}
		_delay_us(25);

	}
	for (uint8_t zy = 0; zy < 4; zy++) {
		if (PIN_rxs_we) {
			l3 += 1;
		}
		_delay_us(25);

	}
	for (uint8_t zy = 0; zy < 4; zy++) {
		if (PIN_rxs_we) {
			l4 += 1;
		}
		_delay_us(25);

	}
	for (uint8_t zy = 0; zy < 4; zy++) {
		if (PIN_rxs_we) {
			l5 += 1;
		}
		_delay_us(25);

	}
	for (uint8_t zy = 0; zy < 4; zy++) {
		if (PIN_rxs_we) {
			l6 += 1;
		}
		_delay_us(25);

	}
	for (uint8_t zy = 0; zy < 4; zy++) {
		if (PIN_rxs_we) {
			l7 += 1;
		}
		_delay_us(25);

	}
	for (uint8_t zy = 0; zy < 4; zy++) {
		if (PIN_rxs_we) {
			l8 += 1;
		}
		_delay_us(25);

	}

	while (!(PIN_rxs_we)) {
	}
	_delay_us(150);

	int liczba = 0;
	if (l1 > 2) {
		liczba += 1;
	}
	if (l2 > 2) {
		liczba += 2;
	}
	if (l3 > 2) {
		liczba += 4;
	}
	if (l4 > 2) {
		liczba += 8;
	}
	if (l5 > 2) {
		liczba += 16;
	}
	if (l6 > 2) {
		liczba += 32;
	}
	if (l7 > 2) {
		liczba += 64;
	}
	if (l8 > 2) {
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

