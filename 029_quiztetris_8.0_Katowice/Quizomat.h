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




volatile uint8_t FL_start_rules_counter = 1, FL_time_counter = 1;

#endif /* QUIZOMAT_H_ */
