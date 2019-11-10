#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"

int main(void) {
	DDR_wyjscie;
	PORT_wyjscie_0;

	DDR_wyjscie2;
	PORT_wyjscie2_0;

	DDR_wejscie;
	wejscie_VCC;
	PORT_wyjscie2_0;


for (int i = 0; i < 0; i++) {
		_delay_ms(10000);
	}
	PORT_wyjscie_1;
	PORT_wyjscie2_1;

	while (1) {/*
		while(PIN_wejscie){
			PORT_wyjscie_0;
			PORT_wyjscie2_0;

		}
		PORT_wyjscie_1;
		PORT_wyjscie2_1;
*/


	}

}
