#include <avr/io.h>
#include <util/delay.h>

#include "bnc.h"
#include "../init/init.h"
#include "../hopper/hopper.h"
#include "../meters/meters.h"

void bnc_check(void){
	 a = bit_is_clear(PINB, VEND1);
	 b = bit_is_clear(PINC, VEND2);
	 c = bit_is_clear(PINC, VEND3);
	 d = bit_is_clear(PINC, VEND4);

	if(a || b || c || d){
		_delay_ms(EMP_DETECTION_TIME);
		 a1 = bit_is_clear(PINB, VEND1);
		 b1 = bit_is_clear(PINC, VEND2);
		 c1 = bit_is_clear(PINC, VEND3);
		 d1 = bit_is_clear(PINC, VEND4);
		if(bnc_emp(a, b, c, d, a1, b1, c1, d1)){
		// emp detected
			bnc_turn_off();
			power_off();
		}
		_delay_ms(COIN_IMPULSE_TIME);
		 a1 = bit_is_clear(PINB, VEND1);
		 b1 = bit_is_clear(PINC, VEND2);
		 c1 = bit_is_clear(PINC, VEND3);
		 d1 = bit_is_clear(PINC, VEND4);
		if(bnc_emp_pulse_time(a, b, c, d, a1, b1, c1, d1)){
		// emp detected
			bnc_turn_off();
			power_off();
			while(1)
			{

			}

		}else{
			 credits = 0;
			if(a){
				credits = 10;
				pay(credits);
			}else if(b){
				credits = 20;
				pay(credits);
			}else if(c){
				credits = 50;
				pay(credits);
			}else if(d){
				credits = 100;
				pay(credits);
			}
		}
	}
}
int bnc_emp(int a, int b, int c, int d, int a1,int b1,int c1,int d1){
	if((a &&( b||c||d||b1||c1||d1))||(b &&( a||c||d||a1||c1||d1))||(c &&(a||b||d||a1||b1||d1))||(d &&(a||b||c||a1||b1||c1))){
		// EMP detected
		return 1;
	}else{
		return 0;
	}
}

int bnc_emp_pulse_time(int a, int b, int c, int d, int a1,int b1,int c1,int d1){
	if((a &&(a1|| b||c||d||b1||c1||d1))||(b &&(b1 || a||c||d||a1||c1||d1))||(c &&(c1||a||b||d||a1||b1||d1))||(d &&(d1||a||b||c||a1||b1||c1))){
		// EMP detected
		return 1;
	}else{
		return 0;
	}
}
void bnc_turn_on(void){
	//Set INHIBIT ON
	PORTC &= ~_BV(INH);
}
void bnc_turn_off(void){
	//	Set INHIBIT OFF
	PORTC |= _BV(INH);
}
