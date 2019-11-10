#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/eeprom.h"
#include "main.h"

volatile uint16_t time = 0;
volatile uint8_t FL_Kredyty = 1, FL_send = 0;

int main(void) {

	DDR_KEY_0_IN;
	DDR_KEY_9_IN;
	DDR_KEY_AG_IN;
	DDR_KEY_WP_IN;
	DDR_PAY_OUT;

	KEY_0_IN_VCC;
	KEY_9_IN_VCC;
	KEY_AG_IN_VCC;
	KEY_WP_IN_VCC;

	PORT_PAY_OUT_0;
	while (1) {

		if ((!(PIN_KEY_AG_IN)) & (!(PIN_KEY_WP_IN)) & (!(PIN_KEY_9_IN))) {
			_delay_ms(5);
			if ((!(PIN_KEY_AG_IN)) & (!(PIN_KEY_WP_IN)) & (!(PIN_KEY_9_IN))) {
				FL_Kredyty = 1;
				FL_send = 0;
			}

		}

		if ((!(PIN_KEY_AG_IN)) & (!(PIN_KEY_WP_IN))) {
			_delay_ms(5);
			if ((!(PIN_KEY_AG_IN)) & (!(PIN_KEY_WP_IN))) {
				FL_Kredyty = 1;
				FL_send = 0;
			}

		}

		if ((!(PIN_KEY_AG_IN)) && (PIN_KEY_WP_IN) && (PIN_KEY_9_IN)) {
			_delay_ms(5);
			if ((!(PIN_KEY_AG_IN)) && (PIN_KEY_WP_IN) && (PIN_KEY_9_IN)) {
				FL_Kredyty = 0;
			}

		}

		if (FL_Kredyty == 0) {
			if (FL_send == 0) {
				FL_send = 1;

				PORT_PAY_OUT_1;
				_delay_ms(125);
				PORT_PAY_OUT_0;
			}
		}
	}
}
