#include <avr/io.h>
#include <util/delay.h>

#include "meters.h"
#include "../init/init.h"

void meter_out(void){
	PORTD |= _BV(METER_OUT);
	_delay_ms(COUNTER_TIME);
	PORTD &= ~_BV(METER_OUT);
	//_delay_ms(COUNTER_TIME);
}
void meter_in(void){
	PORTB |= _BV(METER_IN);
	_delay_ms(COUNTER_TIME);
	PORTB &= ~_BV(METER_IN);
	_delay_ms(COUNTER_TIME);
}
