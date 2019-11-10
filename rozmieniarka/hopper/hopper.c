#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "hopper.h"
#include "../init/init.h"
#include "../operator/operator.h"
#include "../meters/meters.h"
#include "../bnc/bnc.h"


void power_on(void){
	PORTD |= _BV(H_POW);
	PORTB |= _BV(H_IN3);
}
void power_off(void){
	PORTD &= ~_BV(H_POW);
	PORTB &= ~_BV(H_IN3);
}
void pay(int credits){
	coins_to_pay = credits / COIN_VAL;

	bnc_turn_off();

	for(int i = 0; i < coins_to_pay; i++){
		meter_in();
	}

	power_on();
	timer0_reboot();

	while(coins_to_pay > 0){
		if(bit_is_clear(PIND, H_SEN)){
			timer0_reboot();
			while(bit_is_clear(PIND, H_SEN));
			coins_to_pay--;
			meter_out();
		}else{
			// Check timer
			if(tot_overflow >= HOPPER_TIME){
				//	Hopper Empty, turn it off, break program
				power_off();
				while(1);
			}
		}
	}
	//	Payed, turn hopper off, turn inhibit on
	power_off();
	bnc_turn_on();
}

void dump_on(void){
	bnc_turn_off();
	power_on();
	while( bit_is_set(PIND, SW) && (!(PIN_SW2_IN)) ){
		if(bit_is_clear(PIND, H_SEN)){
			meter_out();
			while(bit_is_clear(PIND, H_SEN));

		}
		//if(bit_is_clear(PIND, SW)) dump_off();
	}
	while(bit_is_clear(PIND, SW));
	dump_off();
}

void dump_off(void){
	power_off();
	_delay_ms(1000);
	bnc_turn_on();
}

void timer0_init(void){
	TCCR0 |= _BV(CS02) | _BV(CS00);	  // set up timer with prescaler = 1024
	TCNT0 = 0;  // initialize counter
	TIMSK |= (1 << TOIE0);  // enable overflow interrupt
	sei();	// enable global interrupts
	tot_overflow = 0;	// initialize overflow counter variabl
}

void timer0_reboot(void){
	TCNT0 = 0;
	tot_overflow = 0;
}

ISR(TIMER0_OVF_vect){
    tot_overflow++;
}
