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
	sendCounterOut();
	sendStart();
	sendKeySwitch();
	SetRelay();
	checkQuizBet();
	checkQuizHold();
	checkQuizButton();
}

void sendCounterOut() {
	if (FL_automatOn) {
		if ((!(PIN_COUNTER_OUT_IN)) && FL_time_counter_OUT) {
			_delay_ms(1);
			if (!(PIN_COUNTER_OUT_IN)) {

				for (uint8_t i = 0; i < buffer_size; i++) {
					commandBuffer[i] = 0;
				}

				FL_time_counter_OUT = 0;
				counterTimeout_counter_OUT = 1;
				counter_pulses_out++;
				if (counter_pulses_out >= 100) {

					for (int i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = Counter_OUT_25;
							counter_pulses_out -= 100;
							i = buffer_size;

						}
					}
					FL_time_counter_OUT = 0;
					counterTimeout_counter_OUT = 1;

				}
			}
		} else if (PIN_COUNTER_OUT_IN) {
			if (counterTimeout_counter_OUT) {
				counterTimeout_counter_OUT++;
			}
			if (counterTimeout_counter_OUT == counter_off) {

				for (int i = 0; i < buffer_size; i++) {

					if (commandBuffer[i] == 0) {
						if (counter_pulses >= 40) {
							commandBuffer[i] = Counter_OUT_10;
							counter_pulses_out -= 40;
							i++;
						}
					}

					 if (commandBuffer[i] == 0) {
						if (counter_pulses_out >= 10) {
							commandBuffer[i] = Counter_OUT_5;
							counter_pulses_out -= 10;
							i++;
						}
					}
					 if (commandBuffer[i] == 0) {
						if (counter_pulses_out >= 5) {
							commandBuffer[i] = Counter_OUT_2;
							counter_pulses_out -= 5;
							i++;
						}
					}
					 if (commandBuffer[i] == 0) {
						if (counter_pulses_out >= 1) {
							commandBuffer[i] = Counter_OUT_1;
							counter_pulses_out -= 1;
							i++;
						}
					}
				}
				if(counter_pulses_out == 0)
				{
					counterTimeout_counter_OUT = 0;
				}
				else
				{
					counterTimeout_counter_OUT = 1;
				}

			}
			FL_time_counter_OUT = 1;
		}
	}
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
					for (int i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = com_quiz_start_rules;
							i = buffer_size;
						}
					}
					FL_start_rules_counter = 0;
				}
				FL_time_counter = 0;
				counterTimeout_counter = 1;
				counter_pulses++;
				if (counter_pulses >= 100) {

					for (int i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = Counter_IN_25;
							counter_pulses -= 100;
							i = buffer_size;

						}
					}
					FL_time_counter = 0;
					counterTimeout_counter = 1;

				}
			}
		} else if (PIN_COUNTER_IN) {
			if (counterTimeout_counter) {
				counterTimeout_counter++;
			}
			if (counterTimeout_counter == counter_off) {
				FL_start_rules_counter = 1;
				SCREEN_SWITCH_OUT_LOW;

				for (int i = 0; i < buffer_size; i++) {

					if (commandBuffer[i] == 0) {
						if (counter_pulses >= 50) {
							commandBuffer[i] = Counter_IN_10;
							counter_pulses -= 50;
							i++;
						}
					}

					 if (commandBuffer[i] == 0) {
						if (counter_pulses >= 20) {
							commandBuffer[i] = Counter_IN_5;
							counter_pulses -= 20;
							i++;
						}
					}
					 if (commandBuffer[i] == 0) {
						if (counter_pulses >= 5) {
							commandBuffer[i] = Counter_IN_2;
							counter_pulses -= 5;
							i++;
						}
					}
					 if (commandBuffer[i] == 0) {
						if (counter_pulses >= 1) {
							commandBuffer[i] = Counter_IN_1;
							counter_pulses -= 1;
							i++;
						}
					}
				}
				if(counter_pulses == 0)
				{
					counterTimeout_counter = 0;
				}
				else
				{
					counterTimeout_counter = 1;
				}


			}
			FL_time_counter = 1;
		}
	}
}

void SetRelay() {
	if (receive == com_Relay_ON) {
		SWITCH_RELAY_HIGH;
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
			if (FL_wyk_byt == 0) {
				FL_wyk_byt = 1;
				for (uint8_t i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = klik_stawka;
						i = buffer_size;
					}
				}
			}

		} else {
			FL_wyk_byt = 0;
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

	if (!(PIN_HOLD_BUTTON_IN)) {

		HOLD_BUTTON_OUT_HIGH;
		if (FL_wyk_hold == 0) {
			FL_wyk_hold = 1;
			for (uint8_t i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = klik_podglad;
					i = buffer_size;
				}
			}
		}

	} else {
		FL_wyk_hold = 0;
		HOLD_BUTTON_OUT_LOW;
	}

}

void checkQuizButton() {
	if (receive == com_unlock_Button) {

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
