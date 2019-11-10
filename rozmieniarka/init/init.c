#include <avr/io.h>
#include <util/delay.h>

#include "init.h"
#include "../hopper/hopper.h"

void init(void){
	set_ports();
	_delay_ms(3000);	// delay if operator sw is pressed

	if(check_ports()){
		while(1);		// We got problem, set infinite loop
	}

	timer0_init();
}
int check_ports(void){
	/*	Check if inputs are ok then end function, else stop program	*/
	if(bit_is_clear(PINB, VEND1)){
		//	VEND1 error
		return 1;
	}else if(bit_is_clear(PINC, VEND2)){
		//	VEND2 error
		return 1;
	}else if(bit_is_clear(PINC, VEND3)){
		//	VEND3 error
		return 1;
	}else if(bit_is_clear(PINC, VEND4)){
		//	VEND4 error
		return 1;
	}else if(bit_is_clear(PIND, H_SEN)){
		//	Hopper sensor error
		return 1;
	}else if(bit_is_clear(PIND, SW)){
		//	SWITCH error
		return 1;
	}else{
		// All right
		return 0;
	}
}
void set_ports(void){
	// I/O definitions
	DDRB |= _BV(H_IN3) | _BV(METER_IN);
	PORTB &= ~(_BV(H_IN3) | _BV(METER_IN));
	PORTB |= _BV(VEND1);

	DDRC |= _BV(INH) ;
	PORTC |= _BV(INH);
	PORTC |= _BV(VEND2) | _BV(VEND3) | _BV(VEND4);

	DDRD |= _BV(H_POW) | _BV(METER_OUT);
	PORTD &= ~(_BV(H_POW) | _BV(METER_OUT));
	PORTD |= _BV(H_SEN) | _BV(SW);
}


