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
void addAttack(void);
void sendHearts(void);



#endif /* QUIZOMAT_H_ */
