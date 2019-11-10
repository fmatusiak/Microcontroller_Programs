#include <avr/io.h>
#include <util/delay.h>
#include "HD44780.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

volatile uint8_t sec = 0, m = 0, start = 1, swieci = 0, value[5];
volatile uint8_t p = 1, j = 0, pintka = 0, i = 0;
volatile uint16_t min = 1, pom = 0, pomo = 0, przerwa = 0, czas = 0, punkty = 0,
		licznik = 0, time = 1600, punktyb = 0;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void convert_m(uint16_t m) {
	char str[16];
	itoa(m, str, 10);
	LCD_WriteText(str);
}

void convert_s(uint8_t s) {
	char str[16];
	itoa(s, str, 10);
	LCD_WriteText(str);
}

void napisz(uint8_t n) {
	switch (n) {

	case 2:
		LCD_Clear();
		LCD_WriteText(" zmienna =");
		LCD_GoTo(0, 1);
		LCD_WriteText(" ");
		convert_m(min);
		break;

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
	// Oczekiwanie na zakoñczenie nadawania
	while (!(UCSRA & (1 << UDRE)))
		;

	// Wys³anie danych
	UDR = data;
}
//
uint8_t uart_ischar() {
	// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc() {
	// Czy w buforze s¹ dane?
	while (!uart_ischar())
		;

	// Dane z bufora
	return UDR;
}

void init_device() {
	uart_putc(252);
	uart_putc(5);
	uart_putc(17);
	uart_putc(39);
	uart_putc(86);

	_delay_ms(100);

	uart_putc(252);
	uart_putc(5);
	uart_putc(136);
	uart_putc(111);
	uart_putc(95);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(5);
	uart_putc(64); // reset devaice
	uart_putc(43);
	uart_putc(21);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(6);
	uart_putc(195); // reset devaice
	uart_putc(0);
	uart_putc(4);
	uart_putc(214);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(6);
	uart_putc(199); // reset devaice
	uart_putc(252);
	uart_putc(135);
	uart_putc(140);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(5);
	uart_putc(17); // request sttusa
	uart_putc(39);
	uart_putc(86);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(6);
	uart_putc(195); // reset devaice
	uart_putc(0);
	uart_putc(4);
	uart_putc(214);
	_delay_ms(100);

	uart_putc(252);
	uart_putc(6);
	uart_putc(199); // reset devaice
	uart_putc(252);
	uart_putc(135);
	uart_putc(140);
	_delay_ms(100);
}

void request_status() {
	uart_putc(252);
	uart_putc(5);
	uart_putc(17); // request sttusa
	uart_putc(39);
	uart_putc(86);
}



volatile int poszlo = 1;

int main(void) {
	LCD_Initalize();
	LCD_Clear();
	LCD_WriteText("   ");
	LCD_GoTo(0, 1);
	LCD_WriteText("    ");

	_delay_ms(2000);

	DDR_jedynka;
	jedynka_VCC;

	DDR_dwojka;
	dwojka_VCC;

	DDR_trojka;
	trojka_VCC;

	DDR_czworka;
	czworka_VCC;

	DDR_kanal_1b;
	kanal_1b_VCC;

	DDR_jedynka_wy;
	DDR_dwojka_wy;
	DDR_trojka_wy;
	DDR_czworka_wy;
	PORT_jedynka_wy_1;
	PORT_dwojka_wy_1;
	PORT_trojka_wy_1;
	PORT_czworka_wy_1;

	uart_init(RS_UBRR);
	_delay_ms(2000);

	init_device();

	while (1) {

		if (!(PIN_jedynka)) {
			_delay_ms(5);

			if(!(PIN_jedynka))
			listening();

		}
		request_status();
		min = uart_getc();

		_delay_ms(150);
		LCD_Clear();
		napisz(2);
		if (min == 232) { //ukladarka reset
			init_device();

		}
		if (min == 251) { //ten
			min = 0;

			uart_putc(252);
			uart_putc(5);
			uart_putc(65); // request sttusa
			uart_putc(162);
			uart_putc(4);
			_delay_ms(150);

			for (uint8_t i = 0; i < 10; i++) {
				request_status();
				_delay_ms(150);
			}

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			request_status();

			nabij_pulse();

			min = 1;

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			request_status();
			_delay_ms(150);

			min = uart_getc();
			min = uart_getc();
			min = uart_getc();

		}

		if (min == 201) { // twenty
			min = 0;

			uart_putc(252);
			uart_putc(5);
			uart_putc(65); // request sttusa
			uart_putc(162);
			uart_putc(4);
			_delay_ms(150);

			for (uint8_t i = 0; i < 10; i++) {
				request_status();
				_delay_ms(150);
			}

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			request_status();

			for (uint8_t i = 0; i < 2; i++) {
				nabij_pulse();
			}

			min = 1;

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			request_status();

			_delay_ms(150);

			min = uart_getc();
			min = uart_getc();
			min = uart_getc();

		}

		if (min == 216) {
			min = 0;

			uart_putc(252);
			uart_putc(5);
			uart_putc(65); // request sttusa
			uart_putc(162);
			uart_putc(4);
			_delay_ms(150);

			for (uint8_t i = 0; i < 10; i++) {
				request_status();
				_delay_ms(150);
			}

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			request_status();

			for (uint8_t i = 0; i < 5; i++) {
				nabij_pulse();
			}

			min = 1;

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			request_status();

			_delay_ms(150);

			min = uart_getc();
			min = uart_getc();
			min = uart_getc();

		}

		if (min == 172) {
			min = 0;

			uart_putc(252);
			uart_putc(5);
			uart_putc(65); // request sttusa
			uart_putc(162);
			uart_putc(4);
			_delay_ms(150);

			for (uint8_t i = 0; i < 10; i++) {
				request_status();
				_delay_ms(150);
			}

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			request_status();

			for (uint8_t i = 0; i < 10; i++) {
				nabij_pulse();
			}

			min = 1;

			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			request_status();

			_delay_ms(150);

			min = uart_getc();
			min = uart_getc();
			min = uart_getc();

		}
		if (min == 16) {
			uart_putc(252);
			uart_putc(5);
			uart_putc(80); // request sttusa
			uart_putc(170);
			uart_putc(5);
			_delay_ms(150);

			uart_putc(252);
			uart_putc(5);
			uart_putc(17); // request sttusa
			uart_putc(39);
			uart_putc(86);
			_delay_ms(150);

			min = uart_getc();
			min = uart_getc();
			min = uart_getc();

		}

	}
}

void nabij_pulse() {
	PORT_dwojka_wy_0;
	_delay_ms(100);
	PORT_dwojka_wy_1;
	_delay_ms(100);
}


void listening() {
	while (!(PIN_jedynka)) {

		value[0] = uart_getc();
		if(value[0] == 172)
		{
			for (uint8_t i = 0; i < 10; i++) {
									nabij_pulse();
								}
		}


		if(value[0] == 216)
		{
			for (uint8_t i = 0; i < 5; i++) {
									nabij_pulse();
								}
		}


		if(value[0] == 201)
		{
			for (uint8_t i = 0; i < 2; i++) {
									nabij_pulse();
								}
		}


		if(value[0] == 251)
		{
			for (uint8_t i = 0; i < 1; i++) {
									nabij_pulse();
								}
		}





		/*

		for (uint8_t i = 0; i < 10; i++) {
			value[i] = uart_getc();
		}

		if(i == 172)
		{

		}

		for (uint8_t i = 0; i < 10; i++) {
			if (value[i] == 100) {
				if ((value[i] + 1) == 29) {
					if ((value[i] + 2) == 172) {
						for (uint8_t i = 0; i < 10; i++) {
							nabij_pulse();
						}
					}
				}
			}

		}

		for (uint8_t i = 0; i < 10; i++) {
					value[i] = 0;
				}

	if((PIN_jedynka))
	{
		_delay_ms(3);
	}
*/	}
}




