/*
 * Caffe.h
 *
 *  Created on: 27 kwi 2017
 *      Author: dell
 */

#ifndef CAFFE_H_
#define CAFFE_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>



void Caffe(void);
void Settings(void);
void PayOut(void);
void Emulate_Hopper(void);
void SendMoneyRasp(void);
void Disp_automat(void);

void Start_Nabij(void);
void Settings_automat(void);


volatile uint8_t FL_keySwitch,FL_PAYOUT,FL_START_PAYOUT,FL_HOPPER,FL_Nabij,FL_Settings_automat,FL_SA,FL_IMP_HOPPER;
volatile uint16_t Tmp_time_payout,time_hopper,Tmp_time_hopper_high,Tmp_time_hopper_low,FL_Hopper_DOWN ,FL_Hopper_UP, money_pulses,FL_IMP_TIME;





#endif /* CAFFE_H_ */
