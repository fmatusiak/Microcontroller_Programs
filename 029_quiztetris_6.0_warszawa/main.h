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

#define IN1_23_PC4 PC4
#define IN2_24_PC5 PC5
#define IN3_25_PC6 PC6
#define IN4_26_PC7 PC7
#define IN5_40_PB0 PB0
#define HS_ON_OFF_36_PA1 PA1 // p1
#define BARMAN_35_PA2 PA2 // p2
#define DOOR_34_PA3 PA3 //p3
#define WE1_32_PA5 PA5 // stac in
#define RX_DO_RP_41_PB1 PB1 // pi in
#define WE2_33_PA4 PA4 // dwa
#define RX2_11_PD2 PD2 // dwa
// OUTS
#define OUT1_19_PC0 PC0
#define OUT2_20_PC1 PC1
#define OUT3_21_PC2 PC2
#define OUT4_22_PC3 PC3
#define OUT5_37_PA0 PA0
#define NABIJANIE_43_PB3 PB3
#define TX_DO_RP_42_PB2 PB2 //rasp_conf
#define WBA_RES_14_PD5 PD5 // wba reset
#define WBA12V_15_PD6 PD6
#define WBA_PRZE_13_PD4 PD4 // wba switch
#define PRZEL_VGA_44_PB4 PB4 // vga switch
#define JP_SCREEN_SWITCH_PB5 PB5
#define V12_OUT_16_PD7 PD7
#define TX2_12_PD3 PD3
#define HS_ON_OFF_PA1 PA1
#define TX1_12_PD3 PD3

// =============================

// ==============================================================================
// ================================== IN PROGRAM ================================
// INS
#define READ_PI_IN	RX_DO_RP_41_PB1
#define DDR_READ_PI_IN DDRB &= ~(1<<READ_PI_IN)
#define PIN_READ_PI_IN PINB & _BV(READ_PI_IN)
#define READ_PI_IN_VCC PORTB |= _BV(READ_PI_IN)
#define READ_PI_IN_GND PORTB &= ~_BV(READ_PI_IN)

#define CARD_IN DOOR_34_PA3
#define DDR_CARD_IN DDRA &= ~(1<<CARD_IN)
#define PIN_CARD_IN PINA & _BV(CARD_IN)
#define CARD_IN_VCC PORTA |= _BV(CARD_IN)
#define CARD_IN_GND PORTA &= ~_BV(CARD_IN)

#define BUTTON_BUTTON_IN RX2_11_PD2
#define DDR_BUTTON_BUTTON_IN DDRD &= ~(1<<BUTTON_BUTTON_IN)
#define PIN_BUTTON_BUTTON_IN PIND & _BV(BUTTON_BUTTON_IN)
#define BUTTON_BUTTON_IN_VCC PORTD |= _BV(BUTTON_BUTTON_IN)
#define BUTTON_BUTTON_IN_GND PORTD &= ~_BV(BUTTON_BUTTON_IN)

#define BET_BUTTON_IN IN1_23_PC4
#define DDR_BET_BUTTON_IN DDRC &= ~(1<<BET_BUTTON_IN)
#define PIN_BET_BUTTON_IN PINC & _BV(BET_BUTTON_IN)
#define BET_BUTTON_IN_VCC PORTC |= _BV(BET_BUTTON_IN)
#define BET_BUTTON_IN_GND PORTC &= ~_BV(BET_BUTTON_IN)

#define HOLD_BUTTON_IN IN2_24_PC5
#define DDR_HOLD_BUTTON_IN DDRC &= ~(1<<HOLD_BUTTON_IN)
#define PIN_HOLD_BUTTON_IN PINC & _BV(HOLD_BUTTON_IN)
#define HOLD_BUTTON_IN_VCC PORTC |= _BV(HOLD_BUTTON_IN)
#define HOLD_BUTTON_IN_GND PORTC &= ~_BV(HOLD_BUTTON_IN)

#define DISPLAY_CHANGE_BUTTON_IN IN3_25_PC6
#define DDR_DISPLAY_CHANGE_BUTTON_IN DDRC &= ~(1<<DISPLAY_CHANGE_BUTTON_IN)
#define PIN_DISPLAY_CHANGE_BUTTON_IN PINC & _BV(DISPLAY_CHANGE_BUTTON_IN)
#define DISPLAY_CHANGE_BUTTON_IN_VCC PORTC |= _BV(DISPLAY_CHANGE_BUTTON_IN)
#define DISPLAY_CHANGE_BUTTON_IN_GND PORTC &= ~_BV(DISPLAY_CHANGE_BUTTON_IN)

#define PAYOUT_BUTTON_IN IN4_26_PC7
#define DDR_PAYOUT_BUTTON_IN DDRC &= ~(1<<PAYOUT_BUTTON_IN)
#define PIN_PAYOUT_BUTTON_IN PINC & _BV(PAYOUT_BUTTON_IN)
#define PAYOUT_BUTTON_IN_VCC PORTC |= _BV(PAYOUT_BUTTON_IN)
#define PAYOUT_BUTTON_IN_GND PORTC &= ~_BV(PAYOUT_BUTTON_IN)

#define PROTECTION_IN IN5_40_PB0
#define DDR_PROTECTION_IN DDRB &= ~(1<<PROTECTION_IN)
#define PIN_PROTECTION_IN PINB & _BV(PROTECTION_IN)
#define PROTECTION_IN_VCC PORTB |= _BV(PROTECTION_IN)
#define PROTECTION_IN_GND PORTB &= ~_BV(PROTECTION_IN)

#define PILOT_IN HS_ON_OFF_PA1
#define DDR_PILOT_IN DDRA &= ~(1<<PILOT_IN)
#define PIN_PILOT_IN PINA & _BV(PILOT_IN)
#define PILOT_IN_VCC PORTA |= _BV(PILOT_IN)
#define PILOT_IN_GND PORTA &= ~_BV(PILOT_IN)

#define KEY_SWITCH_IN WE1_32_PA5
#define DDR_KEY_SWITCH_IN DDRA &= ~(1<<KEY_SWITCH_IN)
#define PIN_KEY_SWITCH_IN PINA & _BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN_VCC PORTA |= _BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN_GND PORTA &= ~_BV(KEY_SWITCH_IN)

#define COUNTER_IN WE2_33_PA4
#define DDR_COUNTER_IN DDRA &= ~(1<<COUNTER_IN)
#define PIN_COUNTER_IN PINA & _BV(COUNTER_IN)
#define COUNTER_IN_VCC PORTA |= _BV(COUNTER_IN)
#define COUNTER_IN_GND PORTA &= ~_BV(COUNTER_IN)

#define ON_MACHINE_IN DOOR_34_PA3
#define DDR_ON_MACHINE_IN DDRA &= ~(1<<ON_MACHINE_IN)
#define PIN_ON_MACHINE_IN PINA & _BV(ON_MACHINE_IN)
#define ON_MACHINE_IN_VCC PORTA |= _BV(ON_MACHINE_IN)
#define ON_MACHINE_IN_GND PORTA &= ~_BV(ON_MACHINE_IN)

// OUTS
#define BUTTON_BUTTON_OUT TX1_12_PD3
#define BUTTON_BUTTON_OUT_DDR DDRD |= (1<<BUTTON_BUTTON_OUT)
#define BUTTON_BUTTON_OUT_LOW PORTD &= ~(1<<BUTTON_BUTTON_OUT)
#define BUTTON_BUTTON_OUT_HIGH PORTD |= (1<<BUTTON_BUTTON_OUT)
#define BUTTON_BUTTON_OUT_Z PORTD ^= (1<<BUTTON_BUTTON_OUT)

#define MUTE_OUT OUT5_37_PA0
#define MUTE_OUT_DDR DDRA |= (1<<OUT5_37_PA0)
#define MUTE_OUT_LOW PORTA &= ~(1<<OUT5_37_PA0)
#define MUTE_OUT_HIGH PORTA |= (1<<OUT5_37_PA0)
#define MUTE_OUT_Z PORTA ^= (1<<OUT5_37_PA0)

#define SEND_PI_OUT TX_DO_RP_42_PB2
#define SEND_PI_OUT_DDR DDRB |= (1<<SEND_PI_OUT)
#define SEND_PI_OUT_LOW PORTB &= ~(1<<SEND_PI_OUT)
#define SEND_PI_OUT_HIGH PORTB |= (1<<SEND_PI_OUT)
#define SEND_PI_OUT_Z PORTB ^= (1<<SEND_PI_OUT)

#define BET_BUTTON_OUT OUT1_19_PC0
#define BET_BUTTON_OUT_DDR DDRC |= (1<<BET_BUTTON_OUT)
#define BET_BUTTON_OUT_LOW PORTC &= ~(1<<BET_BUTTON_OUT)
#define BET_BUTTON_OUT_HIGH PORTC |= (1<<BET_BUTTON_OUT)
#define BET_BUTTON_OUT_Z PORTC ^= (1<<BET_BUTTON_OUT)

#define HOLD_BUTTON_OUT OUT2_20_PC1
#define HOLD_BUTTON_OUT_DDR DDRC |= (1<<HOLD_BUTTON_OUT)
#define HOLD_BUTTON_OUT_LOW PORTC &= ~(1<<HOLD_BUTTON_OUT)
#define HOLD_BUTTON_OUT_HIGH PORTC |= (1<<HOLD_BUTTON_OUT)
#define HOLD_BUTTON_OUT_Z PORTC ^= (1<<HOLD_BUTTON_OUT)

#define PAYOUT_OUT OUT4_22_PC3
#define PAYOUT_OUT_DDR DDRC |= (1<<PAYOUT_OUT)
#define PAYOUT_OUT_LOW PORTC &= ~(1<<PAYOUT_OUT)
#define PAYOUT_OUT_HIGH PORTC |= (1<<PAYOUT_OUT)
#define PAYOUT_OUT_Z PORTC ^= (1<<PAYOUT_OUT)

#define START_OUT OUT3_21_PC2
#define START_OUT_DDR DDRC |= (1<<START_OUT)
#define START_OUT_LOW PORTC &= ~(1<<START_OUT)
#define START_OUT_HIGH PORTC |= (1<<START_OUT)
#define START_OUT_Z PORTC ^= (1<<START_OUT)

#define SCREEN_SWITCH_OUT JP_SCREEN_SWITCH_PB5
#define SCREEN_SWITCH_OUT_DDR DDRB |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_LOW PORTB &= ~(1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_HIGH PORTB |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_Z PORTB ^= (1<<SCREEN_SWITCH_OUT)

#define SWITCH_RELAY PRZEL_VGA_44_PB4
#define SWITCH_RELAY_DDR DDRB |= (1<<SWITCH_RELAY)
#define SWITCH_RELAY_LOW PORTB &= ~(1<<SWITCH_RELAY)
#define SWITCH_RELAY_HIGH PORTB |= (1<<SWITCH_RELAY)
#define SWITCH_RELAY_Z PORTB ^= (1<<SWITCH_RELAY)

#define ALARM V12_OUT_16_PD7
#define ALARM_DDR DDRD |= (1<<ALARM)
#define ALARM_LOW PORTD &= ~(1<<ALARM)
#define ALARM_HIGH PORTD |= (1<<ALARM)
#define ALARM_Z PORTD ^= (1<<ALARM)

#define CONTROL NABIJANIE_43_PB3
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
		com_quiz_start_rules,com_quiz_on,com_switch_on_tetris;

//===========Recive
volatile uint8_t com_unlock_pay, com_lock_pay, com_unlock_BET, com_lock_BET,
		com_round, com_off, com_Relay_ON, com_Relay_OFF, com_unlock_HOLD,
		com_lock_HOLD, com_unlock_Button, com_lock_Button;

//===========================
volatile uint8_t TETRIS_ON, QUIZ_ON;
volatile uint8_t FL_TETRIS_ON, FL_QUIZ_ON;

volatile uint16_t counterTimeout_counter, counter_off, startTimeout,
		startImpulseTime;

volatile uint8_t receive, FLAGA_Send, command, sended;

volatile uint8_t FL_wyk, FL_payout, FL_button, FL_keySwitch, FL_hold, FL_bet,
		FL_automatOn, FL_counter_in, FL_pilotes, FL_start, FL_pilot, FL_CARD;
#endif /* MAIN_H_ */
