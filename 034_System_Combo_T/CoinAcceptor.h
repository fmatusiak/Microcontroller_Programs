/*
 * CoinAcceptor.h
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#ifndef COINACCEPTOR_H_
#define COINACCEPTOR_H_

#include "main.h"

void Check_Coin_Acceptor(void);
uint8_t Coin_Acceptor_Send(uint8_t dataCount,uint8_t command,uint8_t *data,uint8_t *datarecive);
void Init_Coin_Acceptor(void);
void Coin_Acceptor_inhibit(void);
void Coin_Acceptor_unhibit(void);
void Coin_check_buffor(void);

#endif /* COINACCEPTOR_H_ */
