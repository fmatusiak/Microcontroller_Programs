#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "main.h"

volatile uint8_t INHIBIT = 1;

volatile uint8_t Money_In_Automat = 0, BillEvent = 0;
volatile uint8_t bill_5 = 0, bill_10 = 0, bill_20 = 0, bill_50 = 0,
		bill_100 = 0, bill_200 = 0;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

int main(void) {

	DDR_PULS_LED;

	PORT_PULS_LED_1;

	for (uint8_t i = 0; i < 30; i++) {
		for (uint8_t j = 0; j < 30; j++) {
			_delay_ms(100);
		}
	}
	PORT_PULS_LED_0;

	for(uint8_t i = 0 ; i < 10 ;i++)
	{
		_delay_ms(100);
	}

	PORT_PULS_LED_1;
}

// FUNCTIONS

