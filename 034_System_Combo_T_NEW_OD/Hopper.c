/*
 * Hopper.c
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#include "Hopper.h"

void Check_Hopper(void) {
	uint8_t datarecive[20] = {0};
	Write_LCD_String(PSTR("       HOPPER       "), 3);
	Write_LCD_String(PSTR("                    "), 4);
	_delay_ms(1000);

	ccTalk_send(HOPPER_5ZL,0, 242, 0);
	if (ccTalk_recive(datarecive,HOPPER_5ZL)) {

		if (((*(datarecive + 4)) == HOPPER5ID_NUMBER_1)
				&& ((*(datarecive + 5)) == HOPPER5ID_NUMBER_2)
				&& ((*(datarecive + 6)) == HOPPER5ID_NUMBER_3)) {
			Write_LCD_String(PSTR("    HOPPER 1 OK     "), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String(PSTR("   HOPPER 1 FAIL   "), 4);
			while (1) {
			}
		}
	} else {
		Write_LCD_String(PSTR("   HOPPER 1 ERROR   "), 4);
		while (1) {
		}
	}
	ccTalk_send(HOPPER_1ZL,0, 242, 0);
	if (ccTalk_recive(datarecive,HOPPER_1ZL)) {

		if (((*(datarecive + 4)) == HOPPER1ID_NUMBER_1)
				&& ((*(datarecive + 5)) == HOPPER1ID_NUMBER_2)
				&& ((*(datarecive + 6)) == HOPPER1ID_NUMBER_3)) {
			Write_LCD_String(PSTR("    HOPPER 2 OK     "), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String(PSTR("   HOPPER 2 FAIL   "), 4);
			while (1) {

			}
		}
	} else {
		Write_LCD_String(PSTR("   HOPPER 2 ERROR   "), 4);
		while (1) {
		}
	}
	ccTalk_send(HOPPER_50GR,0, 242, 0);
	if (ccTalk_recive(datarecive,HOPPER_50GR)) {

		if (((*(datarecive + 4)) == HOPPER50ID_NUMBER_1)
				&& ((*(datarecive + 5)) == HOPPER50ID_NUMBER_2)
				&& ((*(datarecive + 6)) == HOPPER50ID_NUMBER_3)) {
			Write_LCD_String(PSTR("    HOPPER 3 OK     "), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String(PSTR("   HOPPER 3 FAIL   "), 4);
			while (1) {

			}
		}
	} else {
		Write_LCD_String(PSTR("   HOPPER 3 ERROR   "), 4);
		while (1) {
		}
	}

}



//
//uint8_t Hopper_PayOut(uint8_t Count, uint8_t Hopper) {
//	uint8_t Data1, Data2, Data3;
//	uint8_t datarecive[30] = { 0 };
//	HopperSend(Hopper, 1, 164, (uint8_t[] ) { 165 }, datarecive);
//	_delay_ms(20);
//	HopperSend(Hopper, 0, 242, (uint8_t[] ) { 0 }, datarecive);
//	_delay_ms(50);
//	Data1 = datarecive[4];
//	Data2 = datarecive[5];
//	Data3 = datarecive[6];
//	HopperSend(Hopper, 0, 236, (uint8_t[] ) { 0 }, datarecive);
//
//	_delay_ms(50);
//
//	HopperSend(Hopper, 4, 167, (uint8_t[] ) { Data1, Data2, Data3, Count },
//			datarecive);
//	_delay_ms(20);
//	return false;
//}

