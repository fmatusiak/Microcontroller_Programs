//	DOUBLE
#include <avr/io.h>
#include <util/delay.h>

#include "config.h"

void init_all(){
	BT1_INIT;
	BT2_INIT;
	BTO_INIT;
	//HP_INIT;
	H1M_INIT;
	H1C_INIT;
	H1E_INIT;
	H2M_INIT;
	H2C_INIT;
	H2E_INIT;
	LD_INIT;
	METER_INIT;
	METER_OFF;
	LD_OFF;
	//HP_OFF;
	H1M_OFF;
}
void h1_on(){
	//HP_ON;
	H1M_ON;
}
void h1_off(){
	//HP_OFF;
	H1M_OFF;
}
void h2_on(){
	//HP_ON;
	H2M_ON;
}
void h2_off(){
	//HP_OFF;
	H2M_OFF;
}
void meter_puls(){
	METER_ON;
	_delay_ms(100);
	METER_OFF;
	_delay_ms(100);
}
void ld_blink(){
	LD_ON;
	_delay_ms(100);
	LD_OFF;
	_delay_ms(100);
}
void ld_void(){
	while(1){
		LD_ON;
			_delay_ms(500);
			LD_OFF;
			_delay_ms(500);
	}
}
