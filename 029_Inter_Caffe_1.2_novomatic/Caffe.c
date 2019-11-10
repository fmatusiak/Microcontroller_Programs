/*
 * Caffe.c
 *
 *  Created on: 27 kwi 2017
 *      Author: dell
 */

#include "Caffe.h"
#include "main.h"

void Caffe(void) {
	Settings(); //Ustawienia raspberry
	PayOut();
	Emulate_Hopper();
	SendMoneyRasp();
	Disp_automat();
	Start_Nabij();
	Settings_automat();
}

void Settings_automat(void) {
	if ((!(PIN_SETTINGS_AUTOMAT_IN)) && FL_Settings_automat) {
		_delay_ms(2);
		if ((!(PIN_SETTINGS_AUTOMAT_IN)) && FL_Settings_automat) {
			FL_Settings_automat = 0;

			SETTINGS_AUTOMAT_OUT_Z;
			SETTINGS_AUTOMAT_REVERSE_OUT_Z;
		}
	}

	if ((PIN_SETTINGS_AUTOMAT_IN) && FL_Settings_automat == 0) {
		_delay_ms(2);
		if ((PIN_SETTINGS_AUTOMAT_IN) && FL_Settings_automat == 0) {
			FL_Settings_automat = 1;
		}
	}

}

void Settings(void) {
	if ((!(PIN_SETTINGS_IN)) && FL_keySwitch) {
		_delay_ms(2);
		if ((!(PIN_SETTINGS_IN)) && FL_keySwitch) {

			FL_keySwitch = 0;
			ALARM_LOW;
			SCREEN_SWITCH_OUT_LOW;

			for (uint8_t i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_key_switch;
					i = buffer_size;
				}
			}
		}
	}

	if ((PIN_SETTINGS_IN) && (!(FL_keySwitch))) {
		FL_keySwitch = 1;
	}

}
///////////////////////
void PayOut(void) {
	if ((!(PIN_PAYOUT_IN)) && (FL_PAYOUT)) {
		_delay_ms(2);
		if ((!(PIN_PAYOUT_IN)) && (FL_PAYOUT)) {
			_delay_ms(20);
			FL_PAYOUT = 0;
			PAYOUT_OUT_HIGH;
		}
	}
	if ((PIN_PAYOUT_IN) && (FL_PAYOUT == 0)) {
		FL_PAYOUT = 1;
		PAYOUT_OUT_LOW;
	}
}

void Emulate_Hopper(void) {
		if ((!(PIN_MOTOR_HOPPER_CONTROL_IN)) && FL_IMP_HOPPER) {
			_delay_ms(1);
			if ((!(PIN_MOTOR_HOPPER_CONTROL_IN)) && FL_IMP_HOPPER) {
				FL_IMP_HOPPER = 0;
				money_pulses++;
			}
		}
		if ((PIN_MOTOR_HOPPER_CONTROL_IN) && (FL_IMP_HOPPER == 0)) {
			_delay_ms(1);
			if ((PIN_MOTOR_HOPPER_CONTROL_IN) && (FL_IMP_HOPPER == 0)) {
				FL_IMP_HOPPER = 1;

			}
		}
}


//////////////////
void SendMoneyRasp(void) {
	if (FL_HOPPER == 0) {

		if (money_pulses >= 100) {
			for (uint8_t i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_money_hundred;
					money_pulses -= 100;
					i = buffer_size;
				}
			}
		}

		if (money_pulses >= 50) {
			for (uint8_t i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_money_fifty;
					money_pulses -= 50;
					i = buffer_size;

				}
			}
		}

		if (money_pulses >= 20) {
			for (uint8_t i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_money_twenty;
					money_pulses -= 20;
					i = buffer_size;

				}
			}
		}

		if (money_pulses >= 10) {
			for (uint8_t i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_money_ten;
					money_pulses -= 10;
					i = buffer_size;
				}
			}
		}

		if (money_pulses >= 5) {
			for (uint8_t i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {

					commandBuffer[i] = com_money_five;
					money_pulses -= 5;
					i = buffer_size;
				}
			}
		}

		if (money_pulses >= 2) {
			for (uint8_t i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_money_two;
					money_pulses -= 2;
					i = buffer_size;
				}
			}
		}

		if (money_pulses == 1) {
			for (uint8_t i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_money_one;
					money_pulses -= 1;
					i = buffer_size;
				}
			}
		}
	}
}

void Disp_automat(void) {
	if (receive == com_disp) {
		SCREEN_SWITCH_OUT_HIGH;
		FL_Nabij = 1;
		FL_keySwitch = 1;
	}

}

void Start_Nabij(void) {
	if ((!(PIN_GIVEMONEY_IN)) && (FL_Nabij)) {
		_delay_ms(2);
		if (!(PIN_GIVEMONEY_IN)) {
			SCREEN_SWITCH_OUT_LOW;
			FL_Nabij = 0;
			for (int i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_nabijKredyt;
					i = buffer_size;

				}
			}
		}
	}

}

