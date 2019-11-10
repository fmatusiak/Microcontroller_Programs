/*
 * IO_Button.c
 *
 *  Created on: 5 lip 2017
 *      Author: dell
 */

#include "IO_Button.h"

uint8_t checkPin(uint16_t pinIn) {
	if (!(pinIn)) {
		return true;
	} else {
		return false;
	}
}


void Check_IO (uint16_t pinIn,char *text)
{
	if (checkPin(pinIn)) {
		_delay_ms(2);
		if (checkPin(pinIn)) {
			FL_KEY_SWITCH = 1;
			while (FL_KEY_SWITCH) {
				Write_LCD_String(text, 4);

				if (checkPin(pinIn) == false) {
					_delay_ms(1);
					if (checkPin(pinIn) == false) {
						FL_KEY_SWITCH = 0;
					}
				}
			}
		}
	}
}


void Check_Button_Machine(void) {
	Write_LCD_String("     IO BUTTON      ", 3);
	Write_LCD_String("                    ", 4);
	delayS(1);
	Check_IO (PIN_BUTTON_1_IN,"  IO BUTTON 1 ERROR ");
	Check_IO (PIN_BUTTON_2_IN,"  IO BUTTON 2 ERROR ");
	Check_IO (PIN_BUTTON_3_IN,"  IO BUTTON 3 ERROR ");
	Check_IO (PIN_KEY_SWITCH_ADMIN_IN,"   IO KEY 1 ERROR   ");
	Check_IO (PIN_KEY_SWITCH_SERWIS_IN,"   IO KEY 2 ERROR   ");
	Write_LCD_String("    IO BUTTON OK    ", 4);
	delayS(1);
}



