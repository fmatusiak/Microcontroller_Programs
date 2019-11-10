   /*
 * main.h
 *
 *  Created on: 23 mar 2015
 *      Author: Arek Trojanowski
 */

#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#define RS_BAUD 9600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "stdlib.h"

#define TIMER0_ON TCCR0 |= (1<<CS00) | (1<<CS01)
#define TIMER0_OFF TCCR0 = 0x00
#define REF_VCC (1<<REFS0)
#define BIT_DELAY 20
#define FRAME_DELAY 40
#define CREDIT_DELAY 200
#define CREDITHS_DELAY 100
#define RS_UBRR 103

// INS



#define DDR_RX DDRD &= ~(_BV(RX))
#define PIN_RX PIND & _BV(RX)
#define RX_VCC PORTD |= _BV(RX)
#define RX_GND PORTD &= ~_BV(RX)
#define RX PD0

#define DDR_IN1 DDRC &= ~(_BV(IN1))
#define PIN_IN1 PINC & _BV(IN1)
#define IN1_VCC PORTC |= _BV(IN1)
#define IN1_GND PORTC &= ~_BV(IN1)
#define IN1 PC4

#define DDR_IN2 DDRC &= ~(_BV(IN2))
#define PIN_IN2 PINC & _BV(IN2)
#define IN2_VCC PORTC |= _BV(IN2)
#define IN2_GND PORTC &= ~_BV(IN2)
#define IN2 PC5

#define DDR_IN3 DDRC &= ~(_BV(IN3))
#define PIN_IN3 PINC & _BV(IN3)
#define IN3_VCC PORTC |= _BV(IN3)
#define IN3_GND PORTC &= ~_BV(IN3)
#define IN3 PC6

#define DDR_IN4 DDRC &= ~(_BV(IN4))
#define PIN_IN4 PINC & _BV(IN4)
#define IN4_VCC PORTC |= _BV(IN4)
#define IN4_GND PORTC &= ~_BV(IN4)
#define IN4 PC7

#define DDR_IN5 DDRB &= ~(_BV(IN5))
#define PIN_IN5 PINB & _BV(IN5)
#define IN5_VCC PORTB |= _BV(IN5)
#define IN5_GND PORTB &= ~_BV(IN5)
#define IN5 PB0

// outy

#define DDR_OUT1 DDRC |= _BV(OUT1)
#define PORT_OUT1_0 PORTC &= ~(_BV(OUT1))
#define PORT_OUT1_1 PORTC |= _BV(OUT1)
#define OUT1 PC0

#define DDR_OUT2 DDRC |= _BV(OUT2)
#define PORT_OUT2_0 PORTC &= ~(_BV(OUT2))
#define PORT_OUT2_1 PORTC |= _BV(OUT2)
#define OUT2 PC1

#define DDR_OUT3 DDRC |= _BV(OUT3)
#define PORT_OUT3_0 PORTC &= ~(_BV(OUT3))
#define PORT_OUT3_1 PORTC |= _BV(OUT3)
#define OUT3 PC2

#define DDR_OUT4 DDRC |= _BV(OUT4)
#define PORT_OUT4_0 PORTC &= ~(_BV(OUT4))
#define PORT_OUT4_1 PORTC |= _BV(OUT4)
#define OUT4 PC3

#define DDR_OUT5 DDRA |= _BV(OUT5)
#define PORT_OUT5_0 PORTA &= ~(_BV(OUT5))
#define PORT_OUT5_1 PORTA |= _BV(OUT5)
#define OUT5 PA0


// dodatkowe
#define BARMAN_35_PA2 PA2 // p2
#define ON_MACHINE_IN BARMAN_35_PA2
#define DDR_ON_MACHINE_IN DDRA &= ~(1<<ON_MACHINE_IN)
#define PIN_ON_MACHINE_IN PINA & _BV(ON_MACHINE_IN)
#define ON_MACHINE_IN_VCC PORTA |= _BV(ON_MACHINE_IN)
#define ON_MACHINE_IN_GND PORTA &= ~_BV(ON_MACHINE_IN)

#define HS_ON_OFF_PA1 PA1
#define PILOT_IN HS_ON_OFF_PA1
#define DDR_PILOT_IN DDRA &= ~(1<<PILOT_IN)
#define PIN_PILOT_IN PINA & _BV(PILOT_IN)
#define PILOT_IN_VCC PORTA |= _BV(PILOT_IN)
#define PILOT_IN_GND PORTA &= ~_BV(PILOT_IN)

#define CARD_IN PA3
#define DDR_CARD_IN DDRA &= ~(1<<CARD_IN)
#define PIN_CARD_IN PINA & _BV(CARD_IN)
#define CARD_IN_VCC PORTA |= _BV(CARD_IN)
#define CARD_IN_GND PORTA &= ~_BV(CARD_IN)


#define STAC_IN PA5	// Drzwi
#define STAC_IN_DDR DDRA &= ~(1<<STAC_IN)
#define STAC_IN_VCC PORTA |= (1<<STAC_IN) // ok
#define STAC_IN_HIGH PINA & (1<<STAC_IN) // ok
#define STAC_IN_LOW !(PINA & (1<<STAC_IN))

#define PI_IN PB1	// Drzwi
#define PI_IN_DDR DDRB &= ~(1<<PI_IN)
#define PI_IN_VCC PORTB |= (1<<PI_IN) // ok
#define PI_IN_HIGH PINB & (1<<PI_IN) // ok
#define PI_IN_LOW !(PINB & (1<<PI_IN))


#define DWA PA4	// Drzwi
#define DWA_DDR DDRA &= ~(1<<DWA)
#define DWA_VCC PORTA |= (1<<DWA) // ok
#define DWA_HIGH PINA & (1<<DWA) // ok
#define DWA_LOW !(PINA & (1<<DWA))





#define RASP_CREDIT PB3
#define RASP_CREDIT_DDR DDRB |= (1<<RASP_CREDIT) // ok
#define RASP_CREDIT_LOW PORTB &= ~(1<<RASP_CREDIT) // ok
#define RASP_CREDIT_HIGH PORTB |= (1<<RASP_CREDIT)

#define RASP_CONF PB2
#define RASP_CONF_DDR DDRB |= (1<<RASP_CONF)
#define RASP_CONF_LOW PORTB &= ~(1<<RASP_CONF) //ok
#define RASP_CONF_HIGH PORTB|= (1<<RASP_CONF)

#define WBA_RESET PD5
#define WBA_RESET_DDR DDRD |= (1<<WBA_RESET)
#define WBA_RESET_LOW PORTD &= ~(1<<WBA_RESET) // ok
#define WBA_RESET_HIGH PORTD |= (1<<WBA_RESET) // ok

#define WBA_V12 PD6
#define WBA_V12_DDR DDRD |= (1<<WBA_V12)
#define WBA_V12_LOW PORTD &= ~(1<<WBA_V12) // ok
#define WBA_V12_HIGH PORTD |= (1<<WBA_V12) // ok

#define WBA_SWITCH PD4
#define WBA_SWITCH_DDR DDRD |= (1<<WBA_SWITCH)
#define WBA_SWITCH_LOW PORTD &= ~(1<<WBA_SWITCH) // ok
#define WBA_SWITCH_HIGH PORTD |= (1<<WBA_SWITCH) // ok



#define VGA_SWITCH PB4
#define VGA_SWITCH_DDR DDRB |= (1<<VGA_SWITCH)
#define VGA_SWITCH_LOW PORTB &= ~(1<<VGA_SWITCH) // ok
#define VGA_SWITCH_HIGH PORTB |= (1<<VGA_SWITCH) // ok

#define BUTTONS PA0
#define BUTTONS_DDR DDRA |= (1<<BUTTONS)
#define BUTTONS_LOW PORTA &= ~(1<<BUTTONS) // ok
#define BUTTONS_HIGH PORTA |= (1<<BUTTONS) // ok

#define V12 PD7
#define V12_DDR DDRD |= (1<<V12)
#define V12_LOW PORTD &= ~(1<<V12) // ok
#define V12_HIGH PORTD |= (1<<V12) // ok

// FUNCTIONS DECLARATION

void sendDataFrame(void);
void addRaspCredits(uint8_t);
void addHsCredits(uint8_t);
uint16_t adcConversion(uint8_t);
uint8_t potxConversion(uint16_t);
uint8_t potyConversion(uint16_t);
void config(void);
uint8_t uart_getc(void);
uint8_t uartIsChar(void);
void uart_putc(uint8_t);
void uartPutData(uint8_t, uint8_t*);
void turnOnRasp(void);

// GLOBAL VARIABLES

volatile uint8_t timeX = 0;
volatile uint8_t timeY = 0;
volatile uint16_t counter = 0;
volatile uint8_t potX = 0;
volatile uint8_t potY = 0;
volatile char timeXRunOut = 0;
volatile int dataFrame[13];
volatile uint8_t uart = 0;
volatile char hotSpotOn = 0;

volatile  uint16_t tempxResult = 0, tempyResult = 1;

#endif /* MAIN_H_ */
