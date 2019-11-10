#include "tetris.h"
#include "main.h"



void tetris() {

	if ((!(PIN_PILOT_KEY_IN)) && FL_kom_pilot == 0) {
		iterGND++;
		iter_kom = 120;

	}

	else if (iterGND >= 400) {
		if (PIN_PILOT_KEY_IN) {
			_delay_us(100);
			if (PIN_PILOT_KEY_IN) {
				iterGND = 0;
				FL_kom_pilot = 1;
				sendCommand(6);
			}
		}
	}
	if (FL_kom_pilot) {
		if (!(PIN_PILOT_KEY_IN)) {

			iterGND++;
		}

		if (PIN_PILOT_KEY_IN) {

			iterVCC++;
		}

		if (iterGND >= 19)
		{
			iterGND = 0;
			iterVCC = 0;
			pilot_date = pilot_date + (iter_kom);
			iter_kom--;
		}



		else if(iterVCC >= 19)
		{
			iterVCC = 0;
			iterGND = 0;
			pilot_date = pilot_date + (iter_kom);
			iter_kom--;
		}


		if (iter_kom == 0) {
			iter_kom = 120;
			//FL_kom_pilot = 0;



			counter_pulses = pilot_date;
			sendTime();
		}


}
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
		if (PROTECTION_IN) {
			if ((!fl_bill_impuls_tetris) && (!(PIN_BILL_ACCEPTOR_IN))) {
				_delay_ms(2);
				if ((!fl_bill_impuls_tetris) && (!(PIN_BILL_ACCEPTOR_IN))) {
					fl_bill_impuls_tetris = 1;
				}
			}
			if ((fl_bill_impuls_tetris) && (PIN_BILL_ACCEPTOR_IN)) {
				heart += 5;
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

