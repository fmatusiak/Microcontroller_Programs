#include <avr/io.h>


void timers_init(void){
	//Timer A clock set (CS02)(CS01)(CS00)		// 0,0,0 - no presc. : 101 - clk/1024
	TCCR0B = (1<<CS01) | (1<<CS00);
	//TCNT0 -counter value rgister {io}
	//OCR0A -compare value register

	// Enable timer interrupt
	TIMSK0=(1<<TOIE0);
}
void timer_start(void){
	//timer_stop();
	TCNT0 = 0;
	TCCR0B = (1<<CS01) | (1<<CS00);
}
void timer_stop(void){
	//TCCR0B = (0<<CS01) | (0<<CS00);
	TCCR0B &= ~(1<<CS01);
	TCCR0B &= ~(1<<CS00);

	TCNT0 = 0;
}
void timer_restart(void){
	timer_stop();

	timer_start();
}
