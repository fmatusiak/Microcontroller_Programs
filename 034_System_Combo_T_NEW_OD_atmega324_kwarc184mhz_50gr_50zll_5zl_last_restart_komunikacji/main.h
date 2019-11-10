// 6 in lcd
// 2 in coins
// 2 in buttons
// 1 in switch
#ifndef MAIN_H_
#define MAIN_H_

// 2 out control

// 1 cctalk
#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "Hopper.h"
#include "HD44780.h"
#include "IO_Button.h"
#include "IO_Combo.h"
#include "BillAcceptor.h"
#include "CoinAcceptor.h"
#include <avr/pgmspace.h>
#include "LCD.h"


#define BUTTON_1_IN PB1//SW
#define DDR_BUTTON_1_IN DDRB &= ~(1<<BUTTON_1_IN)
#define PIN_BUTTON_1_IN PINB & _BV(BUTTON_1_IN)
#define BUTTON_1_IN_VCC PORTB |= _BV(BUTTON_1_IN)
#define BUTTON_1_IN_GND PORTB &= ~_BV(BUTTON_1_IN)

#define BUTTON_2_IN PB2//SW
#define DDR_BUTTON_2_IN DDRB &= ~(1<<BUTTON_2_IN)
#define PIN_BUTTON_2_IN PINB & _BV(BUTTON_2_IN)
#define BUTTON_2_IN_VCC PORTB |= _BV(BUTTON_2_IN)
#define BUTTON_21_IN_GND PORTB &= ~_BV(BUTTON_1_IN)

#define BUTTON_3_IN PB3//SW
#define DDR_BUTTON_3_IN DDRB &= ~(1<<BUTTON_3_IN)
#define PIN_BUTTON_3_IN PINB & _BV(BUTTON_3_IN)
#define BUTTON_3_IN_VCC PORTB |= _BV(BUTTON_3_IN)
#define BUTTON_3_IN_GND PORTB &= ~_BV(BUTTON_3_IN)

#define KEY_SWITCH_ADMIN_IN PC5//I2C
#define DDR_KEY_SWITCH_ADMIN_IN DDRC &= ~(1<<KEY_SWITCH_ADMIN_IN)
#define PIN_KEY_SWITCH_ADMIN_IN PINC & _BV(KEY_SWITCH_ADMIN_IN)
#define KEY_SWITCH_ADMIN_IN_VCC PORTC |= _BV(KEY_SWITCH_ADMIN_IN)
#define KEY_SWITCH_ADMIN_IN_GND PORTC &= ~_BV(KEY_SWITCH_ADMIN_IN)

#define KEY_SWITCH_SERWIS_IN PC4//I2C
#define DDR_KEY_SWITCH_SERWIS_IN DDRC &= ~(1<<KEY_SWITCH_SERWIS_IN)
#define PIN_KEY_SWITCH_SERWIS_IN PINC & _BV(KEY_SWITCH_SERWIS_IN)
#define KEY_SWITCH_SERWIS_IN_VCC PORTC |= _BV(KEY_SWITCH_SERWIS_IN)
#define KEY_SWITCH_SERWIS_IN_GND PORTC &= ~_BV(KEY_SWITCH_SERWIS_IN)

// ========================================================================================================

#define RELAY_1_OUT PD5 //Hopper 2
#define RELAY_1_OUT_DDR DDRD |= (1<<RELAY_1_OUT)
#define RELAY_1_OUT_LOW PORTD &= ~(1<<RELAY_1_OUT)
#define RELAY_1_OUT_HIGH PORTD |= (1<<RELAY_1_OUT)
#define RELAY_1_OUT_Z PORTD ^= (1<<RELAY_1_OUT)

#define RELAY_2_OUT PD4 //Hopper 2
#define RELAY_2_OUT_DDR DDRD |= (1<<RELAY_2_OUT)
#define RELAY_2_OUT_LOW PORTD &= ~(1<<RELAY_2_OUT)
#define RELAY_2_OUT_HIGH PORTD |= (1<<RELAY_2_OUT)
#define RELAY_2_OUT_Z PORTD ^= (1<<RELAY_2_OUT)

#define RELAY_3_OUT PD3 //Hopper 2
#define RELAY_3_OUT_DDR DDRD |= (1<<RELAY_3_OUT)
#define RELAY_3_OUT_LOW PORTD &= ~(1<<RELAY_3_OUT)
#define RELAY_3_OUT_HIGH PORTD |= (1<<RELAY_3_OUT)
#define RELAY_3_OUT_Z PORTD ^= (1<<RELAY_3_OUT)

#define HPOW_OUT PB4 //Hopper 2
#define HPOW_OUT_DDR DDRB |= (1<<HPOW_OUT)
#define HPOW_OUT_LOW PORTB &= ~(1<<HPOW_OUT)
#define HPOW_OUT_HIGH PORTB |= (1<<HPOW_OUT)
#define HPOW_OUT_Z PORTB ^= (1<<HPOW_OUT)

//-----------------------------------------------------------------------------

//#define false 0
//#define true 1

#define F_CPU 18432000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 119


void Init_Automat(void);

typedef volatile enum {
	false, true
} bool;

int bufferEq();
void gpioInit();
void Check_Connections(void);
void Init_Dev(void);

/////Uart
void uart_init(uint16_t ubrr);
void uart_putc(uint8_t data);
uint8_t uart_getc(void);
uint8_t uart_ischar(void);
void uart_clear(void);
////LCD

/////Bill Acceptor
void ccTalk_send(uint8_t from, uint8_t dataCount, uint8_t command,
		uint8_t *data);

uint8_t ccTalk_recive(uint8_t *datarecive, uint8_t from);
uint8_t ccTalk_recive_no_timeout(uint8_t *datarecive, uint8_t from);
uint8_t uart_getc_no_timeout(void) ;
////Coin Acceptor
void Check_Money(void);
void Check_inhbit(void);
void Disp_Menu(void);
void StanVar(void);
//IO Board
void Init_EEProm(void);
void Save_Money_Hopper(void);
void Check_Admin(void);
void Check_Admin_Start(void);
void Set_Open_Door(void);
void Check_Time_Out_Money(void);
void error_payout(void);
uint8_t RNG(void);
void Check_Button_Door(void);

volatile uint8_t FL_Serwish, FL_Adminh, FL_WPBlock, SterWhile, Hopper_One_Opto,
		Hopper_Two_Opto,Hopper_Three_Opto,FL_Blocked;
volatile uint8_t Time_Disp, BillEvent, CoinEvent, FL_Button_1, FL_Button_2,
		FL_Button_3, FL_Restart,FL_KEY_SWITCH, Tmp_Time_Door,Door_One,Door_Two,Door_Three,Time_out_Money;
volatile uint16_t Money_In_Automat,Last_Transaction_Atmega,Last_Money_In;

volatile uint8_t Expense_Atmega,First_Run_Atmega,First_Run,FL_ERROR,FL_Dead_Comm;
volatile uint16_t Money_5zl_Atmega, Money_1zl_Atmega, Money_50gr_Atmega;
volatile 	uint8_t Stan_Hopper,Inhibit_Coin,FL_Cena_UP;
volatile uint32_t Seed_RNG;
volatile uint8_t FL_Key_One,FL_Key_Two,FL_Key_Three;

volatile uint8_t licznik_error;


#define Seed_RNG_A 22695477
#define Seed_RNG_C 1
#define TIME_OUT_MONEY 220
#define IS_TIME_OUT 1

#define HOPPER_5ZL 6
#define HOPPER_1ZL 5
#define HOPPER_50GR 4
#define CONTROLER 1
#define BILL_ACCEPTOR 45
#define COIN_ACCEPTOR 2
#define IO_COMBO 80


#define NV10ID_NUMBER_1 0//89/0
#define NV10ID_NUMBER_2 66//31/66
#define NV10ID_NUMBER_3 11//32/11
#define NV10ID_NUMBER_4 170//0

#define X6D2SID_NUMBER_1 72//101
#define X6D2SID_NUMBER_2 12//187
#define X6D2SID_NUMBER_3 41//28

#define HOPPER5ID_NUMBER_1 110
#define HOPPER5ID_NUMBER_2 53
#define HOPPER5ID_NUMBER_3 26

#define HOPPER1ID_NUMBER_1 104
#define HOPPER1ID_NUMBER_2 53
#define HOPPER1ID_NUMBER_3 26

#define HOPPER50ID_NUMBER_1 103
#define HOPPER50ID_NUMBER_2 53
#define HOPPER50ID_NUMBER_3 26

#define IOCOMBOID_NUMBER_ 0

#endif /* MAIN_H_ */

