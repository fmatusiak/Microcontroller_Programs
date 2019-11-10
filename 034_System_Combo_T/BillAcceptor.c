/*
 * BillAcceptor.c
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#include "BillAcceptor.h"

void Check_Bill_Acceptor(void) {
	uint8_t datarecive[20] = {0};
	Write_LCD_String("    BILL ACCEPTOR   ", 3);
	Write_LCD_String("                    ", 4);
	delayS(1);

	if (Bill_Acceptor_Send(0, 242, 0, datarecive)) {

		if (((*(datarecive + 9)) == NV10ID_NUMBER_1)
				&& ((*(datarecive + 10)) == NV10ID_NUMBER_2)
				&& ((*(datarecive + 11)) == NV10ID_NUMBER_3)
			    && ((*(datarecive + 12)) == NV10ID_NUMBER_4))

		{
			Write_LCD_String("  BILL ACCEPTOR OK  ", 4);
			delayS(1);
		} else {
			Write_LCD_String(" BILL ACCEPTOR FAIL", 4);
			while (1) {
			}
		}

	} else {
		Write_LCD_String(" BILL ACCEPTOR ERROR", 4);
		while (1) {
		}
	}
}

uint8_t Bill_Acceptor_Send(uint8_t dataCount, uint8_t command, uint8_t *data,
		uint8_t *datarecive) {

	return ccTalk_send(dataCount, command, data, datarecive, BILL_ACCEPTOR);
}

void Init_Bill_Acceptor(void) {
	uint8_t datarecive[20] = {0};
	Bill_Acceptor_Send(0, 254, (uint8_t[] ) { 0 }, datarecive);
	_delay_ms(50);
	Bill_Acceptor_Send(2, 231, (uint8_t[] ) { 255, 255 }, datarecive);
	_delay_ms(50);
	Bill_Acceptor_Send(1, 228, (uint8_t[] ) { 1 }, datarecive);
	_delay_ms(50);

}
void Bill_Acceptor_inhibit(void) {
	uint8_t datarecive[20] = {0};
	Bill_Acceptor_Send(2, 231, (uint8_t[] ) { 0, 0 }, datarecive);
	_delay_ms(25);

}

void Bill_Acceptor_unhibit(void) {
	uint8_t datarecive[20] = {0};
	Bill_Acceptor_Send(2, 231, (uint8_t[] ) { 255, 255 }, datarecive);
	_delay_ms(25);

}

void Bill_Check_Buffor(void) {
	uint8_t datarecive[30] = {0};
	Bill_Acceptor_Send(0, 159, 0, datarecive);
	_delay_ms(25);

	if (datarecive[9] != BillEvent) {
		datarecive[9] = BillEvent;
		if ((datarecive[11] == 1) && (datarecive[10] == 1)) {
			Bill_Acceptor_Send(1, 154, (uint8_t[] ) { 1 }, datarecive);
			_delay_ms(20);
			Money_In_Automat = 100;
			FL_WPBlock = true;

		}

		if ((datarecive[11] == 1) && (datarecive[10] == 2)) {
			Bill_Acceptor_Send(1, 154, (uint8_t[] ) { 1 }, datarecive);
			_delay_ms(20);
			Money_In_Automat = 200;
			FL_WPBlock = true;
		}

		if ((datarecive[11] == 1) && (datarecive[10] == 3)) {
			Bill_Acceptor_Send(1, 154, (uint8_t[] ) { 1 }, datarecive);
			_delay_ms(20);
			Money_In_Automat = 500;
			FL_WPBlock = true;

		}

		if ((datarecive[11] == 1) && (datarecive[10] == 4)) {
			Bill_Acceptor_Send(1, 154, (uint8_t[] ) { 0 }, datarecive);
		}
		if ((datarecive[11] == 1) && (datarecive[10] == 5)) {
			Bill_Acceptor_Send(1, 154, (uint8_t[] ) { 0 }, datarecive);
		}
	}
}
