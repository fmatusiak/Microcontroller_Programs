/*
 * CoinAcceptor.c
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */
#include "CoinAcceptor.h"

void Set_Sorter(void) {


	if (Hopper_One_Opto == 0) {

		ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 6, 1 });
		_delay_ms(50);

	} else {
		ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 6, 5 });
		_delay_ms(50);
	}

	if (Hopper_Two_Opto == 0) {
		ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 5, 1 });
		_delay_ms(50);

	} else {
		ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 5, 3 });
		_delay_ms(50);
	}

	if (Hopper_Three_Opto == 0) {
		ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 3, 1 });
		_delay_ms(50);

	}

	else {
		ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 3, 2 });
		_delay_ms(50);
	}

}

void Check_Coin_Acceptor(void) {
	uint8_t datarecive[20] = { 0 };
	Write_LCD_String_FLASH(PSTR("    COIN ACCEPTOR   "), 3);
	Write_LCD_String_FLASH(PSTR("                    "), 4);
	_delay_ms(1000);
	ccTalk_send(COIN_ACCEPTOR, 0, 242, (uint8_t[] ) { 0 });

	if (ccTalk_recive(datarecive, COIN_ACCEPTOR)) {

		if (((*(datarecive + 4)) == X6D2SID_NUMBER_1)
				&& ((*(datarecive + 5)) == X6D2SID_NUMBER_2)
				&& ((*(datarecive + 6)) == X6D2SID_NUMBER_3)) {
			Write_LCD_String_FLASH(PSTR("  COIN ACCEPTOR OK  "), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String_FLASH(PSTR("COIN ACCEPTOR FAIL"), 4);
			while (1) {
				Write_LCD_String_FLASH(PSTR("    COIN ACCEPTOR   "), 3);
				Write_LCD_String_FLASH(PSTR("COIN ACCEPTOR FAIL"), 4);
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
		Write_LCD_String_FLASH(PSTR(" COIN ACCEPTOR ERROR"), 4);
		while (1) {
		}
	}

}

void Init_Coin_Acceptor(void) {

	ccTalk_send(COIN_ACCEPTOR, 0, 254, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 245, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 244, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 1, 1 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 2, 1 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 3, 2 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 4, 1 });
	_delay_ms(75);
	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 5, 3 });
	_delay_ms(75);
	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 6, 5 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 192, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 246, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 242, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 241, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 4, (uint8_t[] ) { 0 });
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



	ccTalk_send(COIN_ACCEPTOR, 2, 231, (uint8_t[] ) { Inhibit_Coin, 0 }); //252
	_delay_ms(75);

}
void Coin_Clear_buffor(void) {
	uint8_t datarecive[20] = { 0 };
	ccTalk_send(COIN_ACCEPTOR, 0, 229, (uint8_t[] ) { 0 });

	if (ccTalk_recive(datarecive, COIN_ACCEPTOR)) {
		if (*(datarecive + 4) != CoinEvent) {
			CoinEvent = *(datarecive + 4);
		}

	}
	uart_clear();
}

void Coin_check_buffor(void) {
	uint8_t datarecive[20] = { 0 };
	ccTalk_send(COIN_ACCEPTOR, 0, 229, (uint8_t[] ) { 0 });

	if (ccTalk_recive(datarecive, COIN_ACCEPTOR)) {
		if (*(datarecive + 4) != CoinEvent) {
			CoinEvent = *(datarecive + 4);
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 1)) {
				Money_In_Automat += 1;
				Time_out_Money = 0;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 2)) {
				Money_In_Automat += 2;
				Time_out_Money = 0;
			}

			if (((*(datarecive + 6) == 2) || (*(datarecive + 6) == 1))
					&& (*(datarecive + 5) == 3)) {
				Money_In_Automat += 5;
				Money_50gr_Atmega++;
				Time_out_Money = 0;
			}

			if (((*(datarecive + 6) == 3) || (*(datarecive + 6) == 1))
					&& (*(datarecive + 5) == 4)) {
				Money_In_Automat += 10;

				Time_out_Money = 0;

			}
			if (((*(datarecive + 6) == 3) || (*(datarecive + 6) == 1))
					&& (*(datarecive + 5) == 5)) {
				Money_In_Automat += 20;
				Money_2zl_Atmega++;
				Time_out_Money = 0;
			}
			if (((*(datarecive + 6) == 5) || (*(datarecive + 6) == 1))
					&& (*(datarecive + 5) == 6)) {
				Money_In_Automat += 50;
				Money_5zl_Atmega++;
				Time_out_Money = 0;
			}
		}

	}
	uart_clear();
}

void Refil(void) {
	uint8_t inhibit;
	uint8_t datarecive[20] = { 0 };

	inhibit = 255;

	if (Hopper_One_Opto == 0) {
		inhibit -= 32;
	}
	if (Hopper_Two_Opto == 0) {
		inhibit -= 16;
	}
	if (Hopper_Three_Opto == 0) {
		inhibit -= 4;
	}

	Write_LCD(3);


	ccTalk_send(COIN_ACCEPTOR, 2, 231, (uint8_t[] ) { inhibit, 0 }); //252
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 229, (uint8_t[] ) { 0 });

	if (ccTalk_recive(datarecive, COIN_ACCEPTOR)) {
		if (*(datarecive + 4) != CoinEvent) {
			CoinEvent = *(datarecive + 4);

			if ((*(datarecive + 6) == 2) && (*(datarecive + 5) == 3)) {
				Money_50gr_Atmega++;
			}

			if ((*(datarecive + 6) == 4) && (*(datarecive + 5) == 5)) {
				Money_2zl_Atmega++;

			}

			if ((*(datarecive + 6) == 5) && (*(datarecive + 5) == 6)) {
				Money_5zl_Atmega++;
			}
		}

	}
	Set_Hopper_Opto();
	Set_Sorter();
	uart_clear();

}

