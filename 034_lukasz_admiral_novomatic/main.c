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
	SWITCH_IN_VCC;
	DDR_OUT_5;
	PORT_OUT_5_0;


	while (1) {
		if (!(PIN_SWITCH_IN)) {
			PORT_OUT_5_0;


		}

		else {
			PORT_OUT_5_1;


		}
	}
}
