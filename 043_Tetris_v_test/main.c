#include "main.h"

// GLOBAL VARIABLES

void uart_init(uint16_t ubrr);

void uart_putc(uint8_t data);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);

uint8_t x = 0;

int main(void) {

	ioInit();

	uart_init(RS_UBRR);
	ALARM_12V_PB1_HIGH;

	while (1) {

		OUT8_PA1_LOW;
		OUT5_PC1_LOW;
		_delay_ms(250);
		OUT8_PA1_HIGH;
		OUT5_PC1_HIGH;
		_delay_ms(250);


	}

	while (1) {
		if (!(PIN_IN1_PC3)) {
			OUT1_PD5_HIGH;

		} else {
			OUT1_PD5_LOW;
			VGA_SWITCH_PB2_LOW;
		}

		uart_putc(x);
		x++;
		_delay_ms(100);
	}

	while (1) {

		x = uart_getc();

		if (x == 1) {

			OUT1_PD5_HIGH;

		}
		if (x == 2) {

			OUT2_PD6_HIGH;

		}
		if (x == 3) {

			OUT3_PD7_HIGH;

		}
		if (x == 4) {

			OUT4_PC0_HIGH;
		}
		if (x == 5) {

			OUT5_PC1_HIGH;
		}
		if (x == 6) {

			OUT5_PC1_LOW;
			OUT4_PC0_LOW;
			OUT3_PD7_LOW;
			OUT2_PD6_LOW;
			OUT1_PD5_LOW;
		}

		ALARM_12V_PB1_Z;
	}

	for (;;) {
		if (!(PIN_IN1_PC3)) {
			OUT1_PD5_HIGH;
			VGA_SWITCH_PB2_HIGH;

			//TX_PD1_HIGH;

		} else {
			OUT1_PD5_LOW;
			VGA_SWITCH_PB2_LOW;
		}

		if (!(PIN_IN2_PC4)) {
			OUT2_PD6_HIGH;
			RELAY_PB0_HIGH;

		} else {
			OUT2_PD6_LOW;
			RELAY_PB0_LOW;
		}
		if (!(PIN_IN3_PC5)) {
			OUT3_PD7_HIGH;
			MUTE_PD4_LOW;

		} else {
			MUTE_PD4_HIGH;
			OUT3_PD7_LOW;
		}

		if (!(PIN_IN4_PC6)) {
			OUT4_PC0_HIGH;
		} else {
			OUT4_PC0_LOW;
		}

		if (!(PIN_IN5_PC2)) {
			OUT5_PC1_HIGH;
		} else {
			OUT5_PC1_LOW;
		}

		if (!(PIN_IN6_PD2)) {
			OUT6_PD3_HIGH;
		} else {
			OUT6_PD3_LOW;
		}

		if (!(PIN_IN7_PA2)) {
			OUT7_PA3_HIGH;
		} else {
			OUT7_PA3_LOW;
		}
		if (!(PIN_IN8_PA0)) {
			OUT8_PA1_HIGH;
		} else {
			OUT8_PA1_LOW;
		}
		if (!(PIN_IN9_PB3)) {
			OUT9_PB4_HIGH;
		} else {
			OUT9_PB4_LOW;
		}

		if (!(PIN_IN10_PA6)) {
			OUT1_PD5_HIGH;
		} else {
			OUT1_PD5_LOW;
		}

		if (!(PIN_IN11_PA4)) {
			OUT2_PD6_HIGH;
		} else {
			OUT2_PD6_LOW;
		}

		if (!(PIN_IN12_PA5)) {
			OUT3_PD7_HIGH;
		} else {
			OUT3_PD7_LOW;
		}
		/*
		 if (!(PIN_PC1WE_PA7)) {
		 OUT4_PC0_HIGH;
		 ALARM_12V_PB1_HIGH;
		 } else {
		 OUT4_PC0_LOW;
		 ALARM_12V_PB1_LOW;
		 }*/

		if (!(PIN_MISO_PB6)) {
			OUT5_PC1_HIGH;
		} else {
			OUT5_PC1_LOW;
		}

		if (0) {

			x = uart_getc();

			if (x == 1) {
				OUT1_PD5_HIGH;

			}
			if (x == 2) {
				OUT2_PD6_HIGH;

			}
			if (x == 3) {
				OUT3_PD7_HIGH;

			}
			if (x == 4) {
				OUT4_PC0_HIGH;
			}
			if (x == 5) {
				OUT5_PC1_HIGH;
			}
			if (x == 6) {
				OUT5_PC1_HIGH;
				OUT4_PC0_HIGH;
				OUT3_PD7_HIGH;
				OUT2_PD6_HIGH;
				OUT1_PD5_HIGH;
			}

		}

	}
}
void ioInit(void) {
//========== INS ========================
	_delay_ms(500);

	DDR_IN1_PC3;
	DDR_IN2_PC4;
	DDR_IN3_PC5;
	DDR_IN4_PC6;
	DDR_IN5_PC2;
	DDR_IN6_PD2;
	DDR_IN8_PA0;
	DDR_IN9_PB3;
	DDR_IN10_PA6;
	DDR_IN11_PA4;
	DDR_IN12_PA5;

	//DDR_PC1WE_PA7;
	//DDR_PC2WE_PC7;

	IN1_PC3_VCC;
	IN2_PC4_VCC;
	IN3_PC5_VCC;
	IN4_PC6_VCC;
	IN5_PC2_VCC;
	IN6_PD2_VCC;
	IN7_PA2_VCC;
	IN8_PA0_VCC;
	IN9_PB3_VCC;
	IN10_PA6_VCC;
	IN11_PA4_VCC;
	IN12_PA5_VCC;

//	PC1WE_PA7_VCC;
//	PC2WE_PC7_VCC;

	DDR_MISO_PB6;
	MISO_PB6_VCC;

	DDR_RX_PD0;
	RX_PD0_VCC;

//========= OUTS ========================

	OUT1_PD5_DDR;
	OUT2_PD6_DDR;
	OUT3_PD7_DDR;
	OUT4_PC0_DDR;
	OUT5_PC1_DDR;
	OUT6_PD3_DDR;
	OUT8_PA1_DDR;

	VGA_SWITCH_PB2_DDR;
	RELAY_PB0_DDR;
	MUTE_PD4_DDR;
	ALARM_12V_PB1_DDR;

	MOSI_PB5_DDR;
	MOSI_PB5_LOW;

	VGA_SWITCH_PB2_LOW;
	RELAY_PB0_LOW;
	MUTE_PD4_HIGH;
	ALARM_12V_PB1_LOW;

	OUT1_PD5_LOW;
	OUT2_PD6_LOW;
	OUT3_PD7_LOW;
	OUT4_PC0_LOW;
	OUT5_PC1_LOW;
	OUT6_PD3_LOW;
	OUT7_PA3_LOW;
	OUT8_PA1_LOW;
	OUT9_PB4_LOW;

	_delay_ms(500);

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
//
uint8_t uart_ischar(void) {
	// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc(void) {
	// Czy w buforze s¹ dane?
	while (!uart_ischar())
		;

	// Dane z bufora
	return UDR;
}
