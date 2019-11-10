#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "main.h"

volatile uint8_t punkty = 0, FL_time = 0, FL_V1 = 1, FL_V2 = 1, FL_V3 = 1,
		FL_V4 = 1, FL_V5 = 1;
volatile uint16_t tmp_time = 0, time_out = 50000;
void check_points(void);
#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

int main(void) {
	DDR_VEND1_IN;
	DDR_VEND2_IN;
	DDR_VEND3_IN;
	DDR_VEND4_IN;
	DDR_VEND5_IN;
	DDR_puls;
	DDR_puls_2;

	PORT_puls_0;
	PORT_puls_2_0;
	//PORT_puls_0_2;
	VEND1_IN_VCC;
	VEND2_IN_VCC;
	VEND3_IN_VCC;
	VEND4_IN_VCC;
	VEND5_IN_VCC;

	while (1) {
		check_points();

		if (punkty) {
			for (uint8_t i = 0; i < 50; i++) {
				check_points();
				_delay_ms(10);
			}

			PORT_puls_1;
			PORT_puls_2_1;
			for (uint8_t i = 0; i < 10; i++) {
				check_points();
				_delay_ms(10);
			}
			PORT_puls_0;
			PORT_puls_2_0;
			punkty -= 5;
		}
	}
}

void check_points(void) {
	if (!(PIN_VEND1_IN) && (FL_V1)) {
		_delay_ms(2);
		if (!(PIN_VEND1_IN) && (FL_V1)) {
			FL_V1 = 0;
		}
	}

	if ((PIN_VEND1_IN) && (!(FL_V1))) {
		_delay_ms(2);
		if ((PIN_VEND1_IN) && (!(FL_V1))) {
			FL_V1 = 1;
			punkty += 10;
		}
	}

	if (!(PIN_VEND2_IN) && (FL_V2)) {
		_delay_ms(2);
		if (!(PIN_VEND2_IN) && (FL_V2)) {
			FL_V2 = 0;
		}
	}

	if ((PIN_VEND2_IN) && (!(FL_V2))) {
		_delay_ms(2);
		if ((PIN_VEND2_IN) && (!(FL_V2))) {
			FL_V2 = 1;
			punkty += 5;
		}
	}
}
