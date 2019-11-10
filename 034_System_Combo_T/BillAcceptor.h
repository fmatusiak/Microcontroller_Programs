/*
 * BillAcceptor.h
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#ifndef BILLACCEPTOR_H_
#define BILLACCEPTOR_H_

#include "main.h"



void Check_Bill_Acceptor(void);
uint8_t Bill_Acceptor_Send(uint8_t dataCount, uint8_t command, uint8_t *data, uint8_t *datarecive);
void Init_Bill_Acceptor(void);
void Bill_Acceptor_inhibit(void);
void Bill_Acceptor_unhibit(void);
void Bill_Check_Buffor(void);


#endif /* BILLACCEPTOR_H_ */
