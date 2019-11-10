#ifndef QUIZOMAT_H_
#define QUIZOMAT_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

void quizomat(void);

void checkQuizPayout(void);
void sendTime(void);
void sendStart(void);
void checkCounter(void);
void sendKeySwitch(void);
void checkQuizBet(void);
void checkQuizButton(void);
void checkQuizHold(void);
void SetRelay(void);
void SetDisplay(void);


volatile uint8_t FL_time_counter = 0,FL_start_rules_counter = 1;
volatile uint8_t FL_time_counter_OUT = 0;

#endif /* QUIZOMAT_H_ */