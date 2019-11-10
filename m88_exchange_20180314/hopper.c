//DOUBLE
#include <avr/io.h>
#include <util/delay.h>

#include "config.h"

uint8_t h1_pay(void){
	uint32_t time = 0;
	//while(!H1C_DOWN);
	if(bit_is_clear(PIND, PD6)){
		while(bit_is_clear(PIND, PD6));
		_delay_ms(50);
	}
	h1_on();
	while(bit_is_set(PIND, PD6)){
		if(time > 10000000){
			h1_off();
			// time out
			//lcd_clrscr();
			//lcd_puts("timeout");
			return 1;
			break;
		}
		time ++;
	}
	h1_off();
	//	LD BLINK
	ld_blink();
	//	METER PULS
	meter_puls();
	_delay_ms(250);
	return 0;
}
uint8_t h2_pay(void){
	uint32_t time = 0;
	//while(!H2C_DOWN);
	if(bit_is_clear(PIND,PD3)){
		while(bit_is_clear(PIND,PD3));
		_delay_ms(50);
	}
	h2_on();
	while(bit_is_set(PIND, PD3)){
		if(time > 10000000){
			h2_off();
			// time out
			//lcd_clrscr();
			//lcd_puts("timeout");
			return 1;
			break;
		}
		time ++;
	}

	h2_off();
	_delay_ms(250);
	return 0;
}
