#include <avr/io.h>
#include <util/delay.h>

#include "init/init.h"
#include "operator/operator.h"
#include "hopper/hopper.h"
#include "meters/meters.h"
#include "bnc/bnc.h"

int main(void){
	init();
	bnc_turn_on();
	DDR_SW2_IN;
	SW2_IN_VCC;

	while(1){
		bnc_check();
		if(!(PIN_SW2_IN))
		{
		operator_check();
		}
	}
	return 0;
}
