#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "data.h"



// FUNCTIONS DECLARATION
//======= MAIN =============
int sendCommand(uint8_t);
int sendCommandUart(uint8_t);
uint8_t receiveCommand(void);
void settings(void);
void switchOn(void);
void ioInit(void);
void configurationInit(void);
void switchOnPi(void);
// =========================
//======== QUIZ ============
void checkQuizPayout(void);
void checkCounter(void);
void displaySwitch(void);

void quizomat(void);
//==========================
//======== TETRIS ==========
void tetris(void);
void sendHearts(void);
void endTime(void);
void switchOnCard(void);
void sendTimeCounter(void);

//==========================
void configurationInit(void);
void initSettings(void);
void creditsCoinAcceptorQuizomat(void);
void creditsBillAcceptorQuizomat(void);
volatile uint8_t commandBuffer[30];
// ========================================== quiz command =============================================================================

// ========================================== tetris command ===========================================================================
volatile uint8_t sended, buffer_size;

volatile uint16_t toLong, startTimeout, startImpulseTime, counter_off, counter_off1, counter_off2,
		switchTimeout,counter_pulses_in,counter_pulses_out;
volatile uint8_t TETRIS_ON, QUIZ_ON, PROT_ON, FL_TETRIS_ON,
		FL_QUIZ_ON, FL_pilot, FL_CARD;
volatile uint16_t delayCounts, counterTimeout, displayTimeout,counterTimeout_counter,counterTimeout_counter_OUT;
volatile uint8_t FL_counter, FL_automatOn, FL_payout, FL_display_switch,
		FL_settingsQuiz, FL_settingsTetris, FL_keySwitch, FL_protection,
		command, pause, receive, FL_start;
volatile uint8_t tmp_tetris, tmp_quiz, FL_start_rules, FL_counter_in,
		FL_display, FL_pilotes, FLAGA_Send;

#endif /* MAIN_H_ */
