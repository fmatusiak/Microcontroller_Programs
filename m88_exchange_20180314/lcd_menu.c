#include "lcd_new.h"
#include <stdlib.h>
#include <util/delay.h>
#include "config.h"

void convert(uint32_t data){
	char str[32];
	lcd_puts(ultoa(data, str, 10));
}
void lcd_update(uint8_t x,uint8_t y ,uint32_t val){
	lcd_gotoxy(x, y);
	convert(val);
}
void lcd_display_menu(uint8_t screen, uint8_t data){

}

void lcd_error(){

}
void lcd_service(uint8_t type){

}
void service_menu(void){

}
