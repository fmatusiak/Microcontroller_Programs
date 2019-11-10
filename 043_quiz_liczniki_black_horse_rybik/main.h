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

#define IN1_PA3 PA3
#define IN2_PA2 PA2
#define IN3_PA1 PA1
#define IN4_PA0 PA0
#define IN5_PA4 PA4
#define IN6_PC3 PC3


#define WE1_PB4 PB4 // stac in
#define RX_DO_RP_PD0 PD0 // pi in
#define WE2_PC1 PC1 // dwa
#define RX2_PC0 PC0 // dwa

// OUTS
#define OUT1_PC6 PC6
#define OUT2_PC7 PC7
#define OUT3_PA7 PA7
#define OUT4_PA6 PA6
#define OUT5_PA5 PA5

#define MUTE_OFF_PC4 PC4
#define NABIJANIE_PB7 PB7
#define TX_DO_RP_PD1 PD1 //rasp_conf
#define PRZEL_VGA_PB2 PB2 // vga switch
#define Relay_2_PD2 PD2 // vga switch
#define JP_SCREEN_SWITCH_PD4 PD4
#define OUT6_PC5 PC5

// =============================

// ==============================================================================
// ================================== IN PROGRAM ================================
// INS
#define READ_PI_IN	RX_DO_RP_PD0
#define DDR_READ_PI_IN DDRD &= ~(1<<READ_PI_IN)
#define PIN_READ_PI_IN PIND & _BV(READ_PI_IN)
#define READ_PI_IN_VCC PORTD |= _BV(READ_PI_IN)
#define READ_PI_IN_GND PORTD &= ~_BV(READ_PI_IN)

#define COIN_ACCEPTOR_IN IN1_PA3
#define DDR_COIN_ACCEPTOR_IN DDRA &= ~(1<<COIN_ACCEPTOR_IN)
#define PIN_COIN_ACCEPTOR_IN PINA & _BV(COIN_ACCEPTOR_IN)
#define COIN_ACCEPTOR_IN_VCC PORTA |= _BV(COIN_ACCEPTOR_IN)
#define COIN_ACCEPTOR_IN_GND PORTA &= ~_BV(COIN_ACCEPTOR_IN)

#define BILL_ACCEPTOR_IN IN2_PA2
#define DDR_BILL_ACCEPTOR_IN DDRA &= ~(1<<BILL_ACCEPTOR_IN)
#define PIN_BILL_ACCEPTOR_IN PINA & _BV(BILL_ACCEPTOR_IN)
#define BILL_ACCEPTOR_IN_VCC PORTA |= _BV(BILL_ACCEPTOR_IN)
#define BILL_ACCEPTOR_IN_GND PORTA &= ~_BV(BILL_ACCEPTOR_IN)

#define PROTECTION_IN IN5_PA4
#define DDR_PROTECTION_IN DDRA &= ~(1<<PROTECTION_IN)
#define PIN_PROTECTION_IN PINA & _BV(PROTECTION_IN)
#define BILL_PROTECTION_IN_VCC PORTA |= _BV(PROTECTION_IN)
#define BILL_PROTECTION_IN_GND PORTA &= ~_BV(PROTECTION_IN)

#define KEY_SWITCH_IN WE1_PB4
#define DDR_KEY_SWITCH_IN DDRB &= ~(1<<KEY_SWITCH_IN)
#define PIN_KEY_SWITCH_IN PINB & _BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN_VCC PORTB |= _BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN_GND PORTB &= ~_BV(KEY_SWITCH_IN)

// OUTS
#define COIN_ACCEPTOR_OUT OUT1_PC6
#define COIN_ACCEPTOR_OUT_DDR DDRC |= (1<<COIN_ACCEPTOR_OUT)
#define COIN_ACCEPTOR_OUT_LOW PORTC &= ~(1<<COIN_ACCEPTOR_OUT)
#define COIN_ACCEPTOR_OUT_HIGH PORTC |= (1<<COIN_ACCEPTOR_OUT)
#define COIN_ACCEPTOR_OUT_Z PORTC ^= (1<<COIN_ACCEPTOR_OUT)

#define BILL_ACCEPTOR_OUT OUT2_PC7
#define BILL_ACCEPTOR_OUT_DDR DDRC |= (1<<BILL_ACCEPTOR_OUT)
#define BILL_ACCEPTOR_OUT_LOW PORTC &= ~(1<<BILL_ACCEPTOR_OUT)
#define BILL_ACCEPTOR_OUT_HIGH PORTC |= (1<<BILL_ACCEPTOR_OUT)
#define BILL_ACCEPTOR_OUT_Z PORTC ^= (1<<BILL_ACCEPTOR_OUT)


#define SEND_PI_OUT TX_DO_RP_PD1
#define SEND_PI_OUT_DDR DDRD |= (1<<SEND_PI_OUT)
#define SEND_PI_OUT_LOW PORTD &= ~(1<<SEND_PI_OUT)
#define SEND_PI_OUT_HIGH PORTD |= (1<<SEND_PI_OUT)
#define SEND_PI_OUT_Z PORTD ^= (1<<SEND_PI_OUT)

#define PAYOUT_OUT Relay_2_PD2
#define PAYOUT_OUT_DDR DDRD |= (1<<PAYOUT_OUT)
#define PAYOUT_OUT_LOW PORTD &= ~(1<<PAYOUT_OUT)
#define PAYOUT_OUT_HIGH PORTD |= (1<<PAYOUT_OUT)
#define PAYOUT_OUT_Z PORTD ^= (1<<PAYOUT_OUT)


#define PAYOUT_OUT_4 PA6
#define PAYOUT_OUT_4_DDR DDRA |= (1<<PAYOUT_OUT_4)
#define PAYOUT_OUT_4_LOW PORTA &= ~(1<<PAYOUT_OUT_4)
#define PAYOUT_OUT_4_HIGH PORTA |= (1<<PAYOUT_OUT_4)
#define PAYOUT_OUT_4_Z PORTA ^= (1<<PAYOUT_OUT_4)


#define START_OUT PRZEL_VGA_PB2
#define START_OUT_DDR DDRB |= (1<<START_OUT)
#define START_OUT_LOW PORTB &= ~(1<<START_OUT)
#define START_OUT_HIGH PORTB |= (1<<START_OUT)
#define START_OUT_Z PORTB ^= (1<<START_OUT)

#define START_OUT_3 PA7
#define START_OUT_3_DDR DDRA |= (1<<START_OUT_3)
#define START_OUT_3_LOW PORTA &= ~(1<<START_OUT_3)
#define START_OUT_3_HIGH PORTA |= (1<<START_OUT_3)
#define START_OUT_3_Z PORTA ^= (1<<START_OUT_3)

#define SCREEN_SWITCH_OUT JP_SCREEN_SWITCH_PD4
#define SCREEN_SWITCH_OUT_DDR DDRD |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_LOW PORTD &= ~(1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_HIGH PORTD |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_Z PORTD ^= (1<<SCREEN_SWITCH_OUT)

#define CONTROL NABIJANIE_PB7
#define CONTROL_DDR DDRB |= (1<<CONTROL)
#define CONTROL_LOW PORTB &= ~(1<<CONTROL)
#define CONTROL_HIGH PORTB |= (1<<CONTROL)
#define CONTROL_Z PORTB ^= (1<<CONTROL)

// FUNCTIONS DECLARATION
//======= MAIN =============
int sendCommand(uint8_t);
uint8_t receiveCommand(void);
void settings(void);
void switchOn(void);
void ioInit(void);
void configurationInit(void);
void initSettings(void);
void switchOnCard(void);
// =========================
//======== QUIZ ============
void quizomat(void);

void creditsCoinAcceptorQuizomat(void);
void creditsBillAcceptorQuizomat(void);

//==========================
void endTime(void);

void sendTimeCounter(void);
void sendKeySwitch(void);
//==========================

volatile uint8_t commandBuffer[40], buffer_size;
// ========================================== quiz command =============================================================================

//===========Send
volatile uint8_t com_quiz_start_rules, com_quiz_on, com_switch_on_tetris,
		Counter_IN_1, Counter_IN_2, Counter_IN_5, Counter_IN_10, Counter_IN_25,
		com_attack;

//===========Recive
volatile uint8_t com_round;

//===========================
volatile uint8_t TETRIS_ON, QUIZ_ON;
volatile uint8_t FL_TETRIS_ON, FL_QUIZ_ON, FL_counter_pulses,
		FL_start_rules_counter;

volatile uint16_t counter_pulses, counterTimeout;

volatile uint8_t receive, FLAGA_Send, command, sended;

volatile uint8_t FL_keySwitch, FL_automatOn, FL_pilot,
		FL_protection;
#endif /* MAIN_H_ */
