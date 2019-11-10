#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "main.h"


#define F_CPU 8000000UL // zegar w Hz

volatile uint16_t kasa,i,timnes = 0;
volatile uint8_t money,FL_hopper = 1,FLwhile = 1;
volatile uint8_t BAN10 = 10,BAN20=20,BAN50=50,BAN100=100;

void nabij_kase(uint8_t ile);
int main(void) {

	DDR_LINE1_IN;
	DDR_LINE2_IN;
	DDR_LINE3_IN;
	DDR_LINE4_IN;
	DDR_COIN_IN;
	DDR_SERVICE_IN;


	LINE1_IN_VCC;
	LINE2_IN_VCC;
	LINE3_IN_VCC;
	LINE4_IN_VCC;
	SERVICE_IN_VCC;
	COIN_IN_VCC;

	DDR_HOPPER_MOTOR_OUT;
	DDR_INHIBIT_OUT_OUT;

	PORT_INHIBIT_OUT_1;
	PORT_HOPPER_MOTOR_OUT_0;


	_delay_ms(500);


	while (1) {
// ==========================================================================================
// =================================== drugi ================================================

		if (!(PIN_SERVICE_IN))
		{
			while(!(PIN_SERVICE_IN))
			{
				PORT_HOPPER_MOTOR_OUT_1;
			}
			PORT_HOPPER_MOTOR_OUT_0;
		}


			if (!(PIN_LINE1_IN)) {
				_delay_ms(2);
				if (!(PIN_LINE1_IN)) {
						nabij_kase(BAN10);
				}
			}

			if (!(PIN_LINE2_IN)) {
				_delay_ms(2);

				if (!(PIN_LINE2_IN)) {
						nabij_kase(BAN20);
				}
			}
			if (!(PIN_LINE3_IN)) {
				_delay_ms(2);
				if (!(PIN_LINE3_IN)) {
						nabij_kase(BAN50);
				}
			}
			if (!(PIN_LINE4_IN)) {
				_delay_ms(2);
				if (!(PIN_LINE4_IN)) {
						nabij_kase(BAN100);
				}
			}

		}
// ==========================================================================================
// ================================= trzeci =================================================


}




void nabij_kase(uint8_t ile) {
	money = 0;
	PORT_INHIBIT_OUT_0;
	PORT_HOPPER_MOTOR_OUT_1;

	FLwhile = 1;
	while (FLwhile) {
		_delay_ms(1);
		timnes ++;
		if((!(PIN_COIN_IN)) && (FL_hopper)){
			_delay_ms(2);
			if((!(PIN_COIN_IN)) && (FL_hopper))
			{
				FL_hopper = 0;
				money++;
				timnes = 0;
			}
		}

		if ((PIN_COIN_IN) && (FL_hopper == 0))
		{
			_delay_ms(2);
			if ((PIN_COIN_IN) && (FL_hopper == 0))
			{
				FL_hopper  = 1;
			}
		}
		if (timnes >=8000)
		{
			while (1)
			{
				PORT_HOPPER_MOTOR_OUT_0;
				PORT_INHIBIT_OUT_0;
			}
		}

	if (money == ile)
	{
		FLwhile = 0;
	}
	}

	PORT_INHIBIT_OUT_1;
	PORT_HOPPER_MOTOR_OUT_0;
}
