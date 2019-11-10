#include "tetris.h"
#include "main.h"

void tetris() {
	creditsCoinAcceptorTetris();
	creditsBillAcceptorTetris();
	sendHearts();
	sendKeySwitch();
}

void creditsCoinAcceptorTetris() {

	if ((!fl_coin_impuls_tetris) && (!(PIN_COIN_ACCEPTOR_IN))) {
		_delay_ms(2);
		if ((!fl_coin_impuls_tetris) && (!(PIN_COIN_ACCEPTOR_IN))) {
			fl_coin_impuls_tetris = 1;
		}
	}
	if ((fl_coin_impuls_tetris) && (PIN_COIN_ACCEPTOR_IN)) {
		heart += 5;
		fl_coin_impuls_tetris = 0;
	}

}

void creditsBillAcceptorTetris() {
	if ((!fl_bill_impuls_tetris) && (!(PIN_BILL_ACCEPTOR_IN))) {
		_delay_ms(2);
		if ((!fl_bill_impuls_tetris) && (!(PIN_BILL_ACCEPTOR_IN))) {
			fl_bill_impuls_tetris = 1;
		}
	}
	if ((fl_bill_impuls_tetris) && (PIN_BILL_ACCEPTOR_IN)) {
		heart += 10;
		fl_bill_impuls_tetris = 0;
	}

}

void sendHearts() {
	if (heart) {

		for (int i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = com_send_hearts;
				i = buffer_size;
			}
		}
		heart = heart - 5;

		if (FL_heart == 0) {
			for (int i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_quiz_start_rules;
					i = buffer_size;
				}
			}
			FL_heart = 1;
		}

	}

	if (heart == 0) {
		FL_heart = 0;
	}

}

