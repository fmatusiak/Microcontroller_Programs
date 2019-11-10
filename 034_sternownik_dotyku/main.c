#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/eeprom.h"
#include "main.h"

volatile uint16_t led_one = 0, fL_button = 0;
volatile uint8_t stan_akt = 0;
uint8_t EEMEM stan_zapis = 0;

int main(void) {

	DDR_SWITCH_IN;
	DDR_LED_ONE_OUT;
	DDR_LED_TWO_OUT;
	DDR_RELAY_OUT;

	SWITCH_IN_VCC;
	PORT_LED_ONE_OUT_0;
	PORT_LED_TWO_OUT_0;
	PORT_RELAY_OUT_0;

	stan_akt = eeprom_read_byte (&stan_zapis) ;

	if (stan_akt == 0) {
		PORT_LED_TWO_OUT_0;
		PORT_RELAY_OUT_0;
		stan_akt = 1;
	} else {
		PORT_LED_TWO_OUT_1;
		PORT_RELAY_OUT_1;
		stan_akt = 0;
	}

	while (1) {

		led_one++;
		if (led_one >= 62000) {
			led_one = 0;
			PORT_LED_ONE_OUT_z;
		}

		if ((!(PIN_SWITCH_IN)) && (fL_button == 0)) {
			_delay_ms(5);
			if ((!(PIN_SWITCH_IN)) && (fL_button == 0)) {
				fL_button = 1;

				if (stan_akt == 0) {
					PORT_LED_TWO_OUT_0;
					PORT_RELAY_OUT_0;
					stan_akt = 1;
					eeprom_write_byte(&stan_zapis, 0);
				}
				else  {
					PORT_LED_TWO_OUT_1;
					PORT_RELAY_OUT_1;
					stan_akt = 0;
					eeprom_write_byte(&stan_zapis, 1);
				}

			}
		}

		if (PIN_SWITCH_IN) {
			fL_button = 0;
		}

	}
}
