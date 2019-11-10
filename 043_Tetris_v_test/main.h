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



#define HS_ON_OFF_PA4 PA4
#define DOOR_PA6 PA6
#define WE1_PA7 PA7
#define WE2_PC7 PC7 // dwa
#define RX2_PA0 PA0 // dwa
#define RX_DO_RP_PD0 PD0 // pi in


// OUTS




#define NABIJANIE_PB5 PB5
#define TX_DO_RP_PD1 PD1 //rasp_conf
// =============================

// ==============================================================================
// ================================== IN PROGRAM ================================
// INS

#define IN1_PC3 PC3
#define DDR_IN1_PC3 DDRC &= ~(1<<IN1_PC3)
#define PIN_IN1_PC3 PINC & _BV(IN1_PC3)
#define IN1_PC3_VCC PORTC |= _BV(IN1_PC3)
#define IN1_PC3_GND PORTC &= ~_BV(IN1_PC3)

#define IN2_PC4 PC4
#define DDR_IN2_PC4 DDRC &= ~(1<<IN2_PC4)
#define PIN_IN2_PC4 PINC & _BV(IN2_PC4)
#define IN2_PC4_VCC PORTC |= _BV(IN2_PC4)
#define IN2_PC4_GND PORTC &= ~_BV(IN2_PC4)

#define IN3_PC5 PC5
#define DDR_IN3_PC5 DDRC &= ~(1<<IN3_PC5)
#define PIN_IN3_PC5 PINC & _BV(IN3_PC5)
#define IN3_PC5_VCC PORTC |= _BV(IN3_PC5)
#define IN3_PC5_GND PORTC &= ~_BV(IN3_PC5)

#define IN4_PC6 PC6
#define DDR_IN4_PC6 DDRC &= ~(1<<IN4_PC6)
#define PIN_IN4_PC6 PINC & _BV(IN4_PC6)
#define IN4_PC6_VCC PORTC |= _BV(IN4_PC6)
#define IN4_PC6_GND PORTC &= ~_BV(IN4_PC6)

#define IN5_PC2 PC2
#define DDR_IN5_PC2 DDRC &= ~(1<<IN5_PC2)
#define PIN_IN5_PC2 PINC & _BV(IN5_PC2)
#define IN5_PC2_VCC PORTC |= _BV(IN5_PC2)
#define IN5_PC2_GND PORTC &= ~_BV(IN5_PC2)

#define IN6_PD2 PD2
#define DDR_IN6_PD2 DDRD &= ~(1<<IN6_PD2)
#define PIN_IN6_PD2 PIND & _BV(IN6_PD2)
#define IN6_PD2_VCC PORTD |= _BV(IN6_PD2)
#define IN6_PD2_GND PORTD &= ~_BV(IN6_PD2)

#define IN7_PA2 PA2
#define DDR_IN7_PA2 DDRA &= ~(1<<IN7_PA2)
#define PIN_IN7_PA2 PINA & _BV(IN7_PA2)
#define IN7_PA2_VCC PORTA |= _BV(IN7_PA2)
#define IN7_PA2_GND PORTA &= ~_BV(IN7_PA2)

#define IN8_PA0 PA0
#define DDR_IN8_PA0 DDRA &= ~(1<<IN8_PA0)
#define PIN_IN8_PA0 PINA & _BV(IN8_PA0)
#define IN8_PA0_VCC PORTA |= _BV(IN8_PA0)
#define IN8_PA0_GND PORTA &= ~_BV(IN8_PA0)

#define IN9_PB3 PB3
#define DDR_IN9_PB3 DDRB &= ~(1<<IN9_PB3)
#define PIN_IN9_PB3 PINB & _BV(IN9_PB3)
#define IN9_PB3_VCC PORTB |= _BV(IN9_PB3)
#define IN9_PB3_GND PORTB &= ~_BV(IN9_PB3)

#define IN10_PA6 PA6
#define DDR_IN10_PA6 DDRA &= ~(1<<IN10_PA6)
#define PIN_IN10_PA6 PINA & _BV(IN10_PA6)
#define IN10_PA6_VCC PORTA |= _BV(IN10_PA6)
#define IN10_PA6_GND PORTA &= ~_BV(IN10_PA6)

#define IN11_PA4 PA4
#define DDR_IN11_PA4 DDRA &= ~(1<<IN11_PA4)
#define PIN_IN11_PA4 PINA & _BV(IN11_PA4)
#define IN11_PA4_VCC PORTA |= _BV(IN11_PA4)
#define IN11_PA4_GND PORTA &= ~_BV(IN11_PA4)

#define IN12_PA5 PA5
#define DDR_IN12_PA5 DDRA &= ~(1<<IN12_PA5)
#define PIN_IN12_PA5 PINA & _BV(IN12_PA5)
#define IN12_PA5_VCC PORTA |= _BV(IN12_PA5)
#define IN12_PA5_GND PORTA &= ~_BV(IN12_PA5)

/*
#define PC1WE_PA7 PA7//zmiana 7
#define DDR_PC1WE_PA7 DDRA &= ~(1<<PC1WE_PA7)
#define PIN_PC1WE_PA7 PINA & _BV(PC1WE_PA7)
#define PC1WE_PA7_VCC PORTA |= _BV(PC1WE_PA7)
#define PC1WE_PA7_GND PORTA &= ~_BV(PC1WE_PA7)

#define PC2WE_PC7 PC7//zmiana 7
#define DDR_PC2WE_PC7 DDRC &= ~(1<<PC2WE_PC7)
#define PIN_PC2WE_PC7 PINC & _BV(PC2WE_PC7)
#define PC2WE_PC7_VCC PORTC |= _BV(PC2WE_PC7)
#define PC2WE_PC7_GND PORTC &= ~_BV(PC2WE_PC7)
*/

#define RX_PD0 PD0
#define DDR_RX_PD0 DDRD &= ~(1<<RX_PD0)
#define PIN_RX_PD0 PIND & _BV(RX_PD0)
#define RX_PD0_VCC PORTD |= _BV(RX_PD0)
#define RX_PD0_GND PORTD &= ~_BV(RX_PD0)

#define MISO_PB6 PB6
#define DDR_MISO_PB6 DDRB &= ~(1<<MISO_PB6)
#define PIN_MISO_PB6 PINB & _BV(MISO_PB6)
#define MISO_PB6_VCC PORTB |= _BV(MISO_PB6)
#define MISO_PB6_GND PORTB &= ~_BV(MISO_PB6)


// OUTS

#define TX_PD1 PD1
#define TX_PD1_DDR DDRD |= (1<<TX_PD1)
#define TX_PD1_LOW PORTD &= ~(1<<TX_PD1)
#define TX_PD1_HIGH PORTD |= (1<<TX_PD1)
#define TX_PD1_Z PORTD ^= (1<<TX_PD1)

#define MOSI_PB5 PB5
#define MOSI_PB5_DDR DDRB |= (1<<MOSI_PB5)
#define MOSI_PB5_LOW PORTB &= ~(1<<MOSI_PB5)
#define MOSI_PB5_HIGH PORTB |= (1<<MOSI_PB5)
#define MOSI_PB5_Z PORTB ^= (1<<MOSI_PB5)


#define OUT1_PD5 PD5
#define OUT1_PD5_DDR DDRD |= (1<<OUT1_PD5)
#define OUT1_PD5_LOW PORTD &= ~(1<<OUT1_PD5)
#define OUT1_PD5_HIGH PORTD |= (1<<OUT1_PD5)
#define OUT1_PD5_Z PORTD ^= (1<<OUT1_PD5)

#define OUT2_PD6 PD6
#define OUT2_PD6_DDR DDRD |= (1<<OUT2_PD6)
#define OUT2_PD6_LOW PORTD &= ~(1<<OUT2_PD6)
#define OUT2_PD6_HIGH PORTD |= (1<<OUT2_PD6)
#define OUT2_PD6_Z PORTD ^= (1<<OUT2_PD6)

#define OUT3_PD7 PD7
#define OUT3_PD7_DDR DDRD |= (1<<OUT3_PD7)
#define OUT3_PD7_LOW PORTD &= ~(1<<OUT3_PD7)
#define OUT3_PD7_HIGH PORTD |= (1<<OUT3_PD7)
#define OUT3_PD7_Z PORTD ^= (1<<OUT3_PD7)

#define OUT4_PC0 PC0
#define OUT4_PC0_DDR DDRC |= (1<<OUT4_PC0)
#define OUT4_PC0_LOW PORTC &= ~(1<<OUT4_PC0)
#define OUT4_PC0_HIGH PORTC |= (1<<OUT4_PC0)
#define OUT4_PC0_Z PORTC ^= (1<<OUT4_PC0)

#define OUT5_PC1 PC7
#define OUT5_PC1_DDR DDRC |= (1<<OUT5_PC1)
#define OUT5_PC1_LOW PORTC &= ~(1<<OUT5_PC1)
#define OUT5_PC1_HIGH PORTC |= (1<<OUT5_PC1)
#define OUT5_PC1_Z PORTC ^= (1<<OUT5_PC1)

#define OUT6_PD3 PD3
#define OUT6_PD3_DDR DDRD |= (1<<OUT6_PD3)
#define OUT6_PD3_LOW PORTD &= ~(1<<OUT6_PD3)
#define OUT6_PD3_HIGH PORTD |= (1<<OUT6_PD3)
#define OUT6_PD3_Z PORTD ^= (1<<OUT6_PD3)

#define OUT7_PA3 PA3
#define OUT7_PA3_DDR DDRA |= (1<<OUT7_PA3)
#define OUT7_PA3_LOW PORTA &= ~(1<<OUT7_PA3)
#define OUT7_PA3_HIGH PORTA |= (1<<OUT7_PA3)
#define OUT7_PA3_Z PORTA ^= (1<<OUT7_PA3)

#define OUT8_PA1 PA7
#define OUT8_PA1_DDR DDRA |= (1<<OUT8_PA1)
#define OUT8_PA1_LOW PORTA &= ~(1<<OUT8_PA1)
#define OUT8_PA1_HIGH PORTA |= (1<<OUT8_PA1)
#define OUT8_PA1_Z PORTA ^= (1<<OUT8_PA1)

#define OUT9_PB4 PB4
#define OUT9_PB4_DDR DDRB |= (1<<OUT9_PB4)
#define OUT9_PB4_LOW PORTB &= ~(1<<OUT9_PB4)
#define OUT9_PB4_HIGH PORTB |= (1<<OUT9_PB4)
#define OUT9_PB4_Z PORTB ^= (1<<OUT9_PB4)


#define VGA_SWITCH_PB2 PB2
#define VGA_SWITCH_PB2_DDR DDRB |= (1<<VGA_SWITCH_PB2)
#define VGA_SWITCH_PB2_LOW PORTB &= ~(1<<VGA_SWITCH_PB2)
#define VGA_SWITCH_PB2_HIGH PORTB |= (1<<VGA_SWITCH_PB2)
#define VGA_SWITCH_PB2_Z PORTB ^= (1<<VGA_SWITCH_PB2)

#define RELAY_PB0 PB0
#define RELAY_PB0_DDR DDRB |= (1<<RELAY_PB0)
#define RELAY_PB0_LOW PORTB &= ~(1<<RELAY_PB0)
#define RELAY_PB0_HIGH PORTB |= (1<<RELAY_PB0)
#define RELAY_PB0_Z PORTB ^= (1<<RELAY_PB0)

#define MUTE_PD4 PD4
#define MUTE_PD4_DDR DDRD |= (1<<MUTE_PD4)
#define MUTE_PD4_LOW PORTD &= ~(1<<MUTE_PD4)
#define MUTE_PD4_HIGH PORTD |= (1<<MUTE_PD4)
#define MUTE_PD4_Z PORTD ^= (1<<MUTE_PD4)

#define ALARM_12V_PB1 PB1
#define ALARM_12V_PB1_DDR DDRB |= (1<<ALARM_12V_PB1)
#define ALARM_12V_PB1_LOW PORTB &= ~(1<<ALARM_12V_PB1)
#define ALARM_12V_PB1_HIGH PORTB |= (1<<ALARM_12V_PB1)
#define ALARM_12V_PB1_Z PORTB ^= (1<<ALARM_12V_PB1)

// FUNCTIONS DECLARATION
void ioInit(void);
//======= MAIN =============

#endif /* MAIN_H_ */
