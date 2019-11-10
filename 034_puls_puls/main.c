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

	DDR_SWITCH_IN;
	DDR_LED_ONE_OUT;
	DDR_LED_TWO_OUT;
	DDR_RELAY_OUT;

	SWITCH_IN_VCC;
	PORT_LED_ONE_OUT_0;
	PORT_LED_TWO_OUT_0;
	PORT_RELAY_OUT_0;


	while (1) {
		_delay_ms(1000);
		_delay_ms(1000);
		_delay_ms(1000);
		_delay_ms(1000);

		PORT_LED_ONE_OUT_0;
		_delay_ms(100);
		PORT_LED_ONE_OUT_1;
		_delay_ms(100);
	}
}
