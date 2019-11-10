#include "tetris.h"
#include "main.h"

void tetris() {
	creditsCoinAcceptorTetris();
	creditsBillAcceptorTetris();
	sendHearts();
}

void creditsCoinAcceptorTetris() {
	if (PROT_ON) {
		if (PIN_PROTECTION_IN) {
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

			if (fl_coin_prot_impuls_tetris) {
				for (int i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = com_attack;
						i = buffer_size;
					}
				}
				fl_coin_prot_impuls_tetris = 0;
			}
		} else {
			_delay_ms(2);
			if (!(PIN_PROTECTION_IN)) {
				fl_coin_prot_impuls_tetris = 1;
			}
		}
	} else {
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
}

void creditsBillAcceptorTetris() {
	if (PROT_ON) {
		if (PIN_PROTECTION_IN) {
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

			if (fl_bill_prot_impuls_tetris) {
				for (int i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = com_attack;
						i = buffer_size;
					}
				}
				fl_bill_prot_impuls_tetris = 0;
			}
		} else {
			_delay_ms(2);
			if (!(PIN_PROTECTION_IN)) {
				fl_bill_prot_impuls_tetris = 1;
			}
		}
	} else {
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
}


void sendHearts() {
	if (heart) {
		if (sendCommand(com_send_hearts)) {
			heart = heart - 5;
		}
	}
}

