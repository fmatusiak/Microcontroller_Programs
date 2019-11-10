//DOUBLE

#include <util/delay.h>
#include <string.h>

#include "cctalk.h"
#include "uart.h"
#include "config.h"

void cc_put(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,
		uint8_t *data) {
	uart_putc(from);
	uart_putc(dataCount);
	uart_putc(to);
	uart_putc(command);
	uint8_t checkSum = from + to + command + dataCount;
	for (int i = 0; i < dataCount; i++) {
		uart_putc(data[i]);
		_delay_ms(1);
		checkSum += data[i];
	}
	checkSum %= 256;
	checkSum = 256 - checkSum;
	uart_putc(checkSum);
}
void bill_take(void){
	cc_put(40, 1, 1, 154, (uint8_t[]) {1});
}
void bill_distable(void){
	cc_put(40, 2, 1, 231, (uint8_t[]) {0, 0});
}
void bill_enable(void){
	cc_put(40, 2, 1, 231, (uint8_t[]) {255, 255});
}
void bill_init(){
	_delay_ms(2000);
	cc_put(40, 0, 1, 254, 0);
	_delay_ms(200);
	cc_put(40, 2, 1, 231, (uint8_t[]) {255, 255});
	_delay_ms(200);
	cc_put(40, 1, 1, 228, (uint8_t[]) {1});
	_delay_ms(200);
}
void bill_reject(void){
	cc_put(40, 1, 1, 154, (uint8_t[]) {0});
}
void bill_alive(){
	cc_put(40,0,1,159,0);
	_delay_ms(100);
	cc_put(2,0,1,229,0);
}
uint8_t checksum(uint8_t buffer[],uint8_t byte_count){
	uint16_t checksum = 0;

	for(uint8_t e = 0; e< (byte_count -1); e++){
		checksum += buffer[e];
	}
	checksum %= 256;
	checksum = 256 - checksum;
	if(checksum == buffer[byte_count -1]){
		return 1;
	}else{
		return 0;
	}
}
int analyze_data(uint8_t buffer[]){
	uint8_t kasa = 0;
	if(buffer[0] ==1){
		if(buffer[1] ==11){
			if(buffer[2] == 2){
					if(buffer[4] > 0){
						switch(buffer[5]){
							case 1:
								kasa = 5;
								break;
							case 2:
							break;
						}
					}
			}else if(buffer[2] == 40){

				if((buffer[5]==0)){
					if(buffer[6]==6){
						bill_init();
					}
				}

				if((buffer[5] > 0) & (buffer[6] == 1)){
					switch(buffer[5]){
					case 1:
						//lcd_puts(" 10S");
						kasa = 10;
						//bill_reject();
						//kasa = 0;
						break;
					case 2:
						//lcd_puts(" 20S");
						kasa = 20;
						//bill_reject();
						//kasa = 0;
						break;
					case 3:
						//lcd_puts(" 50S");
						//kasa = 50;
						bill_reject();
						kasa = 0;
						break;
					case 4:
						//lcd_puts("100S");
						//kasa = 100;
						bill_reject();
						kasa = 0;
						break;
					case 5:
						//lcd_puts("200S");
						//kasa = -1;
						bill_reject();
						kasa = 0;
						break;
					case 6:
						//lcd_puts(" 10N");
						kasa = 10;
						break;
					case 7:
						//lcd_puts(" 20N");
						kasa = 20;
						break;
					case 8:
						//lcd_puts(" 50N");
						//kasa = 50;
						bill_reject();
						kasa = 0;
						break;
					case 9:
						//lcd_puts("100N");
						//kasa = 100;
						bill_reject();
						kasa = 0;
						break;
					case 10:
						//lcd_puts("200N");
						//kasa = -1;
						bill_reject();
						kasa = 0;
						break;
					default:
						//lcd_puts("default switch");
						kasa = -1;
						break;
					}
				}
			}
		}else if((buffer[5]== 0) & (buffer[6] == 4)){
			kasa = -2;
			//_delay_ms(2500);
			bill_init();
		}
	}else{

	}

	return kasa;
}

