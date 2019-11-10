#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

// software

// =======================

#define F_CPU 8000000UL // zegar w Hz

volatile uint8_t money = 0, FL_money = 0;

int main(void) {

	DDR_jedynka_wy;
	DDR_czworka;

	czworka_VCC;
	PORT_jedynka_wy_1;

	while (1) {
// softwarowy uart

		if ((!(PIN_czworka)) && FL_money) {
			_delay_ms(2);
			if (!(PIN_czworka)) {
				FL_money = 0;
				money += 3;
			}
		}

		if ((PIN_czworka) && (FL_money == 0))
		{
			_delay_ms(2);
			if (PIN_czworka)
			{
				FL_money = 1;
			}

		}
		if(money)
		{
			PORT_jedynka_wy_0;
			_delay_ms(100);
			PORT_jedynka_wy_1;
			_delay_ms(400);
			money--;
		}


	}
}

