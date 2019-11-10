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
	sendTimeCounter();
	sendTimeBill();
	sendStart();
	sendKeySwitch();
	chcek_end_game();
}

void sendTimeCounter() {
	if (FL_automatOn) {
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
				SCREEN_SWITCH_OUT_LOW;
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
}
void sendTimeBill() {

	if (!(PIN_BILL_ACCEPTOR_IN) && FL_counter && (FL_automatOn == 0)) {
		_delay_ms(1);
		if (!(PIN_BILL_ACCEPTOR_IN)) {
			FL_counter_in = 1;
			if (FL_start_rules == 1) {
				for (int i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = com_quiz_start_rules;
						i = buffer_size;
					}
				}
				FL_start_rules = 0;
			}
			FL_counter = 0;
			counterTimeout = 1;
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
	} else if (PIN_BILL_ACCEPTOR_IN) {
		if (counterTimeout) {
			counterTimeout++;
		}
		if (counterTimeout == counter_off1) {
			FL_start_rules = 1;
			SCREEN_SWITCH_OUT_LOW;
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
			counterTimeout = 0;
		}
		FL_counter = 1;
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
		for (int i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = com_attack;
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
	if (FL_payout) {
		if (!(PIN_PAYOUT_BUTTON_IN)) {
			_delay_ms(1);
			if (!(PIN_PAYOUT_BUTTON_IN)) {
				if (FL_wyk == 0) {
					FL_wyk = 1;
					for (int i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = 18;

							i = buffer_size;
						}
					}
				}
			}
			//	PAYOUT_OUT_HIGH;
		} else {
			FL_wyk = 0;
			//	PAYOUT_OUT_LOW;
		}
	} else {
		PAYOUT_OUT_LOW;

	}
}

void sendStart() {
	if (receive == com_round) {
		receive = 0;
		startTimeout = 0;
		START_OUT_HIGH;
		_delay_ms(75);
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

void chcek_end_game() {
	//aktywne
	if (((PIN_KEY_0_IN) && (!(PIN_KEY_1_IN)) && (PIN_KEY_9_IN))
			|| ((!(PIN_KEY_0_IN)) && (PIN_KEY_1_IN) && (!(PIN_KEY_9_IN)))
			|| ((PIN_KEY_0_IN) && (PIN_KEY_1_IN) && (!(PIN_KEY_9_IN)))) {
		loop_time = 0;
		FL_loop_time = 0;
		if (FL_KREDYT == 0) {
			_delay_ms(1);
			if (((PIN_KEY_0_IN) && (!(PIN_KEY_1_IN)) && (PIN_KEY_9_IN))
					|| ((!(PIN_KEY_0_IN)) && (PIN_KEY_1_IN) && (!(PIN_KEY_9_IN)))
					|| ((PIN_KEY_0_IN) && (PIN_KEY_1_IN) && (!(PIN_KEY_9_IN)))) { //!0!
				FL_KREDYT = 1;
				FL_SEND_KREDYT = 0;
			}
		}
	}
	if (FL_loop_time) {

		OUT_5_HIGH;
		loop_time++;

		if (loop_time == 30000) {
			FL_KREDYT = 0;
			loop_time = 0;
			FL_loop_time = 0;

		}
	}

	/*if (FL_loop_time) {

	 OUT_5_LOW;
	 loop_time_mod++;
	 if (loop_time_mod % 1 == 0) {
	 loop_time++;

	 if (loop_time == 65000) {
	 FL_KREDYT = 0;
	 loop_time = 0;
	 FL_loop_time = 0;
	 }
	 }*/

	else {
		OUT_5_LOW;
	}

//nie aktywne

//nie akwtyne wyplata
//if ((!(PIN_KEY_AG_IN)) & (PIN_KEY_8_IN) & (PIN_KEY_9_IN)) {
	if ((PIN_KEY_0_IN) && (PIN_KEY_1_IN) && (PIN_KEY_9_IN)) {
		if (FL_KREDYT == 1) {
			_delay_ms(1);
			if ((PIN_KEY_0_IN) && (PIN_KEY_1_IN) && (PIN_KEY_9_IN)) {
				FL_loop_time = 1;

			}
		}
	} else {

	}

//wyplata
	if ((FL_KREDYT == 0) && (FL_SEND_KREDYT == 0)) {
		FL_SEND_KREDYT = 1;
		loop_time = 0;

		for (int i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = 18;
				i = buffer_size;

			}
		}

	}
//na chuj out 5?

}
