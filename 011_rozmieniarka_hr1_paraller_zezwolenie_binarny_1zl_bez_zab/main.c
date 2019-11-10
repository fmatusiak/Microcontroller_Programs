#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"

#define F_CPU 8000000UL // zegar w Hz

volatile uint16_t kasa,i,timnes = 0;
volatile uint8_t money,FL_hopper = 1,FLwhile = 1;
volatile uint8_t BAN10 = 10,BAN20=20,BAN50=50,BAN100=100;



int main(void) {

	DDR_pierwszy_we;
	DDR_drugi_we;
	DDR_trzeci_we;
	DDR_czwarty_we;
	DDR_piaty_we;

	DDR_hopper_we;
	DDR_zezwolenie_out;

	pierwszy_we_VCC;
	drugi_we_VCC;
	trzeci_we_VCC;
	czwarty_we_VCC;
	piaty_we_VCC;

	hopper_we_VCC;

	DDR_syrena_wy;
	PORT_syrena_wy_0;
	DDR_hopper_out;
	PORT_hopper_out_0;
	DDR_zezwolenie_out;
	PORT_zezwolenie_out_1;
	DDR_awaria_out;
	PORT_awaria_out_0;
	_delay_ms(1000);
	PORT_hopper_out_0;
	while (1) {

// ==========================================================================================
// =================================== drugi ================================================

			if (!(PIN_pierwszy_we)) {
				_delay_ms(2);
				if (!(PIN_pierwszy_we)) {
						nabij_kase(BAN10);
				}
			}

			if (!(PIN_drugi_we)) {
				_delay_ms(2);

				if (!(PIN_drugi_we)) {
						nabij_kase(BAN20);
				}
			}
			if (!(PIN_trzeci_we)) {
				_delay_ms(2);
				if (!(PIN_trzeci_we)) {
						nabij_kase(BAN50);
				}
			}
			if (!(PIN_czwarty_we)) {
				_delay_ms(2);
				if (!(PIN_czwarty_we)) {
						nabij_kase(BAN100);
				}
			}

		}
// ==========================================================================================
// ================================= trzeci =================================================


}

	void nabij_kase(uint8_t ile) {
		money = 0;
		PORT_zezwolenie_out_0;
		PORT_hopper_out_1;
		PORT_syrena_wy_1;		FLwhile = 1;
		while (FLwhile) {
			_delay_ms(1);
			timnes ++;
			if((!(PIN_hopper_we)) && (FL_hopper)){
				_delay_ms(2);
				if((!(PIN_hopper_we)) && (FL_hopper))
				{
					FL_hopper = 0;
					money++;
					timnes = 0;
				}
			}

			if ((PIN_hopper_we) && (FL_hopper == 0))
			{
				_delay_ms(2);
				if ((PIN_hopper_we) && (FL_hopper == 0))
				{
					FL_hopper  = 1;
				}
			}
			if (timnes >=8000)
			{
				while (1)
				{
					PORT_hopper_out_0;
					PORT_zezwolenie_out_0;
				}
			}

		if (money == ile)
		{
			FLwhile = 0;
		}
		}

		PORT_syrena_wy_0;
	PORT_zezwolenie_out_1;
	PORT_hopper_out_0;
	}


