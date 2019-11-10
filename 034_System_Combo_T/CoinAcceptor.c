/*
 * CoinAcceptor.c
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */
#include "CoinAcceptor.h"

void Check_Coin_Acceptor(void) {
	uint8_t datarecive[30] = {0};
	Write_LCD_String("    COIN ACCEPTOR   ", 3);
	Write_LCD_String("                    ", 4);
	delayS(1);

	if (Coin_Acceptor_Send(0, 242, 0, datarecive) ) {

		if(((datarecive[9]) == X6D2SID_NUMBER_1)
				&& ((datarecive[10]) == X6D2SID_NUMBER_2)
				&& ((datarecive[11]) == X6D2SID_NUMBER_3))
		{
			Write_LCD_String("  COIN ACCEPTOR OK  ", 4);
			delayS(1);
		}
		else
		{
			Write_LCD_String("COIN ACCEPTOR FAIL", 4);
			while (1) {
				}
		}

	} else {
		Write_LCD_String(" COIN ACCEPTOR ERROR", 4);
		while (1) {
		}
	}

}

uint8_t Coin_Acceptor_Send(uint8_t dataCount, uint8_t command, uint8_t *data,
		uint8_t *datarecive) {
	return ccTalk_send(dataCount, command, data, datarecive,
	COIN_ACCEPTOR);

}

void Init_Coin_Acceptor(void) {
	uint8_t datarecive[30] = {0};

	Coin_Acceptor_Send(0, 254, 0, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(0, 245, 0, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(0, 244, 0, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(2, 210, (uint8_t[] ) { 3, 2 }, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(2, 210, (uint8_t[] ) { 4, 3 }, datarecive);
	_delay_ms(75);
	Coin_Acceptor_Send(2, 210, (uint8_t[] ) { 5, 1 }, datarecive);
	_delay_ms(75);
	Coin_Acceptor_Send(2, 210, (uint8_t[] ) { 6, 5 }, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(0, 192, 0, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(0, 246, 0, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(0, 242, 0, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(0, 241, 0, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(0, 4, 0, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(1, 184, (uint8_t[] ) { 1 }, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(1, 184, (uint8_t[] ) { 2 }, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(1, 184, (uint8_t[] ) { 3 }, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(1, 184, (uint8_t[] ) { 4 }, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(1, 184, (uint8_t[] ) { 5 }, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(1, 184, (uint8_t[] ) { 6 }, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(1, 184, (uint8_t[] ) { 7 }, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(1, 184, (uint8_t[] ) { 8 }, datarecive);
	_delay_ms(75);

	Coin_Acceptor_Send(2, 231, (uint8_t[] ) { 252, 0 }, datarecive);
	_delay_ms(75);

}
void Coin_Acceptor_inhibit(void) {
	uint8_t datarecive[20] = {0};
	Coin_Acceptor_Send(2, 231, (uint8_t[] ) { 0, 0 }, datarecive);

	_delay_ms(25);

}

void Coin_Acceptor_unhibit(void) {
	uint8_t datarecive[20] = {0};
	Coin_Acceptor_Send(2, 231, (uint8_t[] ) { 252, 0 }, datarecive);
	_delay_ms(25);

}

void Coin_check_buffor(void) {
	uint8_t datarecive[25] = {0};
	Coin_Acceptor_Send(0, 229, 0, datarecive);
	_delay_ms(25);

}

