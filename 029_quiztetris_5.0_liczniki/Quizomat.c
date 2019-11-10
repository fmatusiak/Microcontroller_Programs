/*
 * Tetris.c
 *
 *  Created on: 15-09-2016
 *      Author: pi
 */

#include "Quizomat.h"

void quizomat() {
	creditsCoinAcceptorQuizomat();
	creditsBillAcceptorQuizomat();
	checkQuizPayout();
	sendTimeCounter();
	sendStart();
	sendKeySwitch();
}

void sendTimeCounter() {
	if (FL_automatOn) {

		if ((!(PIN_COUNTER_OUT_IN)) && FL_COUNTER_OUT_OUT) {
			_delay_ms(1);
			if (!(PIN_COUNTER_OUT_IN)) {
				FL_COUNTER_OUT_OUT = 0;
				counterTimeout_counter_OUT = 1;
				counter_pulses_out++;
			}
		}

		if ((!(PIN_COUNTER_IN_IN)) && FL_time_counter) {
			_delay_ms(1);
			if (!(PIN_COUNTER_IN_IN)) {
				FL_counter_in = 1;
				if (FL_start_rules_counter == 1) {
					for (int i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = 3;
							i = buffer_size;
						}
					}
					FL_start_rules_counter = 0;
				}
				FL_time_counter = 0;
				counterTimeout_counter = 1;
				counter_pulses_in++;
			}
		}
		if (PIN_COUNTER_OUT_IN) {
			FL_COUNTER_OUT_OUT = 1;
			if (counterTimeout_counter_OUT) {
				counterTimeout_counter_OUT++;
			}
			if (counterTimeout_counter_OUT == counter_off) {

				counterTimeout_counter_OUT = 0;

				for (uint8_t i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						if (counter_pulses_out >= 250) {
							commandBuffer[i] = 28;
							counter_pulses_out -= 250;
							i++;
						}
						if (counter_pulses_out >= 100) {
							commandBuffer[i] = 27;
							counter_pulses_out -= 100;
							i++;
						}
						if (counter_pulses_out >= 50) {
							commandBuffer[i] = 26;
							counter_pulses_out -= 50;
							i++;
						}
						if (counter_pulses_out >= 20) {
							commandBuffer[i] = 25;
							counter_pulses_out -= 20;
							i++;
						}

						if (counter_pulses_out >= 10) {
							commandBuffer[i] = 24;
							counter_pulses_out -= 10;
							i++;
						}

						if (counter_pulses_out >= 5) {
							commandBuffer[i] = 23;
							counter_pulses_out -= 5;
							i++;
						}
					}
					if (commandBuffer[i] == 0) {
						if (counter_pulses_out >= 2) {
							commandBuffer[i] = 22;
							counter_pulses_out -= 2;
							i++;
						}
					}
					if (commandBuffer[i] == 0) {
						if (counter_pulses_out >= 1) {
							commandBuffer[i] = 21;
							counter_pulses_out -= 1;
							i++;
						}
					}
				}

			}
		}

		if (PIN_COUNTER_IN_IN) {
			FL_time_counter = 1;
			if (counterTimeout_counter) {
				counterTimeout_counter++;
			}
			if (counterTimeout_counter == counter_off) {
				FL_start_rules_counter = 1;
				SCREEN_SWITCH_OUT_LOW;
				for (uint8_t i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						if (counter_pulses_in >= 100) {
							commandBuffer[i] = 20;
							counter_pulses_in -= 100;
							i++;
						}
						if (counter_pulses_in >= 50) {
							commandBuffer[i] = 19;
							counter_pulses_in -= 50;
							i++;
						}
						if (counter_pulses_in >= 20) {
							commandBuffer[i] = 5;
							counter_pulses_in -= 20;
							i++;
						}

						if (counter_pulses_in >= 10) {
							commandBuffer[i] = 10;
							counter_pulses_in -= 10;
							i++;
						}

						if (counter_pulses_in >= 5) {
							commandBuffer[i] = 5;
							counter_pulses_in -= 5;
							i++;
						}
					}
					if (commandBuffer[i] == 0) {
						if (counter_pulses_in >= 2) {
							commandBuffer[i] = 2;
							counter_pulses_in -= 2;
							i++;
						}
					}
					if (commandBuffer[i] == 0) {
						if (counter_pulses_in >= 1) {
							commandBuffer[i] = 1;
							counter_pulses_in -= 1;
							i++;
						}
					}
				}

				counterTimeout_counter = 0;
			}
		}
	}
}

void creditsCoinAcceptorQuizomat() {
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
		for (uint8_t i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = 13;
				i = buffer_size;
			}
		}
	}
}

void creditsBillAcceptorQuizomat() {
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
		for (uint8_t i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = 13;
				i = buffer_size;
			}
		}
	}
}

void checkQuizPayout() {
	if (receive == 13) {

		FL_payout = 1;
	}
	if (receive == 12) {
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
	if (receive == 11) {
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
		for (uint8_t i = 0; i < buffer_size; i++) {
			commandBuffer[i] = 0;
		}
		for (uint8_t i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = 8;
				i = buffer_size;

			}
		}
	} else if (PIN_KEY_SWITCH_IN) {
		FL_keySwitch = 1;
	}
}
