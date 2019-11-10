//DOUBLE

#include <avr/eeprom.h>
#include "config.h"

uint32_t read(uint32_t adr){
	return eeprom_read_dword((uint32_t *) adr);
}
void write(uint8_t target, uint32_t value){
	//uint32_t old;
	//eeprom_write_dword(0, 1000);
	switch(target){
		//counter in
		case 1:
			eeprom_write_dword((uint32_t *)0x0000, value);
			break;
		//counter out
		case 2:
			eeprom_write_dword((uint32_t *)0x0020, value);
			break;
		//hopper
		case 3:
			eeprom_write_dword((uint32_t *)0x0040, value);
			break;
		default:
			break;
	}
}
uint32_t read_in(void){
	return read(0x0000);
}
uint32_t read_out1(void){
	return read(0x0020);
}
uint32_t read_out2(void){
	return read(0x0040);
}
void set_in(uint8_t value){
	uint32_t old = read_in();
	old = old + value;
	write(1, old);
}
void set_out1(uint8_t value){
	uint32_t old = read_out1();
	old	= old + value;
	write(2, old);
}
void set_out2(uint8_t value){
	uint32_t old = read_out2();
	old = old + value;
	write(3, old);
}
