/*
 * IO_Board.c
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#include "IO_Combo.h"

void Check_IO_Combo(void) {
	uint8_t datarecive[20] = { 0 };

	Write_LCD_String_FLASH(PSTR("      IO COMBO      "), 3);
	Write_LCD_String_FLASH(PSTR("                    "), 4);
	_delay_ms(1000);

	ccTalk_send(IO_COMBO, 0, 242, 0);
	if (ccTalk_recive_no_timeout(datarecive, IO_COMBO)) {

		if (((*(datarecive + 4)) == IOCOMBOID_NUMBER_)
				&& ((*(datarecive + 5)) == IOCOMBOID_NUMBER_)
				&& ((*(datarecive + 6)) == IOCOMBOID_NUMBER_)) {
			Write_LCD_String_FLASH(PSTR("    IO COMBO OK"), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String_FLASH(PSTR("   IO COMBO FAIL   "), 4);
			while (1) {
				Write_LCD_String_FLASH(PSTR("      IO COMBO      "), 3);
				Write_LCD_String_FLASH(PSTR("   IO COMBO FAIL   "), 4);
				_delay_ms(1500);
				Write_LCD_String_FLASH(PSTR("                   "), 3);
				Write_LCD_String_FLASH(PSTR("  "), 3);
				convert_m(*(datarecive + 4));
				LCD_WriteText_FLASH(PSTR(" : "));
				convert_m(*(datarecive + 5));
				LCD_WriteText_FLASH(PSTR(" : "));
				convert_m(*(datarecive + 6));
				LCD_WriteText_FLASH(PSTR(" : "));
				_delay_ms(1500);
			}
		}

	} else {
		Write_LCD_String_FLASH(PSTR("   IO COMBO ERROR   "), 4);
		while (1) {
		}
	}

}

void IO_Combo_Clear_Escrow(void) {
	ccTalk_send(IO_COMBO, 1, 70, (uint8_t[] ) { 1 });
	_delay_ms(50);
	ccTalk_send(IO_COMBO, 0, 71, (uint8_t[] ) { 0 });
	_delay_ms(50);
}

void IO_Combo_Claer_Acceptor(void) {

	if ((FL_Adminh == 0) && (FL_Serwish == 0) && (FL_Blocked == 0)) {
		ccTalk_send(IO_COMBO, 1, 71, (uint8_t[] ) { 0 });
		_delay_ms(50);
	}

}
