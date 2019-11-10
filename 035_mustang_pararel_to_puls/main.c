#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "main.h"

void _delay_and_check(uint8_t time);
void check_state(void);

volatile uint8_t FL_Line_1 = 0;

volatile uint8_t Credit = 0;

volatile uint16_t Tmp_Time = 0;

int main(void) {

	DDR_LINE1_IN;
	LINE1_IN_VCC;

	DDR_LINE1_OUT;
	DDR_LINE2_OUT;
	DDR_LINE3_OUT;
	DDR_LINE4_OUT;

	PORT_LINE1_OUT_0;
	PORT_LINE2_OUT_0;
	PORT_LINE3_OUT_0;
	PORT_LINE4_OUT_0;

	_delay_ms(500);
	while (1) {

		check_state();

		if (Credit) {
			Tmp_Time++;

			if (Tmp_Time >= 60000) {
				Tmp_Time = 0;

				if (Credit >= 10) {
					PORT_LINE4_OUT_1;
					_delay_and_check(99);
					PORT_LINE4_OUT_0;
					_delay_and_check(99);
					Credit -= 10;
				}

				if (Credit >= 5) {
					PORT_LINE3_OUT_1;
					_delay_and_check(99);
					PORT_LINE3_OUT_0;
					_delay_and_check(99);
					Credit -= 5;
				}

				if (Credit >= 2) {
					PORT_LINE2_OUT_1;
					_delay_and_check(99);
					PORT_LINE2_OUT_0;
					_delay_and_check(99);
					Credit -= 2;
				}

				if (Credit >= 1) {
					PORT_LINE1_OUT_1;
					_delay_and_check(99);
					PORT_LINE1_OUT_0;
					_delay_and_check(99);
					Credit -= 1;
				}
			}
		}
	}
}

void _delay_and_check(uint8_t time) {

	for (uint8_t i = 0; i < time; i++) {
		_delay_ms(1);
		check_state();
	}

}

void check_state(void) {

	if ((!(PIN_LINE1_IN)) && (FL_Line_1 == 1)) {
		_delay_us(5);
		if (!(PIN_LINE1_IN)) {
			Credit++;
			FL_Line_1 = 0;
			Tmp_Time = 0;
		}
	}

	if ((PIN_LINE1_IN) && (FL_Line_1 == 0)) {
		_delay_us(5);
		if (PIN_LINE1_IN) {
			FL_Line_1 = 1;
		}
	}

}
