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
#include "HD44780.h"


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

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

#define HOPPER_5ZL 6
#define HOPPER_1ZL 5
#define HOPPER_50GR 4
#define CONTROLER 1
#define BILL_ACCEPTOR 45
#define COIN_ACCEPTOR 2
#define IO_COMBO 80

void Init_Automat(void);

typedef volatile enum { false, true } bool;

int bufferEq();
void gpioInit();
void Check_Connections(void);

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

uint8_t ccTalk_recive(uint8_t *datarecive,uint8_t from);
////Coin Acceptor
void Check_Money(void);
void Check_inhbit(void);
void Disp_Menu(void);
//IO Board



volatile uint8_t FL_Serwish,FL_KEY_SWITCH,FL_WPBlock;
volatile uint8_t Time_Disp,Expense,BillEvent;
volatile uint16_t Money_In_Automat,Expense_16;




#define NV10ID_NUMBER_1 89
#define NV10ID_NUMBER_2 31
#define NV10ID_NUMBER_3 32
#define NV10ID_NUMBER_4 0

#define X6D2SID_NUMBER_1 161
#define X6D2SID_NUMBER_2 125
#define X6D2SID_NUMBER_3 38


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















void Write_LCD(uint8_t n);
void Write_LCD_String(char * text, uint8_t pos);
void convert_m(uint16_t m);




void Check_IO_Combo(void);
void IO_Combo_Clear_Escrow(void);

uint8_t checkPin(uint16_t pinIn);
void Check_Button_Machine(void);
void Check_IO (uint16_t pinIn,char *text);

void Check_Hopper(void);
uint8_t Hopper_PayOut(uint8_t Count,uint8_t Hopper);

void Check_Coin_Acceptor(void);
void Init_Coin_Acceptor(void);
void Coin_check_buffor(void);

void Check_Bill_Acceptor(void);
void Init_Bill_Acceptor(void);
void Bill_Check_Buffor(void);





#endif /* MAIN_H_ */

