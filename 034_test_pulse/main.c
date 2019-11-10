#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

// oscyloscope view

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51


volatile uint8_t start = 0, bit = 1, pozycja = 0, liczba = 0, bilet = 5,
		parzysty = 0, i = 0;
volatile int e, f, g, h, j = 0, pomoc = 0, banknot = 0, l = 0,
		pomocna = 0, punkty = 0;

volatile uint8_t a,b,c,d;

volatile uint16_t time_out = 2, tmp_time = 0, FL_time = 0, FL_timeout = 0;




volatile int poszlo = 1;

int main(void) {
	DDR_IN6_IN;
	IN6_IN_VCC;

	DDR_puls;
	PORT_puls_1;


	while (1) {
		if (!(PIN_IN6_IN))
		{
			_delay_ms(100);
			PORT_puls_0;
			_delay_ms(100);
			PORT_puls_1;
			_delay_ms(100);
		}

	}
}

