#ifndef QUIZOMAT_H_
#define QUIZOMAT_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

void quizomat(void);

void creditsCoinAcceptorQuizomat(void);
void creditsBillAcceptorQuizomat(void);
void checkQuizPayout(void);
void sendTime(void);
void sendStart(void);
void checkCounter(void);
void sendKeySwitch(void);

volatile uint8_t fl_coin_impuls_quizomat = 0, fl_coin_prot_impuls_quizomat = 0;
volatile uint8_t fl_bill_impuls_quizomat = 0, fl_bill_prot_impuls_quizomat = 0;
volatile uint8_t time = 0, points_plus = 0, points_minus = 0,FL_time_counter = 0,FL_start_rules_counter = 0;

#endif /* QUIZOMAT_H_ */
