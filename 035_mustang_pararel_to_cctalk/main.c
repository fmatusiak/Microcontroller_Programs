#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "main.h"

volatile uint8_t INHIBIT = 1;

volatile uint8_t Money_In_Automat = 0, BillEvent = 0;
volatile uint8_t bill_5 = 0, bill_10 = 0, bill_20 = 0, bill_50 = 0,
		bill_100 = 0, bill_200 = 0;

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
uint8_t ccTalk_recive(uint8_t *datarecive, uint8_t from);

void uart_clear(void);

void ccTalk_send(uint8_t from, uint8_t dataCount, uint8_t command,
		uint8_t *data);

void Inhibit_bill_acceptor(void);
void Accept_bill_acceptor(void);
void SendInhibit(void);
void Check_inhibit(void);

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

int main(void) {

	DDR_INHIBIT_IN;
	INHIBIT_IN_VCC;

	DDR_LINE1_OUT;
	DDR_LINE2_OUT;
	DDR_LINE3_OUT;
	DDR_LINE4_OUT;
	DDR_LINE1_COIN_OUT;
	DDR_INHIBIT_LED;
	DDR_PULS_LED;

	PORT_LINE1_OUT_0;
	PORT_LINE2_OUT_0;
	PORT_LINE3_OUT_0;
	PORT_LINE4_OUT_0;
	PORT_LINE1_COIN_OUT_0;
	PORT_INHIBIT_LED_0;
	PORT_PULS_LED_0;

	uart_init(RS_UBRR);
	_delay_ms(1000);

	// coin acceptor
	uartPut(40, 2, 1, 231, (uint8_t[] ) { 255, 255 });
	_delay_ms(100);
	uartPut(40, 8, 1, 231,
			(uint8_t[] ) { 255, 255, 255, 255, 255, 255, 255, 255 });
	_delay_ms(50);
	uartPut(40, 1, 1, 228, (uint8_t[] ) { 1 });
	_delay_ms(150);

	while (1) {
		//===========================
		Check_inhibit();
		SendInhibit();

		uart_clear();
		uint8_t datarecive[20] = { 0 };
		ccTalk_send(40, 0, 159, (uint8_t[] ) { 0 });

		if (ccTalk_recive(datarecive, 40)) {
			if (*(datarecive + 4) != BillEvent) {
				BillEvent = *(datarecive + 4);
				if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 1)) {
					ccTalk_send(40, 1, 154, (uint8_t[] ) { 1 });
					bill_5 = 1;
					Money_In_Automat = 1;
				}

				if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 2)) {
					ccTalk_send(40, 1, 154, (uint8_t[] ) { 1 });
					Money_In_Automat = 1;
					bill_10 = 1;
				}

				if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 3)) {
					ccTalk_send(40, 1, 154, (uint8_t[] ) { 1 });
					Money_In_Automat = 1;
					bill_20 = 1;
				}

				if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 4)) {
					ccTalk_send(40, 1, 154, (uint8_t[] ) { 1 });
					Money_In_Automat = 1;
					bill_50 = 1;
				}
				if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 5)) {
					ccTalk_send(40, 1, 154, (uint8_t[] ) { 1 });
					Money_In_Automat = 1;
					bill_100 = 1;
				}
				if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 6)) {
					ccTalk_send(40, 1, 154, (uint8_t[] ) { 1 });
					bill_200 = 1;
					Money_In_Automat = 1;

				}

				if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 7)) {
					ccTalk_send(40, 1, 154, (uint8_t[] ) { 0 });

				}
			}

		}

		while (Money_In_Automat) {
			Inhibit_bill_acceptor();

			if (bill_5 == 1) {
				Inhibit_bill_acceptor();
//				PORT_LINE1_COIN_OUT_1;
				PORT_LINE1_OUT_1;

				_delay_ms(100);
	//			PORT_LINE1_COIN_OUT_0;
				PORT_LINE1_OUT_0;

				Inhibit_bill_acceptor();
				_delay_ms(100);
				Money_In_Automat = 0;
				bill_5 = 0;
			}

			if (bill_10 == 1) {
				Inhibit_bill_acceptor();
				PORT_LINE1_OUT_1;
				_delay_ms(100);
				PORT_LINE1_OUT_0;
				Inhibit_bill_acceptor();
				_delay_ms(100);
				Money_In_Automat = 0;
				bill_10 = 0;
			}

			if (bill_20 == 1) {
				Inhibit_bill_acceptor();
				PORT_LINE2_OUT_1;
				_delay_ms(100);
				PORT_LINE2_OUT_0;
				Inhibit_bill_acceptor();
				_delay_ms(100);
				Money_In_Automat = 0;
				bill_20 = 0;
			}
			if (bill_50 == 1) {
				Inhibit_bill_acceptor();
				PORT_LINE3_OUT_1;
				_delay_ms(100);
				PORT_LINE3_OUT_0;
				Inhibit_bill_acceptor();
				_delay_ms(100);
				Money_In_Automat = 0;
				bill_50 = 0;
			}

			if (bill_100 == 1) {
				Inhibit_bill_acceptor();
				PORT_LINE4_OUT_1;
				_delay_ms(100);
				PORT_LINE4_OUT_0;
				Inhibit_bill_acceptor();
				_delay_ms(100);
				Money_In_Automat = 0;
				bill_100 = 0;
			}
			if (bill_200 == 1) {
				for (uint8_t i = 0; i < 2; i++) {
					Inhibit_bill_acceptor();
					PORT_LINE4_OUT_1;
					_delay_ms(100);
					PORT_LINE4_OUT_0;
					Inhibit_bill_acceptor();
					_delay_ms(100);
					Money_In_Automat = 0;
					bill_200 = 0;
				}
			}

		}

		// ========================================= banknociarka nabijanie =======================================================
		//  ====================================== koniec banknocarka nabijanie ===================================================
	}
}

void SendInhibit(void) {

	if ((INHIBIT == 1) || (Money_In_Automat)) {
		Inhibit_bill_acceptor();
	} else {
		Accept_bill_acceptor();
	}
	_delay_ms(50);
}

void Check_inhibit(void) {
	if (!(PIN_INHIBIT_IN)) {
		INHIBIT = 0;
		PORT_INHIBIT_LED_1;
	} else {
		INHIBIT = 1;//test
		PORT_INHIBIT_LED_0;
	}
}

void Inhibit_bill_acceptor(void) {
	uartPut(40, 1, 1, 228, (uint8_t[] ) { 0 });

}

void Accept_bill_acceptor(void) {
	uartPut(40, 1, 1, 228, (uint8_t[] ) { 1 });

}

void ccTalk_send(uint8_t from, uint8_t dataCount, uint8_t command,
		uint8_t *data) {
	_delay_ms(1);
	uart_clear();
	uart_putc(from);
	uart_putc(dataCount);
	uart_putc(1);
	uart_putc(command);
	uint8_t checkSum = from + 1 + command + dataCount;

	for (uint8_t i = 0; i < dataCount; i++) {
		uart_putc(data[i]);
		checkSum += data[i];
	}
	checkSum = 256 - checkSum;

	uart_putc(checkSum);
}

uint8_t ccTalk_recive(uint8_t *datarecive, uint8_t from) {
	uint8_t tmp[30] = { 0 };

	for (uint8_t ziet = 0; ziet < 5; ziet++) {

		for (uint8_t i = 0; i < 10; i++) {
			tmp[i] = uart_getc();
		}

		for (uint8_t i = 0; i < (tmp[1] + tmp[6 + tmp[1]]); i++) {
			tmp[i + 10] = uart_getc();
		}

		if ((tmp[5 + tmp[1]] == 1) && (tmp[7 + tmp[1]] == from)) {
			for (uint8_t i = 0; i < 5 + tmp[6 + tmp[1]]; i++) {
				datarecive[i] = tmp[i + 5 + tmp[1]];
			}
			_delay_ms(50);
			uart_clear();
			return 1;
		}
		_delay_ms(50);
		uart_clear();
	}
	return 0;

}

// FUNCTIONS

void uart_clear(void) {
	uint8_t clr;
	while ( UCSRA & (1 << RXC)) {
		clr = UDR;
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

uint8_t uart_getc(void) {
	// Czy w buforze s¹ dane?'
	uint16_t timie_out = 64000;
	while (!uart_ischar()) {

		if (!(--timie_out)) {
			return 0;
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

