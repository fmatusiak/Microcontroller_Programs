#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "Caffe.h"

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
#define PILOT_F_PA1 PA1 // p1
#define PILOT_E_PA2 PA2 // p2
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
#define SCREEN_SWITCH_PB5 PB5
#define V12_OUT_16_PD7 PD7
#define TX2_12_PD3 PD3
#define HS_ON_OFF_PA1 PA1
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

#define PAYOUT_IN IN1_23_PC4
#define DDR_PAYOUT_IN DDRC &= ~(1<<PAYOUT_IN)
#define PIN_PAYOUT_IN PINC & _BV(PAYOUT_IN)
#define PAYOUT_IN_VCC PORTC |= _BV(PAYOUT_IN)
#define PAYOUT_IN_GND PORTC &= ~_BV(PAYOUT_IN)

#define SETTINGS_IN IN2_24_PC5
#define DDR_SETTINGS_IN DDRC &= ~(1<<SETTINGS_IN)
#define PIN_SETTINGS_IN PINC & _BV(SETTINGS_IN)
#define SETTINGS_IN_VCC PORTC |= _BV(SETTINGS_IN)
#define SETTINGS_IN_GND PORTC &= ~_BV(SETTINGS_IN)

#define GIVEMONEY_IN IN3_25_PC6
#define DDR_GIVEMONEY_IN DDRC &= ~(1 << GIVEMONEY_IN )
#define PIN_GIVEMONEY_IN PINC & _BV( GIVEMONEY_IN )
#define GIVEMONEY_IN_VCC PORTC |= _BV( GIVEMONEY_IN )
#define GIVEMONEY_IN_GND PORTC &= ~_BV( GIVEMONEY_IN )

#define SETTINGS_AUTOMAT_IN IN4_26_PC7
#define DDR_SETTINGS_AUTOMAT_IN DDRC &= ~(1<<SETTINGS_AUTOMAT_IN)
#define PIN_SETTINGS_AUTOMAT_IN PINC & _BV(SETTINGS_AUTOMAT_IN)
#define SETTINGS_AUTOMAT_IN_VCC PORTC |= _BV(SETTINGS_AUTOMAT_IN)
#define SETTINGS_AUTOMAT_IN_GND PORTC &= ~_BV(SETTINGS_AUTOMAT_IN)

#define MOTOR_HOPPER_CONTROL_IN IN5_40_PB0
#define DDR_MOTOR_HOPPER_CONTROL_IN DDRB &= ~(1<<MOTOR_HOPPER_CONTROL_IN)
#define PIN_MOTOR_HOPPER_CONTROL_IN PINB & _BV(MOTOR_HOPPER_CONTROL_IN)
#define MOTOR_HOPPER_CONTROL_IN_VCC PORTB |= _BV(MOTOR_HOPPER_CONTROL_IN)
#define MOTOR_HOPPER_CONTROL_IN_GND PORTB &= ~_BV(MOTOR_HOPPER_CONTROL_IN)

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

#define ON_MACHINE_IN DOOR_34_PA3
#define DDR_ON_MACHINE_IN DDRA &= ~(1<<ON_MACHINE_IN)
#define PIN_ON_MACHINE_IN PINA & _BV(ON_MACHINE_IN)
#define ON_MACHINE_IN_VCC PORTA |= _BV(ON_MACHINE_IN)
#define ON_MACHINE_IN_GND PORTA &= ~_BV(ON_MACHINE_IN)

/*---------------------------------------------------------- NEW ----------------------------------------------------------*/
#define PILOT_E_IN PILOT_E_PA2
#define DDR_PILOT_E_IN DDRA &= ~(1 << PILOT_E_IN )
#define PIN_PILOT_E_IN PINA & _BV( PILOT_E_IN )
#define PILOT_E_IN_VCC PORTA |= _BV( PILOT_E_IN )
#define PILOT_E_IN_GND PORTA &= ~_BV( PILOT_E_IN )

#define PILOT_F_IN PILOT_F_PA1
#define DDR_PILOT_F_IN DDRA &= ~(1 << PILOT_F_IN )
#define PIN_PILOT_F_IN PINA & _BV( PILOT_F_IN )
#define PILOT_F_IN_VCC PORTA |= _BV( PILOT_F_IN )
#define PILOT_F_IN_GND PORTA &= ~_BV( PILOT_F_IN )

// OUTS

#define SEND_PI_OUT TX_DO_RP_42_PB2//////////////
#define SEND_PI_OUT_DDR DDRB |= (1<<SEND_PI_OUT)
#define SEND_PI_OUT_LOW PORTB &= ~(1<<SEND_PI_OUT)
#define SEND_PI_OUT_HIGH PORTB |= (1<<SEND_PI_OUT)
#define SEND_PI_OUT_Z PORTB ^= (1<<SEND_PI_OUT)

#define SETTINGS_AUTOMAT_REVERSE_OUT OUT3_21_PC2
#define SETTINGS_AUTOMAT_REVERSE_OUT_DDR DDRC |= (1<<SETTINGS_AUTOMAT_REVERSE_OUT)
#define SETTINGS_AUTOMAT_REVERSE_OUT_LOW PORTC &= ~(1<<SETTINGS_AUTOMAT_REVERSE_OUT)
#define SETTINGS_AUTOMAT_REVERSE_OUT_HIGH PORTC |= (1<<SETTINGS_AUTOMAT_REVERSE_OUT)
#define SETTINGS_AUTOMAT_REVERSE_OUT_Z PORTC ^= (1<<SETTINGS_AUTOMAT_REVERSE_OUT)

#define SETTINGS_AUTOMAT_OUT OUT4_22_PC3
#define SETTINGS_AUTOMAT_OUT_DDR DDRC |= (1<<SETTINGS_AUTOMAT_OUT)
#define SETTINGS_AUTOMAT_OUT_LOW PORTC &= ~(1<<SETTINGS_AUTOMAT_OUT)
#define SETTINGS_AUTOMAT_OUT_HIGH PORTC |= (1<<SETTINGS_AUTOMAT_OUT)
#define SETTINGS_AUTOMAT_OUT_Z PORTC ^= (1<<SETTINGS_AUTOMAT_OUT)

#define HOPPER_PULS_OUT OUT5_37_PA0///////////
#define HOPPER_PULS_OUT_DDR DDRA |= (1<<HOPPER_PULS_OUT)
#define HOPPER_PULS_OUT_LOW PORTA &= ~(1<<HOPPER_PULS_OUT)
#define HOPPER_PULS_OUT_HIGH PORTA |= (1<<HOPPER_PULS_OUT)
#define HOPPER_PULS_OUT_Z PORTA ^= (1<<HOPPER_PULS_OUT)

#define PAYOUT_OUT OUT1_19_PC0//////////
#define PAYOUT_OUT_DDR DDRC |= (1<<PAYOUT_OUT)
#define PAYOUT_OUT_LOW PORTC &= ~(1<<PAYOUT_OUT)
#define PAYOUT_OUT_HIGH PORTC |= (1<<PAYOUT_OUT)
#define PAYOUT_OUT_Z PORTC ^= (1<<PAYOUT_OUT)

#define SCREEN_SWITCH_OUT SCREEN_SWITCH_PB5
#define SCREEN_SWITCH_OUT_DDR DDRB |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_LOW PORTB &= ~(1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_HIGH PORTB |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_Z PORTB ^= (1<<SCREEN_SWITCH_OUT)

#define SWITCH_ON_MACHINE PRZEL_VGA_44_PB4
#define SWITCH_ON_MACHINE_DDR DDRB |= (1<<SWITCH_ON_MACHINE)
#define SWITCH_ON_MACHINE_LOW PORTB &= ~(1<<SWITCH_ON_MACHINE)
#define SWITCH_ON_MACHINE_HIGH PORTB |= (1<<SWITCH_ON_MACHINE)
#define SWITCH_ON_MACHINE_Z PORTB ^= (1<<SWITCH_ON_MACHINE)

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
uint8_t receiveCommand(void);
void switchOn(void);
void ioInit(void);
void configurationInit(void);
// =========================

void Caffe(void);
void Settings(void);
void PayOut(void);
void RunPayOutMode(void);
void Emulate_Hopper(void);
void GetMoney(void);
void Disp_automat(void);
void Hopper_control(void);
void Hopper_down(void);
void Hopper_up(void);

//==========================
void initSettings(void);

volatile uint8_t commandBuffer[50];
volatile uint8_t sended, buffer_size, command, receive, pause;
volatile uint16_t delayCounts;
volatile uint8_t CAFFE_ON, FL_Hopper_time;

volatile uint8_t com_caffe_on, com_off_value, com_start_automat, com_disp;
volatile uint8_t com_caffe_is, com_payout, com_payout_button, com_money_one,
		com_money_two, com_money_five, com_money_ten, com_key_switch,
		com_nabijKredyt, com_money_twenty, com_money_fifty, com_money_hundred,
		com_pilot_e, com_pilot_f;
volatile uint8_t FL_pilotes, FL_start, FL_automatOn, FLAGA_Send, FL_Caffe,
		FL_PILOT_E, FL_PILOT_F;

/////////////////////caffe
//volatile uint8_t FL_keySwitch,FL_PAYOUT,FL_START_PAYOUT,FL_HOPPER,money_pulses;
//volatile uint16_t Tmp_time_payout,time_hopper,Tmp_time_hopper_high,Tmp_time_hopper_low,FL_Hopper_DOWN ,FL_Hopper_UP;

#endif /* MAIN_H_ */
