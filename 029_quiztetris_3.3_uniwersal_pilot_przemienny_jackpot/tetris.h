#ifndef TETRIS_H_
#define TETRIS_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

volatile uint16_t heart = 0;
volatile uint8_t fl_coin_impuls_tetris = 0, fl_coin_prot_impuls_tetris = 0;
volatile uint8_t fl_bill_impuls_tetris = 0, fl_bill_prot_impuls_tetris = 0,FL_heart = 0;

void tetris(void);
//void creditsCoinAcceptorTetris(void);
void creditsBillAcceptorTetris(void);
void sendHearts(void);
void sendKeySwitch(void);

#endif /* TETRIS_H_ */
