#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/eeprom.h"
#include "main.h"

volatile uint16_t led_one = 0, fL_button = 0;
volatile uint8_t stan_akt = 0;

int main(void) {

	DDR_KANAL_1_IN;
	DDR_KANAL_2_IN;
	DDR_KANAL_3_IN;
	DDR_KANAL_4_IN;
	DDR_PULS_1_OUT;
	DDR_PULS_2_OUT;

	KANAL_1_IN_VCC;
	KANAL_2_IN_VCC;
	KANAL_3_IN_VCC;
	KANAL_4_IN_VCC;

	PORT_PULS_1_OUT_0;
	PORT_PULS_2_OUT_0;

	while (1) {

		if ((!(PIN_KANAL_1_IN)) && (PIN_KANAL_3_IN) && (PIN_KANAL_4_IN)) {
			PORT_PULS_1_OUT_1;
		}

		else
		{
			PORT_PULS_1_OUT_0;
		}

		if ((!(PIN_KANAL_2_IN)) && (PIN_KANAL_3_IN) && (PIN_KANAL_4_IN)) {
			PORT_PULS_2_OUT_1;
		}

		else
		{
			PORT_PULS_2_OUT_0;
		}

	}

}
