#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#define F_CPU 16000000UL
#define RS_BAUD 9600
#define CREDIT_DELAY 200
#define CREDITHS_DELAY 100
#define RS_UBRR 103
// ======================= BOARD ===========================================
// INS

#define IN1_PC3 PC3
#define IN2_PC4 PC4
#define IN3_PC5 PC5
#define IN4_PC6 PC6
#define IN5_PC2 PC2

#define HS_ON_OFF_PA4 PA4
#define DOOR_PA6 PA6
#define WE1_PA7 PA7
#define WE2_PC7 PC7 // dwa
#define RX2_PA0 PA0 // dwa

#define RX_DO_RP_PD0 PD0 // pi in


// OUTS
#define OUT1_PD5 PD5
#define OUT2_PD6 PD6
#define OUT3_PD7 PD7
#define OUT4_PC0 PC0
#define OUT5_PC1 PC1

#define PRZEL_VGA_PB2 PB2 // vga switch
#define PRZEKAZNIK_PB0 PB0
#define MUTE_PD4 PB5

#define TX2_PA1 PA1

#define NABIJANIE_PB5 PB5
#define TX_DO_RP_PD1 PD1 //rasp_conf
// =============================

// ==============================================================================
// ================================== IN PROGRAM ================================
// INS
#define READ_PI_IN	RX_DO_RP_PD0
#define DDR_READ_PI_IN DDRD &= ~(1<<READ_PI_IN)
#define PIN_READ_PI_IN PIND & _BV(READ_PI_IN)
#define READ_PI_IN_VCC PORTD |= _BV(READ_PI_IN)
#define READ_PI_IN_GND PORTD &= ~_BV(READ_PI_IN)

#define CARD_IN DOOR_PA6
#define DDR_CARD_IN DDRA &= ~(1<<CARD_IN)
#define PIN_CARD_IN PINA & _BV(CARD_IN)
#define CARD_IN_VCC PORTA |= _BV(CARD_IN)
#define CARD_IN_GND PORTA &= ~_BV(CARD_IN)

#define COIN_ACCEPTOR_IN IN1_PC3
#define DDR_COIN_ACCEPTOR_IN DDRC &= ~(1<<COIN_ACCEPTOR_IN)
#define PIN_COIN_ACCEPTOR_IN PINC & _BV(COIN_ACCEPTOR_IN)
#define COIN_ACCEPTOR_IN_VCC PORTC |= _BV(COIN_ACCEPTOR_IN)
#define COIN_ACCEPTOR_IN_GND PORTC &= ~_BV(COIN_ACCEPTOR_IN)

#define BILL_ACCEPTOR_IN IN2_PC4
#define DDR_BILL_ACCEPTOR_IN DDRC &= ~(1<<BILL_ACCEPTOR_IN)
#define PIN_BILL_ACCEPTOR_IN PINC & _BV(BILL_ACCEPTOR_IN)
#define BILL_ACCEPTOR_IN_VCC PORTC |= _BV(BILL_ACCEPTOR_IN)
#define BILL_ACCEPTOR_IN_GND PORTC &= ~_BV(BILL_ACCEPTOR_IN)

#define DISPLAY_CHANGE_BUTTON_IN IN3_PC5
#define DDR_DISPLAY_CHANGE_BUTTON_IN DDRC &= ~(1<<DISPLAY_CHANGE_BUTTON_IN)
#define PIN_DISPLAY_CHANGE_BUTTON_IN PINC & _BV(DISPLAY_CHANGE_BUTTON_IN)
#define DISPLAY_CHANGE_BUTTON_IN_VCC PORTC |= _BV(DISPLAY_CHANGE_BUTTON_IN)
#define DISPLAY_CHANGE_BUTTON_IN_GND PORTC &= ~_BV(DISPLAY_CHANGE_BUTTON_IN)

#define PAYOUT_BUTTON_IN IN4_PC6
#define DDR_PAYOUT_BUTTON_IN DDRC &= ~(1<<PAYOUT_BUTTON_IN)
#define PIN_PAYOUT_BUTTON_IN PINC & _BV(PAYOUT_BUTTON_IN)
#define PAYOUT_BUTTON_IN_VCC PORTC |= _BV(PAYOUT_BUTTON_IN)
#define PAYOUT_BUTTON_IN_GND PORTC &= ~_BV(PAYOUT_BUTTON_IN)

#define PROTECTION_IN IN5_PC2
#define DDR_PROTECTION_IN DDRC &= ~(1<<PROTECTION_IN)
#define PIN_PROTECTION_IN PINC & _BV(PROTECTION_IN)
#define PROTECTION_IN_VCC PORTC |= _BV(PROTECTION_IN)
#define PROTECTION_IN_GND PORTC &= ~_BV(PROTECTION_IN)

#define PILOT_IN HS_ON_OFF_PA4
#define DDR_PILOT_IN DDRA &= ~(1<<PILOT_IN)
#define PIN_PILOT_IN PINA & _BV(PILOT_IN)
#define PILOT_IN_VCC PORTA |= _BV(PILOT_IN)
#define PILOT_IN_GND PORTA &= ~_BV(PILOT_IN)

#define KEY_SWITCH_IN WE1_PA7
#define DDR_KEY_SWITCH_IN DDRA &= ~(1<<KEY_SWITCH_IN)
#define PIN_KEY_SWITCH_IN PINA & _BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN_VCC PORTA |= _BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN_GND PORTA &= ~_BV(KEY_SWITCH_IN)

#define COUNTER_IN WE2_PC7
#define DDR_COUNTER_IN DDRC &= ~(1<<COUNTER_IN)
#define PIN_COUNTER_IN PINC & _BV(COUNTER_IN)
#define COUNTER_IN_VCC PORTC |= _BV(COUNTER_IN)
#define COUNTER_IN_GND PORTC &= ~_BV(COUNTER_IN)


// OUTS

#define SEND_PI_OUT TX_DO_RP_PD1
#define SEND_PI_OUT_DDR DDRD |= (1<<SEND_PI_OUT)
#define SEND_PI_OUT_LOW PORTD &= ~(1<<SEND_PI_OUT)
#define SEND_PI_OUT_HIGH PORTD |= (1<<SEND_PI_OUT)
#define SEND_PI_OUT_Z PORTD ^= (1<<SEND_PI_OUT)

#define COIN_ACCEPTOR_OUT OUT1_PD5
#define COIN_ACCEPTOR_OUT_DDR DDRD |= (1<<COIN_ACCEPTOR_OUT)
#define COIN_ACCEPTOR_OUT_LOW PORTD &= ~(1<<COIN_ACCEPTOR_OUT)
#define COIN_ACCEPTOR_OUT_HIGH PORTD |= (1<<COIN_ACCEPTOR_OUT)
#define COIN_ACCEPTOR_OUT_Z PORTD ^= (1<<COIN_ACCEPTOR_OUT)

#define BILL_ACCEPTOR_OUT OUT2_PD6
#define BILL_ACCEPTOR_OUT_DDR DDRD |= (1<<BILL_ACCEPTOR_OUT)
#define BILL_ACCEPTOR_OUT_LOW PORTD &= ~(1<<BILL_ACCEPTOR_OUT)
#define BILL_ACCEPTOR_OUT_HIGH PORTD |= (1<<BILL_ACCEPTOR_OUT)
#define BILL_ACCEPTOR_OUT_Z PORTD ^= (1<<BILL_ACCEPTOR_OUT)

#define START_OUT OUT3_PD7
#define START_OUT_DDR DDRD |= (1<<START_OUT)
#define START_OUT_LOW PORTD &= ~(1<<START_OUT)
#define START_OUT_HIGH PORTD |= (1<<START_OUT)
#define START_OUT_Z PORTD ^= (1<<START_OUT)

#define PAYOUT_OUT OUT4_PC0
#define PAYOUT_OUT_DDR DDRC |= (1<<PAYOUT_OUT)
#define PAYOUT_OUT_LOW PORTC &= ~(1<<PAYOUT_OUT)
#define PAYOUT_OUT_HIGH PORTC |= (1<<PAYOUT_OUT)
#define PAYOUT_OUT_Z PORTC ^= (1<<PAYOUT_OUT)

#define SCREEN_SWITCH_OUT PRZEL_VGA_PB2
#define SCREEN_SWITCH_OUT_DDR DDRB |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_LOW PORTB &= ~(1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_HIGH PORTB |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_Z PORTB ^= (1<<SCREEN_SWITCH_OUT)

#define SWITCH_ON_MACHINE PRZEKAZNIK_PB0
#define SWITCH_ON_MACHINE_DDR DDRB |= (1<<SWITCH_ON_MACHINE)
#define SWITCH_ON_MACHINE_LOW PORTB &= ~(1<<SWITCH_ON_MACHINE)
#define SWITCH_ON_MACHINE_HIGH PORTB |= (1<<SWITCH_ON_MACHINE)
#define SWITCH_ON_MACHINE_Z PORTB ^= (1<<SWITCH_ON_MACHINE)


#define CONTROL NABIJANIE_PB5
#define CONTROL_DDR DDRB |= (1<<CONTROL)
#define CONTROL_LOW PORTB &= ~(1<<CONTROL)
#define CONTROL_HIGH PORTB |= (1<<CONTROL)
#define CONTROL_Z PORTB ^= (1<<CONTROL)

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
void creditsCoinAcceptorQuiz(void);
void creditsBillAcceptorQuiz(void); // credits
void quizomat(void);
//==========================
//======== TETRIS ==========
void tetris(void);
void sendHearts(void);
void endTime(void);
void switchOnCard(void);
void sendTimeCounter(void);
void sendTimeBill(void);

//==========================
void configurationInit(void);
void initSettings(void);

volatile uint8_t commandBuffer[50];
// ========================================== quiz command =============================================================================
volatile uint8_t com_counter_start, com_counter_stop, com_attack,
		com_clear_time_switch, com_switch_on_tetris, com_on_automat,
		com_switch_on, sended, com_quiz_start_rules, com_quiz_on;
// ========================================== tetris command ===========================================================================
volatile uint8_t send_hearts, sended, buffer_size, counter_pulses,
		com_send_tetris, com_send_hearts, com_round, com_lock_pay,
		com_unlock_pay;
volatile uint16_t toLong, startTimeout, startImpulseTime, counter_off, counter_off1, counter_off2,
		switchTimeout;
volatile uint8_t TETRIS_ON, QUIZ_ON, JACKPOT_ON, PROT_ON, FL_TETRIS_ON,
		FL_QUIZ_ON, FL_pilot, FL_CARD;
volatile uint16_t delayCounts, counterTimeout, displayTimeout,counterTimeout_counter;
volatile uint8_t FL_counter, FL_automatOn, FL_payout, FL_display_switch,
		FL_settingsQuiz, FL_settingsTetris, FL_keySwitch, FL_protection,
		command, pause, receive, FL_start;
volatile uint8_t tmp_tetris, tmp_quiz, FL_start_rules, FL_counter_in,
		FL_display, FL_pilotes, FLAGA_Send;

#endif /* MAIN_H_ */
