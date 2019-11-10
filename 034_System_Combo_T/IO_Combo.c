/*
 * IO_Board.c
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#include "IO_Combo.h"

void Check_IO_Combo(void) {
	uint8_t datarecive[20] = {0};

	Write_LCD_String("      IO COMBO      ", 3);
	Write_LCD_String("                    ", 4);
	delayS(1);

	if (IO_Combo_Send(0, 242, 0, datarecive)) {

		if (((*(datarecive + 9)) == IOCOMBOID_NUMBER_)
				&& ((*(datarecive + 10)) == IOCOMBOID_NUMBER_)
				&& ((*(datarecive + 11)) == IOCOMBOID_NUMBER_)) {
			Write_LCD_String("    IO COMBO OK", 4);
			delayS(1);
		} else {
			Write_LCD_String("   IO COMBO FAIL   ", 4);
			while (1) {
			}
		}

	} else {
		Write_LCD_String("   IO COMBO ERROR   ", 4);
		while (1) {
		}
	}

}

uint8_t IO_Combo_Send(uint8_t dataCount, uint8_t command, uint8_t *data,
		uint8_t *datarecive) {

	return ccTalk_send(dataCount, command, data, datarecive, IO_COMBO);

}

void IO_Combo_Clear_Escrow(void) {
	uint8_t datarecive[20] = {0};
	IO_Combo_Send(1, 70, (uint8_t[] ) { 1 }, datarecive);

}
