/*
 * Tetris.c
 *
 *  Created on: 15-09-2016
 *      Author: pi
 */

#include "Quizomat.h"
#include "main.h"

void quizomat() {
	creditsCoinAcceptorQuizomat();
	creditsBillAcceptorQuizomat();
	checkQuizPayout();
	sendStart();
	sendKeySwitch();
	sendTimeCounter();
}


void sendTimeCounter() {
	if (FL_automatOn) {
		if ((!(PIN_COUNTER_IN)) && FL_time_counter) {
			_delay_ms(1);
			if (!(PIN_COUNTER_IN)) {


				FL_payout = 0;
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
				if (counter_pulses >= 10) {

					for (int i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = Counter_IN_10_send;
							counter_pulses -= 10;
							i = buffer_size;

						}
					}
					FL_time_counter = 0;
					counterTimeout_counter = 1;

				}
			}
		}
		if (PIN_COUNTER_IN) {
			if (counterTimeout_counter) {
				counterTimeout_counter++;
			}
			if (counterTimeout_counter == counter_off) {
				FL_start_rules_counter = 1;
				SCREEN_SWITCH_OUT_LOW;

				for (int i = 0; i < buffer_size; i++) {


					if (commandBuffer[i] == 0) {
						if (counter_pulses >= 5) {
							commandBuffer[i] = Counter_IN_5_send;
							counter_pulses -= 5;
							i++;
						}
					}

					if (commandBuffer[i] == 0) {
						if (counter_pulses >= 2) {
							commandBuffer[i] = Counter_IN_2_send;
							counter_pulses -= 2;
							i++;
						}
					}
					if (commandBuffer[i] == 0) {
						if (counter_pulses >= 1) {
							commandBuffer[i] = Counter_IN_1_send;
							counter_pulses -= 1;
							i++;
						}
					}
				}
				if (counter_pulses == 0) {
					counterTimeout_counter = 0;
				} else {
					counterTimeout_counter = 1;
				}

			}
			FL_time_counter = 1;
		}
	}
}

void creditsCoinAcceptorQuizomat() {
	sendTimeCounter();
	if ((!(PIN_PROTECTION_IN)) && PROT_ON) {
		COIN_ACCEPTOR_OUT_LOW;
		FL_protection = 1;
	} else if (!(PIN_COIN_ACCEPTOR_IN)) {
		COIN_ACCEPTOR_OUT_HIGH;
	} else {
		COIN_ACCEPTOR_OUT_LOW;
	}
	if ((PIN_PROTECTION_IN) && (FL_protection)) {
		FL_protection = 0;
		ALARM_HIGH;
		for (int i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = com_attack;
				i = buffer_size;
			}
		}
	}
}

void creditsBillAcceptorQuizomat() {
	sendTimeCounter();
	if ((!(PIN_PROTECTION_IN)) && PROT_ON) {
		BILL_ACCEPTOR_OUT_LOW;
		FL_protection = 1;
	} else if (!(PIN_BILL_ACCEPTOR_IN)) {
		BILL_ACCEPTOR_OUT_HIGH;
	} else {
		BILL_ACCEPTOR_OUT_LOW;
	}
	if ((PIN_PROTECTION_IN) && (FL_protection)) {
		FL_protection = 0;
		ALARM_HIGH;
		for (int i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = com_attack;
				i = buffer_size;
			}
		}
	}
}

void checkQuizPayout() {
	if (receive == com_unlock_pay) {
		FL_payout = 1;
		receive = 0;
	}
	if (receive == com_lock_pay) {
		FL_payout = 0;
		receive = 0;
	}

}

void sendStart() {
	if (receive == com_round) {
		receive = 0;
		startTimeout = 0;
		START_OUT_HIGH;

		for (uint8_t obr = 0; obr < 75; obr++) {
			sendTimeCounter();
			_delay_ms(1);
		}
		START_OUT_LOW;
	}
}


void sendKeySwitch() {
	if ((!(PIN_KEY_SWITCH_IN)) && FL_keySwitch) {
		FL_keySwitch = 0;

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


