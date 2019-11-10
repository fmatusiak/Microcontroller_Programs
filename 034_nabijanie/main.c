#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/eeprom.h"
#include "main.h"

volatile uint8_t PASS_CORR = 0, FL_PIN2 = 0, Money = 0, FL_RUN = 1, FL_PIN3 = 0,
		FL_PIN4 = 0, FL_PIN5 = 0, FL_CORR = 1;

void give_money(void);

int main(void) {

	DDR_IN_1;
	DDR_IN_2;
	DDR_IN_3;
	DDR_IN_4;
	DDR_IN_5;
	DDR_OUT_6;
	DDR_OUT_1;
	DDR_OUT_TX;

	IN_1_VCC;
	IN_2_VCC;
	IN_3_VCC;
	IN_4_VCC;
	IN_5_VCC;

	PORT_OUT_1_0;
	PORT_OUT_6_0;
	PORT_OUT_TX_0;

	while (1) {
		give_money();
	}
}

void give_money(void) {
	PORT_OUT_6_1;
	PORT_OUT_1_1;
	PORT_OUT_TX_1;
	_delay_ms(50);
	PORT_OUT_1_0;
	PORT_OUT_6_0;
	PORT_OUT_TX_0;
	_delay_ms(50);
}
