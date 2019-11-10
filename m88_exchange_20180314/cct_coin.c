#include <util/delay.h>

#include "cct_coin.h"
#include "uart.h"
#include "cctalk.h"

void coin_init(void){
	cc_put(2, 0, 1, 254, 0);
	_delay_ms(50);
	cc_put(2, 2, 1, 231, (uint8_t[]) {1, 0});
	_delay_ms(50);
	cc_put(2,0,1,230,0);
	_delay_ms(50);
	cc_put(2, 1, 1, 228, (uint8_t[]) {1});
	_delay_ms(50);
}
void coin_read(void){
	cc_put(2,0,1,229,0);
}
void coin_active(void){
	cc_put(2, 2, 1, 231, (uint8_t[]) {1, 0});
	_delay_ms(50);
	cc_put(2, 1, 1, 228, (uint8_t[]) {1});
	_delay_ms(50);
}
void coin_inactive(void){
	cc_put(2, 2, 1, 231, (uint8_t[]) {0, 0});
	_delay_ms(50);
	cc_put(2, 1, 1, 228, (uint8_t[]) {0});
	_delay_ms(50);
}
