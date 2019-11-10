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


#define DOOR_PB4 PB4 //p3
#define WE1_PC2 PC2 // stac in
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

#define CARD_IN DOOR_PB4
#define DDR_CARD_IN DDRB &= ~(1<<CARD_IN)
#define PIN_CARD_IN PINB & _BV(CARD_IN)
#define CARD_IN_VCC PORTB |= _BV(CARD_IN)
#define CARD_IN_GND PORTB &= ~_BV(CARD_IN)

#define BUTTON_BUTTON_IN IN2_PA2
#define DDR_BUTTON_BUTTON_IN DDRA &= ~(1<<BUTTON_BUTTON_IN)
#define PIN_BUTTON_BUTTON_IN PINA & _BV(BUTTON_BUTTON_IN)
#define BUTTON_BUTTON_IN_VCC PORTA |= _BV(BUTTON_BUTTON_IN)
#define BUTTON_BUTTON_IN_GND PORTA &= ~_BV(BUTTON_BUTTON_IN)

#define BET_BUTTON_IN IN1_PA3
#define DDR_BET_BUTTON_IN DDRA &= ~(1<<BET_BUTTON_IN)
#define PIN_BET_BUTTON_IN PINA & _BV(BET_BUTTON_IN)
#define BET_BUTTON_IN_VCC PORTA |= _BV(BET_BUTTON_IN)
#define BET_BUTTON_IN_GND PORTA &= ~_BV(BET_BUTTON_IN)

#define HOLD_BUTTON_IN IN5_PA4
#define DDR_HOLD_BUTTON_IN DDRA &= ~(1<<HOLD_BUTTON_IN)
#define PIN_HOLD_BUTTON_IN PINA & _BV(HOLD_BUTTON_IN)
#define HOLD_BUTTON_IN_VCC PORTA |= _BV(HOLD_BUTTON_IN)
#define HOLD_BUTTON_IN_GND PORTA &= ~_BV(HOLD_BUTTON_IN)

#define PAYOUT_BUTTON_IN IN4_PA0
#define DDR_PAYOUT_BUTTON_IN DDRA &= ~(1<<PAYOUT_BUTTON_IN)
#define PIN_PAYOUT_BUTTON_IN PINA & _BV(PAYOUT_BUTTON_IN)
#define PAYOUT_BUTTON_IN_VCC PORTA |= _BV(PAYOUT_BUTTON_IN)
#define PAYOUT_BUTTON_IN_GND PORTA &= ~_BV(PAYOUT_BUTTON_IN)

#define PILOT_IN IN3_PA1
#define DDR_PILOT_IN DDRA &= ~(1<<PILOT_IN)
#define PIN_PILOT_IN PINA & _BV(PILOT_IN)
#define PILOT_IN_VCC PORTA |= _BV(PILOT_IN)
#define PILOT_IN_GND PORTA &= ~_BV(PILOT_IN)

#define KEY_SWITCH_IN WE1_PC2
#define DDR_KEY_SWITCH_IN DDRC &= ~(1<<KEY_SWITCH_IN)
#define PIN_KEY_SWITCH_IN PINC & _BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN_VCC PORTC |= _BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN_GND PORTC &= ~_BV(KEY_SWITCH_IN)

#define COUNTER_IN WE2_PC1
#define DDR_COUNTER_IN DDRC &= ~(1<<COUNTER_IN)
#define PIN_COUNTER_IN PINC & _BV(COUNTER_IN)
#define COUNTER_IN_VCC PORTC |= _BV(COUNTER_IN)
#define COUNTER_IN_GND PORTC &= ~_BV(COUNTER_IN)

#define ON_MACHINE_IN DOOR_PB4
#define DDR_ON_MACHINE_IN DDRB &= ~(1<<ON_MACHINE_IN)
#define PIN_ON_MACHINE_IN PINB & _BV(ON_MACHINE_IN)
#define ON_MACHINE_IN_VCC PORTB |= _BV(ON_MACHINE_IN)
#define ON_MACHINE_IN_GND PORTB &= ~_BV(ON_MACHINE_IN)

// OUTS
#define BUTTON_BUTTON_OUT OUT2_PC7
#define BUTTON_BUTTON_OUT_DDR DDRC |= (1<<BUTTON_BUTTON_OUT)
#define BUTTON_BUTTON_OUT_LOW PORTC &= ~(1<<BUTTON_BUTTON_OUT)
#define BUTTON_BUTTON_OUT_HIGH PORTC |= (1<<BUTTON_BUTTON_OUT)
#define BUTTON_BUTTON_OUT_Z PORTC ^= (1<<BUTTON_BUTTON_OUT)

#define MUTE_OUT MUTE_OFF_PC4
#define MUTE_OUT_DDR DDRC |= (1<<MUTE_OUT)
#define MUTE_OUT_LOW PORTC &= ~(1<<MUTE_OUT)
#define MUTE_OUT_HIGH PORTC |= (1<<MUTE_OUT)
#define MUTE_OUT_Z PORTC ^= (1<<MUTE_OUT)

#define SEND_PI_OUT TX_DO_RP_PD1
#define SEND_PI_OUT_DDR DDRD |= (1<<SEND_PI_OUT)
#define SEND_PI_OUT_LOW PORTD &= ~(1<<SEND_PI_OUT)
#define SEND_PI_OUT_HIGH PORTD |= (1<<SEND_PI_OUT)
#define SEND_PI_OUT_Z PORTD ^= (1<<SEND_PI_OUT)

#define BET_BUTTON_OUT OUT1_PC6
#define BET_BUTTON_OUT_DDR DDRC |= (1<<BET_BUTTON_OUT)
#define BET_BUTTON_OUT_LOW PORTC &= ~(1<<BET_BUTTON_OUT)
#define BET_BUTTON_OUT_HIGH PORTC |= (1<<BET_BUTTON_OUT)
#define BET_BUTTON_OUT_Z PORTC ^= (1<<BET_BUTTON_OUT)

#define HOLD_BUTTON_OUT OUT5_PA5
#define HOLD_BUTTON_OUT_DDR DDRA |= (1<<HOLD_BUTTON_OUT)
#define HOLD_BUTTON_OUT_HIGH PORTA |= (1<<HOLD_BUTTON_OUT)
#define HOLD_BUTTON_OUT_LOW PORTA &= ~(1<<HOLD_BUTTON_OUT)
#define HOLD_BUTTON_OUT_Z PORTA ^= (1<<HOLD_BUTTON_OUT)

#define PAYOUT_OUT OUT4_PA6
#define PAYOUT_OUT_DDR DDRA |= (1<<PAYOUT_OUT)
#define PAYOUT_OUT_LOW PORTA &= ~(1<<PAYOUT_OUT)
#define PAYOUT_OUT_HIGH PORTA |= (1<<PAYOUT_OUT)
#define PAYOUT_OUT_Z PORTA ^= (1<<PAYOUT_OUT)

#define START_OUT OUT3_PA7
#define START_OUT_DDR DDRA |= (1<<START_OUT)
#define START_OUT_LOW PORTA &= ~(1<<START_OUT)
#define START_OUT_HIGH PORTA |= (1<<START_OUT)
#define START_OUT_Z PORTA ^= (1<<START_OUT)

#define SCREEN_SWITCH_OUT JP_SCREEN_SWITCH_PD4
#define SCREEN_SWITCH_OUT_DDR DDRD |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_LOW PORTD &= ~(1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_HIGH PORTD |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_Z PORTD ^= (1<<SCREEN_SWITCH_OUT)

#define SWITCH_RELAY PRZEL_VGA_PB2
#define SWITCH_RELAY_DDR DDRB |= (1<<SWITCH_RELAY)
#define SWITCH_RELAY_LOW PORTB &= ~(1<<SWITCH_RELAY)
#define SWITCH_RELAY_HIGH PORTB |= (1<<SWITCH_RELAY)
#define SWITCH_RELAY_Z PORTB ^= (1<<SWITCH_RELAY)

#define CONTROL NABIJANIE_PB7
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
//void checkQuizPayout(void);
void checkCounter(void);
void quizomat(void);
//==========================
void endTime(void);
void switchOnCard(void);
void sendTimeCounter(void);
void sendKeySwitch(void);
//==========================
void configurationInit(void);
void initSettings(void);

volatile uint8_t commandBuffer[40], buffer_size;
// ========================================== quiz command =============================================================================

//===========Send
volatile uint8_t klik_payout, key_switch_clear, com_add_time_one,
		com_quiz_start_rules, com_quiz_on, com_switch_on_tetris, klik_podglad,
		klik_stawka, Counter_IN_1, Counter_IN_2, Counter_IN_5, Counter_IN_10,
		Counter_IN_25;

//===========Recive
volatile uint8_t com_unlock_pay, com_unlock_BET, com_round, com_off,
		com_Relay_ON, com_unlock_HOLD, com_unlock_Button, com_disp_ON;

//===========================
volatile uint8_t TETRIS_ON, QUIZ_ON;
volatile uint8_t FL_TETRIS_ON, FL_QUIZ_ON;

volatile uint16_t counter_pulses;

volatile uint16_t counterTimeout_counter, counter_off, startTimeout,
		startImpulseTime,counterTimeout_counter_OUT;

volatile uint8_t receive, FLAGA_Send, command, sended;

volatile uint8_t FL_wyk, FL_payout, FL_button, FL_keySwitch, FL_hold, FL_bet,
		FL_automatOn, FL_counter_in, FL_pilotes, FL_start, FL_pilot, FL_CARD,
		FL_wyk_byt, FL_wyk_hold;
#endif /* MAIN_H_ */
