/*
 * jackpot.h
 *
 *  Created on: 2 lis 2016
 *      Author: dell
 */

#ifndef JACKPOT_H_
#define JACKPOT_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "stdlib.h"


void jackpot(void);
void checkCounterJackpot(void);
void sendCounterJackpot(void);
void buzzer(void);

volatile uint16_t value_jackpot = 0, timeout_jackpot = 0,TMP_LIGHT = 0;
volatile uint8_t FL_COUNTER_SPIN = 0,FLAGA_START = 0,FLAGA_STAWKA = 0, FL_KEY = 0;



#endif /* JACKPOT_H_ */
