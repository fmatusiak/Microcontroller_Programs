#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/eeprom.h"
#include "main.h"

volatile uint16_t led_one = 0, fL_button = 0;
volatile uint8_t stan_akt = 0;

int main(void) {

	DDR_KEY_1_IN;
	DDR_KEY_2_IN;

	DDR_KEYSWITCH_OUT;
	DDR_KEY_2_OUT;

	KEY_1_IN_VCC;
	KEY_2_IN_VCC;
	PORT_KEYSWITCH_OUT_1;
	PORT_KEY_2_OUT_1;

	while (1) {

		if (!(PIN_KEY_1_IN)) {
			_delay_ms(5);
			if (!(PIN_KEY_1_IN)) {
				_delay_ms(5);
				if (!(PIN_KEY_1_IN)) {
					_delay_ms(5);
					if (!(PIN_KEY_1_IN)) {
						PORT_KEYSWITCH_OUT_0;
						_delay_ms(100);
						PORT_KEY_2_OUT_0;
						_delay_ms(150);
						PORT_KEY_2_OUT_1;
						_delay_ms(150);
						PORT_KEY_2_OUT_0;
						PORT_KEY_3_OUT_0;
						_delay_ms(150);
						PORT_KEY_2_OUT_1;
						PORT_KEY_3_OUT_1;
						_delay_ms(500);
						_delay_ms(500);
						_delay_ms(500);
						_delay_ms(500);
						_delay_ms(500);
						_delay_ms(500);

						PORT_KEYSWITCH_OUT_1;
					}
				}
			}
		}
	}
}
