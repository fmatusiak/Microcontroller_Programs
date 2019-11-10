/*
 * Hopper.h
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#ifndef HOPPER_H_
#define HOPPER_H_

#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>


void Check_Hopper(void);
uint8_t Hopper_PayOut(uint8_t Count,uint8_t Hopper);
uint8_t Hopper_LastPayOut(uint8_t Hopper);
void Chcek_Hopper_Last_PayOut(uint8_t Count_1,uint8_t Count_2,uint8_t Count_3);
uint8_t Check_Hopper_Opto(uint8_t Hopper);
uint8_t Hopper_STOPPayOut(uint8_t Hopper);
void Set_Hopper_Opto(void);
void PayOut(void);
void Hopper_Dump(uint8_t Hopper);
void Dumpowanie(void);
void Set_Expense_Hopper(void);


#endif /* HOPPER_H_ */
