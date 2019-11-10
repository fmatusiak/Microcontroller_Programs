/*
 * CoinAcceptor.c
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */
#include "CoinAcceptor.h"

void Check_Coin_Acceptor(void) {
	uint8_t datarecive[20] = { 0 };
	Write_LCD_String(PSTR("    COIN ACCEPTOR   "), 3);
	Write_LCD_String(PSTR("                    "), 4);
	_delay_ms(1000);
	ccTalk_send(COIN_ACCEPTOR, 0, 242, (uint8_t[] ) {0 });

	if (ccTalk_recive(datarecive, COIN_ACCEPTOR)) {

		if (((*(datarecive+4)) == X6D2SID_NUMBER_1)
				&& ((*(datarecive+5)) == X6D2SID_NUMBER_2)
				&& ((*(datarecive+6)) == X6D2SID_NUMBER_3)) {
			Write_LCD_String(PSTR("  COIN ACCEPTOR OK  "), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String(PSTR("COIN ACCEPTOR FAIL"), 4);
			while (1) {
			}
		}

	} else {
		Write_LCD_String(PSTR(" COIN ACCEPTOR ERROR"), 4);
		while (1) {
		}
	}

}

void Init_Coin_Acceptor(void) {

	ccTalk_send(COIN_ACCEPTOR, 0, 254, (uint8_t[] ) {0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 245, (uint8_t[] ) {0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 244, (uint8_t[] ) {0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) {3,2 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) {4,3 });
	_delay_ms(75);
	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) {5,1 });
	_delay_ms(75);
	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) {6,5 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 192, (uint8_t[] ) {0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 246, (uint8_t[] ) {0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 242, (uint8_t[] ) {0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 241, (uint8_t[] ) {0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 4, (uint8_t[] ) {0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 1 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 2 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 3 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 4 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 5 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 6 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 7 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 8 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 2, 231, (uint8_t[] ) { 252, 0 });
	_delay_ms(75);

}


void Coin_check_buffor(void) {
	uint8_t datarecive[20] = { 0 };
	ccTalk_send(COIN_ACCEPTOR, 0, 229, (uint8_t[] ) { 0 });

	if (ccTalk_recive(datarecive, COIN_ACCEPTOR)) {
		if (*(datarecive + 4) != BillEvent) {
			BillEvent = *(datarecive + 4);
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 1)) {
				Money_In_Automat = 10;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 2)) {
				Money_In_Automat = 20;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 3)) {
				Money_In_Automat = 50;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 4)) {
				Money_In_Automat = 100;

			}
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 5)) {
				Money_In_Automat = 200;
			}
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 6)) {
				Money_In_Automat = 500;
			}
		}

		if (Money_In_Automat >= Expense)
		{
			FL_WPBlock = true;
		}
	}
	uart_clear();



}

