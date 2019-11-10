#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/eeprom.h"
#include "main.h"

volatile uint8_t tmp_led = 0, value_time = 0, tmp_value_time = 0,
		value_mod_time = 2;
uint8_t EEMEM stan_zapis = 0;
volatile uint8_t FL_Button = 0, FL_Door = 0, FL_Barman = 0, mod_time = 0,
		FL_led = 0, FL_led_cyk = 0, FL_Open = 0, FL_IN_Barman = 0;

volatile uint16_t Time = 64000, Time_tmp = 0, Time_light_UP = 0,
		Time_light_DOWN = 0;

void Run_CykCyk(void);
void Set_Light(void);
void Check_Barman(void);
void Check_Door(void);
void Increment_Time(void);
void Power_Reset(void);

int main(void) {

	DDR_DOOR_IN;
	DDR_BARMAN_IN;
	DDR_BUTTON_IN;
	DDR_LED_PLUS_OUT;
	DDR_PILOT_ON_OUT;
	DDR_PILOT_OFF_OUT;

	DOOR_IN_VCC;
	BARMAN_IN_VCC;
	BUTTON_IN_VCC;
	PORT_LED_PLUS_OUT_1;
	PORT_PILOT_OFF_OUT_0;
	PORT_PILOT_ON_OUT_0;
	//eeprom_write_byte(&stan_zapis, 1);
	value_time = eeprom_read_byte(&stan_zapis);

	Power_Reset();

	while (1) {
		Set_Light();
		Check_Door();
		Check_Barman();
		Increment_Time();
		if (FL_Door) {
			Run_CykCyk();

		}
	}

}

void Run_CykCyk() {
	Time_tmp++;
	if (Time_tmp == Time) {
		Time_tmp = 0;

		tmp_value_time++;
		if (tmp_value_time >= value_time) {
			tmp_value_time = 0;
			FL_Door = 0;
			FL_Barman = 0;
			Power_Reset();
		}
	}

}

void Power_Reset(void) {
	PORT_PILOT_OFF_OUT_1;
	_delay_ms(2000);
	PORT_PILOT_OFF_OUT_0;
	_delay_ms(100);
	PORT_PILOT_ON_OUT_1;
	_delay_ms(1000);
	PORT_PILOT_ON_OUT_0;
	_delay_ms(540);
	FL_Door = 0;

}

void Set_Light(void) {
	if (FL_led) {
		if (tmp_led <= ((value_time - 1) / 10)) {

			if (FL_led_cyk) {
				PORT_LED_PLUS_OUT_1;
				Time_light_DOWN++;
				if (Time_light_DOWN == 5000) {
					Time_light_DOWN = 0;
					FL_led_cyk = 0;
				}
			} else {
				PORT_LED_PLUS_OUT_0;
				Time_light_UP++;
				if (Time_light_UP == 5000) {
					Time_light_UP = 0;
					FL_led_cyk = 1;
					tmp_led++;
				}

			}

		} else {
			FL_led = 0;
			tmp_led = 0;
			Time_light_DOWN = 0;
			Time_light_UP = 0;
		}

	}

	else {
		PORT_LED_PLUS_OUT_0;
		Time_light_DOWN++;
		if (Time_light_DOWN == Time) {
			FL_led = 1;
			Time_light_DOWN = 0;
		}
	}

}

void Check_Barman(void) {
	if ((!(PIN_BARMAN_IN)) && FL_IN_Barman) {
		_delay_ms(2);
		if ((!(PIN_BARMAN_IN)) && FL_IN_Barman) {
			if (FL_Open == 0) {
				FL_Door = 0;
				FL_IN_Barman = 0;
			}
		}
	}

	if (((PIN_BARMAN_IN)) && (!(FL_IN_Barman))) {
		_delay_ms(1);
		if (((PIN_BARMAN_IN)) && (!(FL_IN_Barman))) {
			FL_IN_Barman = 1;
		}
	}
}

void Check_Door(void) {
	if ((!(PIN_DOOR_IN)) && FL_Open == 0) {
		_delay_ms(2);
		if (!(PIN_DOOR_IN)) {
			FL_Door = 1;
			FL_Open = 1;
		}
	}
	if ((PIN_DOOR_IN) && FL_Open == 1) {
		_delay_ms(2);
		if ((PIN_DOOR_IN) && FL_Open == 1) {
			FL_Open = 0;
		}
	}
}

void Increment_Time(void) {
	if ((!(PIN_BUTTON_IN)) && (PIN_BARMAN_IN) && FL_Button == 0) {
		_delay_ms(1);
		if ((!(PIN_BUTTON_IN)) && (PIN_BARMAN_IN)) {
			FL_Button = 1;
			value_time += 10;
		}
	}
	if ((!(PIN_BUTTON_IN)) && (!(PIN_BARMAN_IN)) && FL_Button == 0) {
		_delay_ms(1);
		if ((!(PIN_BUTTON_IN)) && (!(PIN_BARMAN_IN))) {
			FL_Button = 1;
			value_time = 1;
			eeprom_write_byte(&stan_zapis, value_time);
		}
	}
	if ((PIN_BUTTON_IN) && (FL_Button)) {
		_delay_ms(1);
		if ((PIN_BUTTON_IN) && (FL_Button)) {
			FL_Button = 0;
			eeprom_write_byte(&stan_zapis, value_time);
		}
	}
}

