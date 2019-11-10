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
	Settings_automat();
	PayOut();
	Emulate_Hopper();
	Disp_automat();

}
void Settings(void) {
	if (receive == com_setting_rasp_on) {
		receive = 0;
		SCREEN_SWITCH_OUT_LOW;
	}
	if (receive == com_disp) {
		receive = 0;
		SCREEN_SWITCH_OUT_HIGH;
	}

}
void Settings_automat(void) {
	if (receive == com_setting_automat) {
		receive = 0;
		SETTINGS_AUTOMAT_OUT_Z;
		SETTINGS_AUTOMAT_REVERSE_OUT_Z;
	}
}


///////////////////////
void PayOut(void) {
	if (receive == com_payout) {
		receive = 0;
		PAYOUT_OUT_HIGH;
		FL_HOPPER = 1;
		FL_Hopper_time = 0;
		_delay_ms(100);
		PAYOUT_OUT_LOW;
	}
}

void Emulate_Hopper(void) {
	if ((!(PIN_MOTOR_HOPPER_CONTROL_IN)) && FL_HOPPER) {
		FL_Hopper_time = 1;
		Hopper_control();
	}

	if ((PIN_MOTOR_HOPPER_CONTROL_IN) && FL_Hopper_time) {
		_delay_ms(2);
		if ((PIN_MOTOR_HOPPER_CONTROL_IN) && FL_Hopper_time) {
			FL_Hopper_UP = 0;
			FL_Hopper_DOWN = 1;

			FL_HOPPER = 0;
			HOPPER_PULS_OUT_LOW;
			Tmp_time_hopper_high = time_hopper;
			Tmp_time_hopper_low = time_hopper;
		}
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
//////////////////

void Disp_automat(void) {
	if (receive == com_disp) {
		SCREEN_SWITCH_OUT_HIGH;
		FL_keySwitch = 1;
	}

}




