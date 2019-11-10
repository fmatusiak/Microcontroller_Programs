
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

void sendTimeCounter(void) {

	if (counter_pulses) {

		counterTimeout ++;
		if (counterTimeout >= 25) {


			for (uint8_t i = 0; i < buffer_size; i++) {
				commandBuffer[i] = 0;
			}

			counterTimeout = 0;
			if (FL_start_rules_counter == 1) {
				for (int i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = com_quiz_start_rules;
						i = buffer_size;
					}
				}
				FL_start_rules_counter = 0;
			}

			for (int i = 0; i < buffer_size; i++) {

				if (commandBuffer[i] == 0) {
					if (counter_pulses >= 10) {
						commandBuffer[i] = Counter_IN_10;
						counter_pulses -= 10;
						i++;
					}
				}

				if (commandBuffer[i] == 0) {
					if (counter_pulses >= 5) {
						commandBuffer[i] = Counter_IN_5;
						counter_pulses -= 5;
						i++;
					}
				}

				if (commandBuffer[i] == 0) {
					if (counter_pulses >= 2) {
						commandBuffer[i] = Counter_IN_2;
						counter_pulses -= 2;
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
		}
	}
	else
	{
		counterTimeout = 0;
	}

}

void creditsCoinAcceptorQuizomat(void) {

	if (PIN_PROTECTION_IN) {
		FL_protection = 1;
		if (!(PIN_COIN_ACCEPTOR_IN)) {
			COIN_ACCEPTOR_OUT_HIGH;

			if (FL_counter_pulses) {
				FL_counter_pulses = 0;
				counter_pulses++;
				FL_start_rules_counter = 1;
			}
		} else {
			COIN_ACCEPTOR_OUT_LOW;
			FL_counter_pulses = 1;
		}
	} else {
		COIN_ACCEPTOR_OUT_LOW;
		if (FL_protection) {
			FL_protection = 0;
			addAttack();
		}
	}

}

void addAttack(void) {
	for (int i = 0; i < buffer_size; i++) {
		if (commandBuffer[i] == 0) {
			commandBuffer[i] = com_attack;
			i = buffer_size;
		}
	}
}

void creditsBillAcceptorQuizomat(void) {

	if (PIN_PROTECTION_IN) {
		FL_protection = 1;
		if (!(PIN_BILL_ACCEPTOR_IN)) {
			BILL_ACCEPTOR_OUT_HIGH;

			if (FL_counter_pulses) {
				FL_counter_pulses = 0;
				counter_pulses++;
				FL_start_rules_counter = 1;
			}
		} else {
			BILL_ACCEPTOR_OUT_LOW;
			FL_counter_pulses = 1;
		}
	} else {
		BILL_ACCEPTOR_OUT_LOW;
		if (FL_protection) {
			FL_protection = 0;
			addAttack();
		}
	}

}

void checkQuizPayout(void) {
	if (receive == 13) {

		receive = 0;
	}
	if (receive == 12) {
		receive = 0;
	}

}

void sendStart(void) {
	if (receive == com_round) {
		receive = 0;

		START_OUT_HIGH;
		START_OUT_3_HIGH;
		for (uint8_t obr = 0; obr < 250; obr++) {
			creditsCoinAcceptorQuizomat();
			creditsBillAcceptorQuizomat();
			_delay_ms(1);
		}
		START_OUT_LOW;
		START_OUT_3_LOW;
	}
}

void sendKeySwitch(void) {
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

