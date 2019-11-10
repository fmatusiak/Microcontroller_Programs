/*
 * Tetris.c
 *
 *  Created on: 15-09-2016
 *      Author: pi
 */

#include "Quizomat.h"
#include "main.h"

void quizomat() {
	SetDisplay();
	checkQuizPayout();
	sendTimeCounter();
	sendStart();
	sendKeySwitch();
	SetRelay();
	checkQuizBet();
	checkQuizHold();
	checkQuizButton();
}

void sendTimeCounter() {
	if (FL_automatOn) {
		if ((!(PIN_COUNTER_IN)) && FL_time_counter) {
			_delay_ms(1);
			if (!(PIN_COUNTER_IN)) {
				FL_bet = 0;
				FL_hold = 0;
				FL_button = 0;
				FL_payout = 0;
				SWITCH_RELAY_LOW;

				FL_counter_in = 1;
				for (uint8_t i = 0; i < buffer_size; i++) {
					commandBuffer[i] = 0;
				}

				if (FL_start_rules_counter == 1) {
					for (uint8_t i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = com_quiz_start_rules;
							i = buffer_size;
						}
					}
					for (uint8_t i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = com_add_time_one;

							i = buffer_size;
						}
					}

					FL_start_rules_counter = 0;
				}
				FL_time_counter = 0;
				counterTimeout_counter = 1;

			}
		} else if (PIN_COUNTER_IN) {
			if (counterTimeout_counter) {
				counterTimeout_counter++;
			}
			if (counterTimeout_counter == counter_off) {
				FL_start_rules_counter = 1;
				SCREEN_SWITCH_OUT_LOW;

				counterTimeout_counter = 0;
			}
			FL_time_counter = 1;
		}
	}
}

void SetRelay() {
	if (receive == com_Relay_ON) {
		//	SWITCH_RELAY_HIGH;
		receive = 0;
	}
}

void SetDisplay() {
	if (receive == com_disp_ON) {
		receive = 0;
		SCREEN_SWITCH_OUT_LOW;

	}
}

void checkQuizBet() {
	if (receive == com_unlock_BET) {

		FL_bet = 1;
		receive = 0;
	}

	if (FL_bet) {
		if (!(PIN_BET_BUTTON_IN)) {

			BET_BUTTON_OUT_HIGH;

		} else {

			BET_BUTTON_OUT_LOW;
		}
	} else {
		BET_BUTTON_OUT_LOW;
	}
}

void checkQuizHold() {
	if (receive == com_unlock_HOLD) {

		FL_hold = 1;
		receive = 0;
	}

	if (FL_hold) {
		if (!(PIN_HOLD_BUTTON_IN)) {

			HOLD_BUTTON_OUT_HIGH;

		} else {

			HOLD_BUTTON_OUT_LOW;
		}
	} else {
		HOLD_BUTTON_OUT_LOW;

	}
}

void checkQuizButton() {
	if (receive == com_unlock_Button) {
		SWITCH_RELAY_HIGH;
		FL_button = 1;
		receive = 0;
	}

	if (FL_button) {
		if (!(PIN_BUTTON_BUTTON_IN)) {

			BUTTON_BUTTON_OUT_HIGH;

		} else {

			BUTTON_BUTTON_OUT_LOW;
		}
	} else {
		BUTTON_BUTTON_OUT_LOW;

	}
}

void checkQuizPayout() {
	if (receive == com_unlock_pay) {
		FL_payout = 1;
		receive = 0;
	}

	if (FL_payout) {
		if (!(PIN_PAYOUT_BUTTON_IN)) {
			_delay_ms(1);
			if (!(PIN_PAYOUT_BUTTON_IN)) {
				if (FL_wyk == 0) {
					FL_wyk = 1;
					for (uint8_t i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = klik_payout;
							i = buffer_size;
						}
					}
				}
			}
		} else {
			FL_wyk = 0;
		}
	} else {
		PAYOUT_OUT_LOW;
	}
}

void sendStart() {
	if (receive == com_round) {
		startTimeout = startImpulseTime;
		receive = 0;
	}
	if (startTimeout) {
		startTimeout--;
		START_OUT_HIGH;

	} else {
		START_OUT_LOW;
	}
}

void sendKeySwitch() {
	if ((!(PIN_KEY_SWITCH_IN)) && FL_keySwitch) {
		FL_keySwitch = 0;
		ALARM_LOW;
		SWITCH_RELAY_HIGH;
		FL_bet = 0;
		FL_hold = 0;
		FL_button = 0;
		FL_payout = 0;

		for (uint8_t i = 0; i < buffer_size; i++) {
			commandBuffer[i] = 0;
		}
		for (uint8_t i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = key_switch_clear;
				i = buffer_size;

			}
		}
	} else if ((PIN_KEY_SWITCH_IN) && (FL_keySwitch == 0)) {
		SWITCH_RELAY_LOW;
		FL_keySwitch = 1;
	}
}
