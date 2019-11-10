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
	sendCounterOut();

	sendStart();
	sendKeySwitch();
	chcek_end_game();
}

void sendCounterOut() {
	if (FL_automatOn) {
		if ((!(PIN_COUNTER_OUT_IN)) && FL_time_counter_OUT) {
			_delay_ms(1);
			if (!(PIN_COUNTER_OUT_IN)) {

				FL_time_counter_OUT = 0;
				counterTimeout_counter_OUT = 1;
				counter_pulses_out++;
				if (counter_pulses_out >= 100) {

					for (int i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = Counter_OUT_100_send;
							counter_pulses_out -= 100;
							i = buffer_size;

						}
					}
					FL_time_counter_OUT = 0;
					counterTimeout_counter_OUT = 1;

				}
			}
		}
		if (PIN_COUNTER_OUT_IN) {
			if (counterTimeout_counter_OUT) {
				counterTimeout_counter_OUT++;
			}
			if (counterTimeout_counter_OUT == counter_off) {

				for (int i = 0; i < buffer_size; i++) {

					if (commandBuffer[i] == 0) {
						if (counter_pulses >= 50) {
							commandBuffer[i] = Counter_OUT_50_send;
							counter_pulses_out -= 50;
							i++;
						}
					}
					if (commandBuffer[i] == 0) {
						if (counter_pulses_out >= 25) {
							commandBuffer[i] = Counter_OUT_25_send;
							counter_pulses_out -= 25;
							i++;
						}
					}
					if (commandBuffer[i] == 0) {
						if (counter_pulses_out >= 10) {
							commandBuffer[i] = Counter_OUT_10_send;
							counter_pulses_out -= 10;
							i++;
						}
					}
					if (commandBuffer[i] == 0) {
						if (counter_pulses_out >= 5) {
							commandBuffer[i] = Counter_OUT_5_send;
							counter_pulses_out -= 5;
							i++;
						}
					}
					if (commandBuffer[i] == 0) {
						if (counter_pulses_out >= 1) {
							commandBuffer[i] = Counter_OUT_1_send;
							counter_pulses_out -= 1;
							i++;
						}
					}
				}
				if (counter_pulses_out == 0) {
					counterTimeout_counter_OUT = 0;
				} else {
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
				if (counter_pulses >= 100) {

					for (int i = 0; i < buffer_size; i++) {
						if (commandBuffer[i] == 0) {
							commandBuffer[i] = Counter_IN_100_send;
							counter_pulses -= 100;
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
						if (counter_pulses >= 50) {
							commandBuffer[i] = Counter_IN_50_send;
							counter_pulses -= 50;
							i++;
						}
					}

					if (commandBuffer[i] == 0) {
						if (counter_pulses >= 20) {
							commandBuffer[i] = Counter_IN_20_send;
							counter_pulses -= 20;
							i++;
						}
					}

					if (commandBuffer[i] == 0) {
						if (counter_pulses >= 10) {
							commandBuffer[i] = Counter_IN_10_send;
							counter_pulses -= 10;
							i++;
						}
					}

					if (commandBuffer[i] == 0) {
						if (counter_pulses >= 5) {
							commandBuffer[i] = Counter_IN_5_send;
							counter_pulses -= 5;
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

	if ((!(PIN_KEY_AG_IN)) && (!(PIN_KEY_8_IN)) && (!(PIN_KEY_9_IN))) { ///dopisz !AG !9 8/////AG 8 !9
		loop_time = 0;
		FL_loop_time = 0;
		if (FL_KREDYT == 0) {
			_delay_ms(1);
			if ((!(PIN_KEY_AG_IN)) && (!(PIN_KEY_8_IN)) && (!(PIN_KEY_9_IN))) {
				FL_KREDYT = 1;
				FL_SEND_KREDYT = 0;
			}
		}
	}

	if (FL_loop_time) {
		OUT_5_HIGH;
		loop_time_mod++;
		if (loop_time_mod % 3 == 0) {
			loop_time++;

			if (loop_time == 65000) {
				FL_KREDYT = 0;
				loop_time = 0;
				FL_loop_time = 0;
			}
		}
	} else {
		OUT_5_LOW;
	}

	if ((!(PIN_KEY_AG_IN)) && (!(PIN_KEY_8_IN)) && (PIN_KEY_9_IN)) {
		_delay_ms(1);
		if ((!(PIN_KEY_AG_IN)) && (!(PIN_KEY_8_IN)) && (PIN_KEY_9_IN)) {

			FL_loop_time = 1;
		}
	}

	/*if ((PIN_KEY_AG_IN) && (PIN_KEY_8_IN) && (!(PIN_KEY_9_IN))) {
	 _delay_us(250);
	 if ((PIN_KEY_AG_IN) && (PIN_KEY_8_IN) && (!(PIN_KEY_9_IN))) {

	 FL_loop_time = 0;
	 loop_time = 0;
	 }
	 }*/

	if ((!(PIN_KEY_AG_IN)) && (PIN_KEY_8_IN) && (PIN_KEY_9_IN)) {
		if (FL_KREDYT == 1) {
			_delay_ms(1);
			if ((!(PIN_KEY_AG_IN)) && (PIN_KEY_8_IN) && (PIN_KEY_9_IN)) {
				FL_loop_time = 1;

			}
		}
	}

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

}
