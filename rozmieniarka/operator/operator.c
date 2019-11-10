#include <avr/io.h>
#include <util/delay.h>

#include "operator.h"
#include "../init/init.h"
#include "../hopper/hopper.h"

void operator_check(){
	if((bit_is_clear(PIND, SW))) {
		_delay_ms(1000);	// debounce
		while(bit_is_clear(PIND, SW));
		dump_on();
	}
}
