/*
 * BillAcceptor.c
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#include "BillAcceptor.h"

void Bill_Clear_buffor(void) {
	uint8_t datarecive[20] = { 0 };
	ccTalk_send(BILL_ACCEPTOR, 0, 159, (uint8_t[] ) { 0 });
	if (ccTalk_recive(datarecive, BILL_ACCEPTOR)) {
		if (*(datarecive + 4) != BillEvent) {
			BillEvent = *(datarecive + 4);
		}

	}
	uart_clear();
}

void Check_Bill_Acceptor(void) {
	uint8_t datarecive[20] = { 0 };
	Write_LCD_String_FLASH(PSTR("    BILL ACCEPTOR   "), 3);
	Write_LCD_String_FLASH(PSTR("                    "), 4);
	_delay_ms(1000);

	ccTalk_send(BILL_ACCEPTOR, 0, 242, (uint8_t[] ) { 0 });
	if (ccTalk_recive(datarecive, BILL_ACCEPTOR)) {

		if (((*(datarecive + 4)) == NV10ID_NUMBER_1)
				&& ((*(datarecive + 5)) == NV10ID_NUMBER_2)
				&& ((*(datarecive + 6)) == NV10ID_NUMBER_3)
				&& ((*(datarecive + 7)) == NV10ID_NUMBER_4))

				{
			Write_LCD_String_FLASH(PSTR("  BILL ACCEPTOR OK  "), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String_FLASH(PSTR(" BILL ACCEPTOR FAIL"), 4);
			while (1) {
			}
		}

	} else {
		Write_LCD_String_FLASH(PSTR(" BILL ACCEPTOR ERROR"), 4);
		while (1) {
		}
	}
}

void Init_Bill_Acceptor(void) {

	ccTalk_send(BILL_ACCEPTOR, 0, 254, (uint8_t[] ) { 0 });
	_delay_ms(50);
	ccTalk_send(BILL_ACCEPTOR, 2, 231, (uint8_t[] ) { 255, 255 });
	_delay_ms(50);
	ccTalk_send(BILL_ACCEPTOR, 1, 228, (uint8_t[] ) { 1 });

	_delay_ms(50);

}

void Bill_Check_Buffor(void) {
	uint8_t datarecive[20] = { 0 };
	ccTalk_send(BILL_ACCEPTOR, 0, 159, (uint8_t[] ) { 0 });

	if (ccTalk_recive(datarecive, BILL_ACCEPTOR)) {
		if (*(datarecive + 4) != BillEvent) {
			BillEvent = *(datarecive + 4);
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 1)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 1 });
				_delay_ms(50);
				Money_In_Automat += 100;
				Time_out_Money = 0;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 2)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 1 });
				_delay_ms(50);
				Money_In_Automat += 200;
				Time_out_Money = 0;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 3)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 1 });
				_delay_ms(50);
				Money_In_Automat += 500;
				Time_out_Money = 0;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 4)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 0 });
				_delay_ms(50);
				Time_out_Money = 0;
			}
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 5)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 0 });
				_delay_ms(50);
				Time_out_Money = 0;
			}
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 6)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 0 });
				_delay_ms(50);
				Time_out_Money = 0;
			}
		}

	}
	uart_clear();
}
