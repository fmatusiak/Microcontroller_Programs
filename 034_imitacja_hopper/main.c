#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/eeprom.h"
#include "main.h"

uint8_t FL_START_PAYOUT = 0;
uint8_t FL_Hopper_DOWN = 1, FL_Hopper_UP = 0;
uint16_t Tmp_time_hopper_low = 10000, Tmp_time_hopper_high = 10000,
		time_hopper = 10000;

void Emulate_Hopper(void);
void Hopper_control(void);
void Hopper_down(void);
void Hopper_up(void);

int main(void) {
	DDR_KEY_SWITCH_IN;
	DDR_MOTOR_HOPPER_CONTROL_IN;
	DDR_PAYOUT_OUT;
	DDR_HOPPER_COIN_OUT;

	MOTOR_HOPPER_CONTROL_IN_VCC;
	KEY_SWITCH_IN_VCC;

	HOPPER_PULS_OUT_LOW;
	PORT_PAYOUT_OUT_1;

	while (1) {
		Emulate_Hopper();

		if ((!(PIN_KEY_SWITCH_IN)) && FL_START_PAYOUT == 0) {
			_delay_ms(2);
			if (!(PIN_KEY_SWITCH_IN)) {
				FL_START_PAYOUT = 1;
				PORT_PAYOUT_OUT_0;
			}
		}

		if ((PIN_KEY_SWITCH_IN) && FL_START_PAYOUT) {
			_delay_ms(2);
			if ((PIN_KEY_SWITCH_IN) && FL_START_PAYOUT) {
				FL_START_PAYOUT = 0;

				FL_Hopper_UP = 0;
				FL_Hopper_DOWN = 1;

				PORT_PAYOUT_OUT_1;
				HOPPER_PULS_OUT_LOW;
				Tmp_time_hopper_high = time_hopper;
				Tmp_time_hopper_low = time_hopper;
			}
		}

	}
}

void Emulate_Hopper(void) {
	if ((!(PIN_MOTOR_HOPPER_CONTROL_IN)) && (FL_START_PAYOUT)) {
		Hopper_control();
	}

}

void Hopper_control(void) {
	Hopper_down();
	Hopper_up();
}

void Hopper_down(void) {
	if (FL_Hopper_DOWN) {
		if (Tmp_time_hopper_low) {
			Tmp_time_hopper_low--;
			HOPPER_PULS_OUT_HIGH;

		} else {
			FL_Hopper_UP = 1;
			FL_Hopper_DOWN = 0;
			Tmp_time_hopper_low = time_hopper;
		}
	}
}

void Hopper_up(void) {
	if (FL_Hopper_UP) {

		if (Tmp_time_hopper_high) {
			Tmp_time_hopper_high--;
			HOPPER_PULS_OUT_LOW;

		} else {
			Tmp_time_hopper_high = time_hopper;
			FL_Hopper_UP = 0;
			FL_Hopper_DOWN = 1;

		}
	}
}
