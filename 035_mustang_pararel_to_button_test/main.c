#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "main.h"

volatile uint8_t FL_give = 0;

void Give_5(void);
void Give_10(void);
void Give_20(void);
void Give_100(void);

void Wait(void);

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

int main(void) {

	DDR_LINE1_OUT;
	DDR_LINE2_OUT;
	DDR_LINE3_OUT;
	DDR_LINE4_OUT;
	DDR_LINE1_COIN_OUT;
	DDR_PULS_LED;
	DDR_INHIBIT_LED;
	DDR_KEY_IN;
	KEY_IN_VCC;

	PORT_LINE1_OUT_0;
	PORT_LINE2_OUT_0;
	PORT_LINE3_OUT_0;
	PORT_LINE4_OUT_0;
	PORT_LINE1_COIN_OUT_0;
	PORT_PULS_LED_0;
	PORT_INHIBIT_LED_0;

	_delay_ms(150);
	_delay_ms(150);
	_delay_ms(150);
	_delay_ms(150);
	PORT_INHIBIT_LED_1;
	while (1) {
		//===========================
		if (!(PIN_KEY_IN)) {
			_delay_ms(2);
			if (!(PIN_KEY_IN)) {
				FL_give = 1;
				PORT_PULS_LED_1;
			}
		} else {
			PORT_PULS_LED_0;
		}

		if (FL_give == 1) {
			FL_give = 0;
			PORT_PULS_LED_1;
			for (uint8_t i = 0; i < 4; i++) {
				for (uint8_t j = 0; j < 100; j++) {
					Give_5();
					Give_10();
					Give_20();
					Give_100();
				}

			}

		}

		// ========================================= banknociarka nabijanie =======================================================
		//  ====================================== koniec banknocarka nabijanie ===================================================
	}
}

void Wait(void) {
	for (uint8_t i = 0; i < 20; i++) {
		_delay_ms(100);
	}
}

void Give_5(void) {

	PORT_LINE1_COIN_OUT_1;
	_delay_ms(100);
	PORT_LINE1_COIN_OUT_0;
	Wait();
}

void Give_10(void) {

	PORT_LINE4_OUT_1;
	_delay_ms(100);
	PORT_LINE4_OUT_0;
	Wait();
}

void Give_20(void) {

	PORT_LINE3_OUT_1;
	_delay_ms(100);
	PORT_LINE3_OUT_0;
	Wait();
}

void Give_100(void) {
	PORT_LINE2_OUT_1;
	_delay_ms(100);
	PORT_LINE2_OUT_0;
	Wait();
}

// FUNCTIONS

