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
void Hopper_control(void);
void Hopper_down(void);
void Hopper_up(void);
void Start_Nabij(void);
void Disp_caffe(void);


volatile uint8_t FL_keySwitch,FL_PAYOUT,FL_START_PAYOUT,FL_HOPPER,FL_Nabij,FL_Settings_automat,FL_SA,FL_SCREEN;
volatile uint16_t Tmp_time_payout,time_hopper,Tmp_time_hopper_high,Tmp_time_hopper_low,FL_Hopper_DOWN ,FL_Hopper_UP, money_pulses;





#endif /* CAFFE_H_ */
