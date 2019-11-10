#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

volatile uint8_t FL_First_Ask = 0, Inhibit = 0, Kredyty = 0, Iter_Kredyt = 0,
		FL_Key = 0;

volatile uint8_t data_controler[30] = { 0 };

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);

////////////Komendy
void FourZero(void);
void FourTwo(void);
void OneOne(void);
void EightEight(void);
void EightAAA(void);
void CCCZero(void);
void CCCOne(void);
void CCCTwo(void);
void CCCThree(void);

void CCCFive(void);
void CCCSix(void);
void CCCSeven(void);

void Check_InsertMoney(void);
////

int main(void) {
	uint16_t i;
	DDR_IN1_IN;
	IN1_IN_VCC;

	uart_init(RS_UBRR);
	_delay_ms(500);

	while (1) {

		Check_InsertMoney();

		data_controler[0] = uart_getc();
		if (data_controler[0] == 0xFC) {
			data_controler[1] = uart_getc();

			for (i = 2; i < data_controler[1]; i++) {
				data_controler[i] = uart_getc();
			}

			if (data_controler[2] == 0x40) {
				FourZero();
			}
			if (data_controler[2] == 0x42) {
				FourTwo();
			}

			if (data_controler[2] == 0x11) {
				OneOne();
			}

			if (data_controler[2] == 0x88) {
				EightEight();
			}

			if (data_controler[2] == 0x8A) {
				EightAAA();
			}

			if (data_controler[2] == 0xC0) {
				CCCZero();
			}

			if (data_controler[2] == 0xC1) {
				CCCOne();
			}

			if (data_controler[2] == 0xC2) {
				CCCTwo();
			}
			if (data_controler[2] == 0xC3) {
				CCCThree();
			}

			if (data_controler[2] == 0xC5) {
				CCCFive();
			}

			if (data_controler[2] == 0xC6) {
				CCCSix();
			}

			if (data_controler[2] == 0xC7) {
				CCCSeven();
			}

			for (i = 0; i < 30; i++) {
				data_controler[i] = 0;
			}
		}
	}
}

// FUNCTIONS

void Check_InsertMoney(void) {

	if (!(PIN_IN1_IN)) {
		if (FL_Key) {
			_delay_ms(2);
			if (!(PIN_IN1_IN)) {
				Kredyty++;
				FL_Key = 0;
			}
		}
	}

	if ((PIN_IN1_IN) && (FL_Key == 0)) {
		FL_Key = 1;
	}

}

void FourZero(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x50);
	uart_putc(0xAA);
	uart_putc(0x05);
}

void FourTwo(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x50);
	uart_putc(0xAA);
	uart_putc(0x05);
}

void OneOne(void) {
	if (FL_First_Ask) {

		uart_putc(0xFC);
		uart_putc(0x05);
		uart_putc(0x1B);
		uart_putc(0x7D);
		uart_putc(0xF9);
	} else {
		FL_First_Ask = 0;

		if (Inhibit) {
			uart_putc(0xFC);
			uart_putc(0x05);
			uart_putc(0x1A);
			uart_putc(0xF4);
			uart_putc(0xE8);
		} else {

			if (Kredyty == 0) {
				uart_putc(0xFC);
				uart_putc(0x05);
				uart_putc(0x11);
				uart_putc(0x27);
				uart_putc(0x56);
			}

			else {
				Iter_Kredyt++;
				if (Iter_Kredyt < 3) {
					uart_putc(0xFC);
					uart_putc(0x05);
					uart_putc(0x12);
					uart_putc(0xBC);
					uart_putc(0x64);
				}

				else if (Iter_Kredyt == 3) {
					uart_putc(0xFC);
					uart_putc(0x06);
					uart_putc(0x13);
					uart_putc(0x64);
					uart_putc(0x1D);
					uart_putc(0xAC);
				}

				else if ((Iter_Kredyt > 3) && (Iter_Kredyt < 5)) {
					uart_putc(0xFC);
					uart_putc(0x05);
					uart_putc(0x14);
					uart_putc(0x8A);
					uart_putc(0x01);
				}

				else if (Iter_Kredyt == 5) {
					uart_putc(0xFC);
					uart_putc(0x05);
					uart_putc(0x15);
					uart_putc(0x03);
					uart_putc(0x10);
				}

				else if (Iter_Kredyt == 6) {
					uart_putc(0xFC);
					uart_putc(0x05);
					uart_putc(0x16);
					uart_putc(0x98);
					uart_putc(0x22);
				}

				else if (Iter_Kredyt == 7) {
					Kredyty--;
					Iter_Kredyt = 0;
					uart_putc(0xFC);
					uart_putc(0x05);
					uart_putc(0x16);
					uart_putc(0x98);
					uart_putc(0x22);
				}

			}

		}
	}

}

void EightEight(void) {
	uart_putc(0xFC);
	uart_putc(0x2E);
	uart_putc(0x88);
	uart_putc(0x55);
	uart_putc(0x28);
	uart_putc(0x50);
	uart_putc(0x4F);
	uart_putc(0x4C);
	uart_putc(0x29);
	uart_putc(0x2D);
	uart_putc(0x31);
	uart_putc(0x30);
	uart_putc(0x2D);
	uart_putc(0x53);
	uart_putc(0x53);
	uart_putc(0x20);
	uart_putc(0x49);
	uart_putc(0x44);
	uart_putc(0x30);
	uart_putc(0x30);
	uart_putc(0x33);
	uart_putc(0x2D);
	uart_putc(0x30);
	uart_putc(0x35);
	uart_putc(0x56);
	uart_putc(0x32);
	uart_putc(0x37);
	uart_putc(0x37);
	uart_putc(0x2D);
	uart_putc(0x35);
	uart_putc(0x31);
	uart_putc(0x20);
	uart_putc(0x31);
	uart_putc(0x31);
	uart_putc(0x4A);
	uart_putc(0x41);
	uart_putc(0x4E);
	uart_putc(0x31);
	uart_putc(0x36);
	uart_putc(0x20);
	uart_putc(0x33);
	uart_putc(0x44);
	uart_putc(0x44);
	uart_putc(0x35);
	uart_putc(0x18);
	uart_putc(0xFA);
}

void EightAAA(void) {
	uart_putc(0xFC);
	uart_putc(0x25);
	uart_putc(0x8A);
	uart_putc(0x61);
	uart_putc(0x1A);
	uart_putc(0x01);
	uart_putc(0x01);
	uart_putc(0x62);
	uart_putc(0x1A);
	uart_putc(0x02);
	uart_putc(0x01);
	uart_putc(0x63);
	uart_putc(0x1A);
	uart_putc(0x05);
	uart_putc(0x01);
	uart_putc(0x64);
	uart_putc(0x1A);
	uart_putc(0x0A);
	uart_putc(0x01);
	uart_putc(0x65);
	uart_putc(0x1A);
	uart_putc(0x14);
	uart_putc(0x01);
	uart_putc(0x66);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0x67);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0x68);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0x6C);
	uart_putc(0x1A);

}

void CCCZero(void) {
	uart_putc(0xFC);
	uart_putc(0x07);
	uart_putc(0xC0);
	uart_putc(0xE0);
	uart_putc(0xFF);
	uart_putc(0xCC);
	uart_putc(0x53);
}

void CCCOne(void) {
	uart_putc(0xFC);
	uart_putc(0x07);
	uart_putc(0xC1);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0xF1);
	uart_putc(0xEF);
}

void CCCTwo(void) {
	uart_putc(0xFC);
	uart_putc(0x06);
	uart_putc(0xC2);
	uart_putc(0x00);
	uart_putc(0xDC);
	uart_putc(0xCF);

}

void CCCThree(void) {
	Inhibit = data_controler[3];

	uart_putc(data_controler[0]);
	uart_putc(data_controler[1]);
	uart_putc(data_controler[2]);
	uart_putc(data_controler[3]);
	uart_putc(data_controler[4]);
	uart_putc(data_controler[5]);
}

void CCCFive(void) {
	uart_putc(0xFC);
	uart_putc(0x07);
	uart_putc(0xC5);
	uart_putc(0x03);
	uart_putc(0x00);
	uart_putc(0xF8);
	uart_putc(0xA6);
}

void CCCSix(void) {
	uart_putc(0xFC);
	uart_putc(0x07);
	uart_putc(0xC6);
	uart_putc(0x01);
	uart_putc(0x12);
	uart_putc(0xBF);
	uart_putc(0x49);
}

void CCCSeven(void) {
	uart_putc(0xFC);
	uart_putc(0x06);
	uart_putc(0xC7);
	uart_putc(0xFC);
	uart_putc(0x87);
	uart_putc(0x8C);

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
//int i = 0;
	while (!uart_ischar()) {

	}

	return UDR;
}
// === cctalk

