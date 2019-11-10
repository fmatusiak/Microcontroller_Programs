#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/eeprom.h"
#include "main.h"

volatile uint16_t led_one = 0, fL_button = 0;
volatile uint8_t stan_akt = 0, FL_PULS = 0;

int main(void) {

	DDR_SWITCH_IN;
	SWITCH_IN_VCC;
	DDR_START_IN;
	START_IN_VCC;
	DDR_COUNTER_IN;
	COUNTER_IN_VCC;

	DDR_OUT_6;
	DDR_OUT_4;
	DDR_OUT_5;
	DDR_OUT_6;
	PORT_OUT_4_0;
	PORT_OUT_5_1;
	PORT_OUT_6_1;

	while (1) {
		if (!(PIN_COUNTER_IN)) {
			while (!(PIN_COUNTER_IN)) {
				PORT_OUT_4_1;
			}

		}

		if (!(PIN_START_IN)) {
			PORT_OUT_4_0;
		} else {
			PORT_OUT_4_1;
		}

		if ((!(PIN_SWITCH_IN)) && FL_PULS) {
			for (uint8_t i = 0; i < 100; i++) {
				_delay_us(10);
				if (!(PIN_START_IN)) {
					PORT_OUT_4_0;
				} else {
					PORT_OUT_4_1;
				}
			}
			if ((!(PIN_SWITCH_IN)) && FL_PULS) {
				FL_PULS = 0;
				PORT_OUT_6_0;
				for (uint8_t i = 0; i < 100; i++) {
					_delay_us(10);
					if (!(PIN_START_IN)) {
						PORT_OUT_4_0;
					} else {
						PORT_OUT_4_1;
					}
				}

				PORT_OUT_6_1;
				for (uint8_t i = 0; i < 100; i++) {
					_delay_us(10);
					if (!(PIN_START_IN)) {
						PORT_OUT_4_0;
					} else {
						PORT_OUT_4_1;
					}
				}
			}

		}
		if ((PIN_SWITCH_IN) && !(FL_PULS)) {
			for (uint8_t i = 0; i < 100; i++) {
				_delay_us(10);
				if (!(PIN_START_IN)) {
					PORT_OUT_4_0;
				} else {
					PORT_OUT_4_1;
				}
			}
			if ((PIN_SWITCH_IN) && !(FL_PULS)) {
				FL_PULS = 1;
			}
		}

	}
}
