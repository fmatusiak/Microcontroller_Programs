#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/eeprom.h"
#include "main.h"

volatile uint8_t PASS_CORR = 0, FL_PIN2 = 0, Money = 0, FL_RUN = 1, FL_PIN3 = 0,
		FL_PIN4 = 0, FL_PIN5 = 0, FL_CORR = 1;

void check_pass(void);
void chcek_money(void);
void give_money(void);

int main(void) {

	DDR_IN_1;
	DDR_IN_2;
	DDR_IN_3;
	DDR_IN_4;
	DDR_IN_5;
	DDR_OUT_6;
	DDR_OUT_1;

	IN_1_VCC;
	IN_2_VCC;
	IN_3_VCC;
	IN_4_VCC;
	IN_5_VCC;

	PORT_OUT_1_0;
	PORT_OUT_6_0;

	while (1) {

		check_pass();

		if (PASS_CORR) {
			chcek_money();
			give_money();
		}
	}
}

void check_pass(void) {
	if (FL_RUN) {

		if ((!(PIN_IN_2)) && (FL_PIN2)) {
			_delay_ms(1);
			if ((!(PIN_IN_2)) && (FL_PIN2)) {
				FL_RUN = 0;
				FL_PIN2 = 0;
			}
		}

		if ((PIN_IN_2) && (FL_PIN2 == 0)) {
			_delay_ms(1);
			if ((PIN_IN_2) && (FL_PIN2 == 0)) {
				FL_PIN2 = 1;
			}
		}

		if ((!(PIN_IN_3)) && (FL_PIN3)) {
			_delay_ms(1);
			if ((!(PIN_IN_3)) && (FL_PIN3)) {
				FL_RUN = 0;
				FL_PIN3 = 0;
			}
		}

		if ((PIN_IN_3) && (FL_PIN3 == 0)) {
			_delay_ms(1);
			if ((PIN_IN_3) && (FL_PIN3 == 0)) {
				FL_PIN3 = 1;
			}
		}

		if ((!(PIN_IN_4)) && (FL_PIN4)) {
			_delay_ms(1);
			if ((!(PIN_IN_4)) && (FL_PIN4)) {
				FL_RUN = 0;
				FL_PIN4 = 0;
			}
		}

		if ((PIN_IN_4) && (FL_PIN4 == 0)) {
			_delay_ms(1);
			if ((PIN_IN_4) && (FL_PIN4 == 0)) {
				FL_PIN4 = 1;
			}
		}

		if ((!(PIN_IN_5)) && (FL_PIN5)) {
			_delay_ms(1);
			if ((!(PIN_IN_5)) && (FL_PIN5)) {
				FL_CORR++;
				FL_PIN5 = 0;
			}
		}

		if ((PIN_IN_5) && (FL_PIN5 == 0)) {
			_delay_ms(1);
			if ((PIN_IN_5) && (FL_PIN5 == 0)) {
				FL_PIN5 = 1;
			}
		}

		if (FL_CORR == 5) {
			FL_RUN = 0;
			PASS_CORR = 1;
			PORT_OUT_6_1;
		}
	}
}

void chcek_money(void) {
	if (!(PIN_IN_1)) {

		if ((!(PIN_IN_2)) && (FL_PIN2)) {
			_delay_ms(1);
			if ((!(PIN_IN_2)) && (FL_PIN2)) {

				FL_PIN2 = 0;
				Money++;
			}
		}

		if ((PIN_IN_2) && (FL_PIN2 == 0)) {
			FL_PIN2 = 1;
		}
	}
}

void give_money(void) {
	if (Money) {
		PORT_OUT_1_1;
		_delay_ms(100);
		PORT_OUT_1_0;
		_delay_ms(300);
		Money--;
	}
}
