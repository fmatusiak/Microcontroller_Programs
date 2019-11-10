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

volatile uint8_t data[40];

volatile uint8_t i, FirstRun = 1, nr_11_zap = 0, Inhibit = 0, FL_coin = 0;

volatile uint8_t iter_money = 0, iter_money_delay = 0,tmie_out = 0,tmp_money = 0;

volatile uint16_t money = 0;

const uint8_t version[46] = { 0x2E, 0x88, 0x55, 0x28, 0x50, 0x4F, 0x4C, 0x29,
		0x2D, 0x31, 0x30, 0x2D, 0x53, 0x53, 0x20, 0x49, 0x44, 0x30, 0x30, 0x33,
		0x2D, 0x30, 0x35, 0x56, 0x32, 0x37, 0x37, 0x2D, 0x35, 0x31, 0x20, 0x31,
		0x31, 0x4A, 0x41, 0x4E, 0x31, 0x36, 0x20, 0x33, 0x44, 0x44, 0x35, 0x18,
		0xFA };

const uint8_t currency[37] = { 0x25, 0x8A, 0x61, 0x1A, 0x01, 0x01, 0x62, 0x1A,
		0x02, 0x01, 0x63, 0x1A, 0x05, 0x01, 0x64, 0x1A, 0x0A, 0x01, 0x65, 0x1A,
		0x14, 0x01, 0x66, 0x00, 0x00, 0x00, 0x67, 0x00, 0x00, 0x00, 0x68, 0x00,
		0x00, 0x00, 0x6C, 0x1A };

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void check_is_money(void);
uint8_t readData(void);
void com_give_money(void);
void GiveMoneyKuwa(void);

#define Synch 0xFC

int main(void) {

	DDR_coin_we;
	coin_we_VCC;

	DDR_Inhibit_Out;
	PORT_Inhibit_Out_0;
	DDR_Inhibit_Out_LED;
	PORT_Inhibit_Out_LED_0;
	DDR_Puls_Out_LED;
	PORT_Puls_Out_LED_0;
	DDR_Puls_Out;
	PORT_Puls_Out_0;

	uart_init(RS_UBRR);
	_delay_ms(2000);

	while (FirstRun) {
		if (readData()) {

			if ((data[1] == 0x05) && (data[2] == 0x40) && (data[3] == 0x2B)
					&& (data[4] == 0x15)) {

				uart_putc(Synch);
				uart_putc(0x05);
				uart_putc(0x50);
				uart_putc(0xAA);
				uart_putc(0x05);
			}

			if ((data[1] == 0x05) && (data[2] == 0x11) && (data[3] == 0x27)
					&& (data[4] == 0x56)) {

				if (nr_11_zap) {

					for (i = 0; i < 5; i++) {
						uart_putc(data[i]);
					}

					if (nr_11_zap == 3) {
						FirstRun = 0;
					}
					nr_11_zap++;
				} else {
					nr_11_zap++;
					uart_putc(Synch);
					uart_putc(0x05);
					uart_putc(0x1B);
					uart_putc(0x7D);
					uart_putc(0xF9);
				}
			}

			if ((data[1] == 0x05) && (data[2] == 0x88) && (data[3] == 0x6F)
					&& (data[4] == 0x5F)) {

				uart_putc(Synch);
				for (i = 0; i < 45; i++) {
					uart_putc(version[i]);
				}
			}

			if ((data[1] == 0x05) && (data[2] == 0x8A) && (data[3] == 0x7D)
					&& (data[4] == 0x7C)) {

				uart_putc(Synch);
				for (i = 0; i < 36; i++) {
					uart_putc(currency[i]);
				}
			}

			if ((data[1] == 0x07) && (data[2] == 0xC0) && (data[3] == 0xE0)
					&& (data[4] == 0xFF) && (data[5] == 0xCC)
					&& (data[6] == 0x53)) {

				for (i = 0; i < 7; i++) {
					uart_putc(data[i]);
				}

			}

			if ((data[1] == 0x07) && (data[2] == 0xC1) && (data[3] == 0x00)
					&& (data[4] == 0x00) && (data[5] == 0xF1)
					&& (data[6] == 0xEF)) {

				for (i = 0; i < 7; i++) {
					uart_putc(data[i]);
				}

			}

			if ((data[1] == 0x07) && (data[2] == 0xC5) && (data[3] == 0x03)
					&& (data[4] == 0x00) && (data[5] == 0xF8)
					&& (data[6] == 0xA6)) {

				for (i = 0; i < 7; i++) {
					uart_putc(data[i]);
				}
			}

			if ((data[1] == 0x06) && (data[2] == 0xC2) && (data[3] == 0x00)
					&& (data[4] == 0xDC) && (data[5] == 0xCF)) {

				for (i = 0; i < 6; i++) {
					uart_putc(data[i]);
				}
			}

			if ((data[1] == 0x07) && (data[2] == 0xC6) && (data[3] == 0x01)
					&& (data[4] == 0x12) && (data[5] == 0xBF)
					&& (data[6] == 0x49)) {

				for (i = 0; i < 7; i++) {
					uart_putc(data[i]);
				}
			}

			if ((data[1] == 0x06) && (data[2] == 0xC7) && (data[3] == 0xFC)
					&& (data[4] == 0x87) && (data[5] == 0x8C)) {

				for (i = 0; i < 6; i++) {
					uart_putc(data[i]);
				}
			}

			if ((data[1] == 0x06) && (data[2] == 0xC3) && (data[3] == 0x01)
					&& (data[4] == 0x8D) && (data[5] == 0xC7)) {

				for (i = 0; i < 6; i++) {
					uart_putc(data[i]);
				}

				Inhibit = 0;
				PORT_Inhibit_Out_0;
				PORT_Inhibit_Out_LED_0;

			}

			if ((data[1] == 0x06) && (data[2] == 0xC3) && (data[3] == 0x00)
					&& (data[4] == 0x04) && (data[5] == 0xD6)) {

				for (i = 0; i < data[1]; i++) {
					uart_putc(data[i]);
				}

				Inhibit = 1;
				PORT_Inhibit_Out_1;
				PORT_Inhibit_Out_LED_1;
			}

			for (i = 0; i < 40; i++) {
				data[i] = 0;
			}

		}
	}

	while (1) {
		check_is_money();

		if (readData()) {
			tmie_out++;
			check_is_money();
			if ((data[1] == 0x06) && (data[2] == 0xC3) && (data[3] == 0x01)
					&& (data[4] == 0x8D) && (data[5] == 0xC7)) {

				Inhibit = 1;
				PORT_Inhibit_Out_0;
				PORT_Inhibit_Out_LED_0;
				check_is_money();
			}

			else if ((data[1] == 0x06) && (data[2] == 0xC3) && (data[3] == 0x00)
					&& (data[4] == 0x04) && (data[5] == 0xD6)) {
				Inhibit = 0; //???????????????
				PORT_Inhibit_Out_1;
				PORT_Inhibit_Out_LED_1;
				check_is_money();
			}

			else if ((data[1] == 0x05) && (data[2] == 0x11) && (data[3] == 0x27)
					&& (data[4] == 0x56)) {
				check_is_money();

				if (Inhibit) {
					data[0] = 0xFC;
					data[1] = 0x05;
					data[2] = 0x1A;
					data[3] = 0xF4;
					data[4] = 0xE8;
					check_is_money();
				} else {
					if (money > 0) {
						if (tmie_out > 4) {

							if (iter_money < 4) {
								com_give_money();
							} else {
								if (iter_money_delay > 10) {
									iter_money_delay = 0;
									iter_money = 0;
								}
								iter_money_delay++;
							}
							iter_money++;
						}
					}
				}

			}

			else if ((data[1] == 0x05) && (data[2] == 0x42) && (data[3] == 0x39)
					&& (data[4] == 0x36) && money > 0) {

				iter_money = 0;

				for (uint8_t x = 0; x < 50; x++) {
					check_is_money();
					_delay_ms(1);
				}

				GiveMoneyKuwa();
			}

			for (i = 0; i < data[1]; i++) {
				uart_putc(data[i]);
			}
			for (i = 0; i < 40; i++) {
				data[i] = 0;
			}

		}
	}
}

// =================================== koniec nri cctalk wrzutnik ==========================================

// FUNCTIONS

void GiveMoneyKuwa(void) {
	Inhibit = 1;
	PORT_Inhibit_Out_0;
	PORT_Inhibit_Out_LED_0;
	check_is_money();

	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x50);
	uart_putc(0xAA);
	uart_putc(0x05);

	for (uint8_t x = 0; x < 5; x++) {
		check_is_money();
		readData();
		check_is_money();

		uart_putc(0xFC);
		uart_putc(0x05);
		uart_putc(0x14);
		uart_putc(0x8A);
		uart_putc(0x01);


		if ((data[1] == 0x06) && (data[2] == 0xC3) && (data[3] == 0x00)
				&& (data[4] == 0x04) && (data[5] == 0xD6)) {
			Inhibit = 0;
		}

	}

	check_is_money();
	readData();
	check_is_money();
	if ((data[1] == 0x06) && (data[2] == 0xC3) && (data[3] == 0x00)
			&& (data[4] == 0x04) && (data[5] == 0xD6)) {
		Inhibit = 0;
	}


	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x15);
	uart_putc(0x03);
	uart_putc(0x10);

	check_is_money();
	readData();
	check_is_money();
	if ((data[1] == 0x06) && (data[2] == 0xC3) && (data[3] == 0x00)
			&& (data[4] == 0x04) && (data[5] == 0xD6)) {
		Inhibit = 0;
	}


	if ((data[1] == 0x05) && (data[2] == 0x50) && (data[3] == 0xAA)
			&& (data[4] == 0x05)) {

		check_is_money();
		readData();
		check_is_money();

		if (tmp_money == 20) {
			tmp_money = 0;
			money = money - 20;
		}

		else if (tmp_money == 10) {
			tmp_money = 0;
			money = money - 10;
		}

		else if (tmp_money == 5) {
			tmp_money = 0;
			money = money - 5;
		}

		else if (tmp_money == 2) {
			tmp_money = 0;
			money = money - 2;
		}

		else if (tmp_money == 1) {
			tmp_money = 0;
			money = money - 1;
		}
	}

	else {
		return;
	}

	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x16);
	uart_putc(0x98);
	uart_putc(0x22);

	check_is_money();
	readData();
	check_is_money();


	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x16);
	uart_putc(0x98);
	uart_putc(0x22);

	data[0] = 0xFC;
	data[1] = 0x05;
	data[2] = 0x11;
	data[3] = 0x27;
	data[4] = 0x56;

	check_is_money();
	readData();
	check_is_money();

	Inhibit = 0;
	PORT_Inhibit_Out_1;
	PORT_Inhibit_Out_LED_1;

}

void com_give_money(void) {
	check_is_money();
	data[0] = 0xFC;
	data[1] = 0x06;
	data[2] = 0x13;

	if (money >= 20) {
		tmp_money = 20;
		data[3] = 0x65;
		data[4] = 0x94;
		data[5] = 0xBD;
	}

	else if (money >= 10) {
		tmp_money = 10;
		data[3] = 0x64;
		data[4] = 0x1D;
		data[5] = 0xAC;
	}

	else if (money >= 5) {
		tmp_money = 5;
		data[3] = 0x63;
		data[4] = 0xA2;
		data[5] = 0xD8;
	}

	else if (money >= 2) {
		tmp_money = 2;
		data[3] = 0x62;
		data[4] = 0x2B;
		data[5] = 0xC9;
	}

	else if (money >= 1) {
		tmp_money = 1;
		data[3] = 0x61;
		data[4] = 0xB0;
		data[5] = 0xFB;
	}
	check_is_money();
}

uint8_t readData(void) {
	check_is_money();
	data[0] = uart_getc();
	check_is_money();
	if (data[0] == Synch) {
		data[1] = uart_getc();
		for (i = 2; i < data[1]; i++) {
			data[i] = uart_getc();
		}
		check_is_money();
		return 1;
	}
	return 0;
}

void check_is_money(void) {
	if (FirstRun == 0) {
		if (PIN_coin_we) {
			FL_coin = 1;
			PORT_Puls_Out_LED_0;
		}

		if ((!(PIN_coin_we)) && (FL_coin)) {
			_delay_us(3);
			if (!(PIN_coin_we)) {
				PORT_Puls_Out_LED_1;
				PORT_Puls_Out_1;
				money++;
				FL_coin = 0;
				tmie_out = 0;
				Inhibit = 0;
				PORT_Inhibit_Out_0;
				PORT_Inhibit_Out_LED_0;

			}
		}
		if (PIN_coin_we) {
			FL_coin = 1;
			PORT_Puls_Out_LED_0;
			PORT_Puls_Out_0;
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
	check_is_money();
// Oczekiwanie na zakoñczenie nadawania
	while (!(UCSRA & (1 << UDRE))) {

	}

// Wys³anie danych
	UDR = data;
}

uint8_t uart_ischar(void) {
// Czy w buforze s¹ dane?
	check_is_money();
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc(void) {
// Czy w buforze s¹ dane?
	check_is_money();
	while (!uart_ischar()) {
		check_is_money();
	}
	check_is_money();

	return UDR;
}

