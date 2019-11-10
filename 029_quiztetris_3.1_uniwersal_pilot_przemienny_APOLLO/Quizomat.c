/*
 * Tetris.c
 *
 *  Created on: 15-09-2016
 *      Author: pi
 */

#include "Quizomat.h"
#include "main.h"

void quizomat() {
	checkAutostart();
	checkQuizPayout();
	sendTimeCounter();
	sendStart();
	sendKeySwitch();
}

void checkAutostart() {

	if (FL_automatOn) {
		if (!(PIN_AUTOSTART_IN)) {
			AUTOSTARTR_OUT_HIGH;
		}

		if (PIN_AUTOSTART_IN) {
			AUTOSTARTR_OUT_LOW;
		}
	}

	else {
		AUTOSTARTR_OUT_LOW;
	}

}

void sendTimeCounter() {

	if ((!(PIN_COUNTER_IN)) && FL_time_counter) {
		_delay_ms(1);
		if (!(PIN_COUNTER_IN)) {
			FL_counter_in = 1;
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
			if (counter_pulses >= 10) {

				for (int i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = 10;
						counter_pulses -= 10;
						i = buffer_size;

					}
				}
			}
		}
	} else if (PIN_COUNTER_IN) {
		if (counterTimeout_counter) {
			counterTimeout_counter++;
		}
		if (counterTimeout_counter == counter_off) {
			FL_start_rules_counter = 1;

			for (int i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					if (counter_pulses >= 5) {
						commandBuffer[i] = 5;
						counter_pulses -= 5;
						i++;
					}
				}
				if (commandBuffer[i] == 0) {
					if (counter_pulses >= 2) {
						commandBuffer[i] = 2;
						counter_pulses -= 2;
						i++;
					}
				}
				if (commandBuffer[i] == 0) {
					if (counter_pulses >= 1) {
						commandBuffer[i] = 1;
						counter_pulses -= 1;
						i++;
					}
				}
			}

			counterTimeout_counter = 0;
		}
		FL_time_counter = 1;
	}

}

void checkQuizPayout() {
	if (receive == com_unlock_pay) {

		FL_payout = 1;
	}
	if (receive == com_lock_pay) {
		FL_payout = 0;
	}
	if (FL_payout) {
		if (!(PIN_PAYOUT_BUTTON_IN)) {
			PAYOUT_OUT_HIGH;
		} else {
			PAYOUT_OUT_LOW;
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
		for (int i = 0; i < buffer_size; i++) {
			commandBuffer[i] = 0;
		}
		for (int i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = 8;
				i = buffer_size;

			}
		}
	} else if (PIN_KEY_SWITCH_IN) {
		FL_keySwitch = 1;
	}
}
