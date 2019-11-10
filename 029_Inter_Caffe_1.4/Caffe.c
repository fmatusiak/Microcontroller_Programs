/*
 * Caffe.c
 *
 *  Created on: 27 kwi 2017
 *      Author: dell
 */

#include "Caffe.h"
#include "main.h"

void Caffe(void) {
	//Settings(); //Ustawienia raspberry


	SendMoneyRasp();
	Disp_automat();
	Start_Nabij();

	Disp_caffe();

}



void Settings(void) {
	if ((!(PIN_SETTINGS_IN)) && FL_keySwitch) {
		_delay_ms(2);
		if ((!(PIN_SETTINGS_IN)) && FL_keySwitch) {


			while (!sendCommand(com_key_switch)) {
				;

			}
			while(1)
			{
				;
			}
		}
	}

	if ((PIN_SETTINGS_IN) && (!(FL_keySwitch))) {
		FL_keySwitch = 1;
	}

}
///////////////////////





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
		receive = 0;
		FL_SCREEN = 1;
	}

}

void Disp_caffe(void) {
	if (receive == com_disp_caffe) {
		SCREEN_SWITCH_OUT_LOW;
		FL_SCREEN = 0;
		FL_Nabij = 1;
		FL_keySwitch = 1;
		receive = 0;
	}
}


void Start_Nabij(void) {
	if (((!(PIN_GIVEMONEY_IN)) && (FL_Nabij)) && (FL_SCREEN))  {
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

