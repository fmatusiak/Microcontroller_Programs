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



// OUTS

// =============================

// ==============================================================================
// ================================== IN PROGRAM ================================
// INS

#define IN1_PA3 PA3
#define DDR_IN1_PA3 DDRA &= ~(1<<IN1_PA3)
#define PIN_IN1_PA3 PINA & _BV(IN1_PA3)
#define IN1_PA3_VCC PORTA |= _BV(IN1_PA3)
#define IN1_PA3_GND PORTA &= ~_BV(IN1_PA3)

#define IN2_PA2 PA2
#define DDR_IN2_PA2 DDRA &= ~(1<<IN2_PA2)
#define PIN_IN2_PA2 PINA & _BV(IN2_PA2)
#define IN2_PA2_VCC PORTA |= _BV(IN2_PA2)
#define IN2_PA2_GND PORTA &= ~_BV(IN2_PA2)

#define IN3_PA1 PA1
#define DDR_IN3_PA1 DDRA &= ~(1<<IN3_PA1)
#define PIN_IN3_PA1 PINA & _BV(IN3_PA1)
#define IN3_PA1_VCC PORTA |= _BV(IN3_PA1)
#define IN3_PA1_GND PORTA &= ~_BV(IN3_PA1)

#define IN4_PA0 PA0
#define DDR_IN4_PA0 DDRA &= ~(1<<IN4_PA0)
#define PIN_IN4_PA0 PINA & _BV(IN4_PA0)
#define IN4_PA0_VCC PORTA |= _BV(IN4_PA0)
#define IN4_PA0_GND PORTA &= ~_BV(IN4_PA0)

#define IN5_PA4 PA4
#define DDR_IN5_PA4 DDRA &= ~(1<<IN5_PA4)
#define PIN_IN5_PA4 PINA & _BV(IN5_PA4)
#define IN5_PA4_VCC PORTA |= _BV(IN5_PA4)
#define IN5_PA4_GND PORTA &= ~_BV(IN5_PA4)

#define IN6_PC3 PC3
#define DDR_IN6_PC3 DDRC &= ~(1<<IN6_PC3)
#define PIN_IN6_PC3 PINC & _BV(IN6_PC3)
#define IN6_PC3_VCC PORTC |= _BV(IN6_PC3)
#define IN6_PC3_GND PORTC &= ~_BV(IN6_PC3)

#define IN7_PC2 PC2
#define DDR_IN7_PC2 DDRC &= ~(1<<IN7_PC2)
#define PIN_IN7_PC2 PINC & _BV(IN7_PC2)
#define IN7_PC2_VCC PORTC |= _BV(IN7_PC2)
#define IN7_PC2_GND PORTC &= ~_BV(IN7_PC2)

#define IN8_PC1 PC1
#define DDR_IN8_PC1 DDRC &= ~(1<<IN8_PC1)
#define PIN_IN8_PC1 PINC & _BV(IN8_PC1)
#define IN8_PC1_VCC PORTC |= _BV(IN8_PC1)
#define IN8_PC1_GND PORTC &= ~_BV(IN8_PC1)

#define IN9_PC0 PC0
#define DDR_IN9_PC0 DDRC &= ~(1<<IN9_PC0)
#define PIN_IN9_PC0 PINC & _BV(IN9_PC0)
#define IN9_PC0_VCC PORTC |= _BV(IN9_PC0)
#define IN9_PC0_GND PORTC &= ~_BV(IN9_PC0)

#define IN10_PB4 PB4
#define DDR_IN10_PB4 DDRB &= ~(1<<IN10_PB4)
#define PIN_IN10_PB4 PINB & _BV(IN10_PB4)
#define IN10_PB4_VCC PORTB |= _BV(IN10_PB4)
#define IN10_PB4_GND PORTB &= ~_BV(IN10_PB4)

#define RX_PD0 PD0
#define DDR_RX_PD0 DDRD &= ~(1<<RX_PD0)
#define PIN_RX_PD0 PIND & _BV(RX_PD0)
#define RX_PD0_VCC PORTD |= _BV(RX_PD0)
#define RX_PD0_GND PORTD &= ~_BV(RX_PD0)

#define MOSI_PB5 PB5
#define DDR_MOSI_PB5 DDRB &= ~(1<<MOSI_PB5)
#define PIN_MOSI_PB5 PINB & _BV(MOSI_PB5)
#define MOSI_PB5_VCC PORTB |= _BV(MOSI_PB5)
#define MOSI_PB5_GND PORTB &= ~_BV(MOSI_PB5)

#define SCK_PB7 PB7
#define DDR_SCK_PB7 DDRB &= ~(1<<SCK_PB7)
#define PIN_SCK_PB7 PINB & _BV(SCK_PB7)
#define SCK_PB7_VCC PORTB |= _BV(SCK_PB7)
#define SCK_PB7_GND PORTB &= ~_BV(SCK_PB7)


#define TEST_POINT_PB6 PB3
#define DDR_TEST_POINT_PB6 DDRB &= ~(1<<TEST_POINT_PB6)
#define PIN_TEST_POINT_PB6 PINB & _BV(TEST_POINT_PB6)
#define TEST_POINT_PB6_VCC PORTB |= _BV(TEST_POINT_PB6)
#define TEST_POINT_PB6_GND PORTB &= ~_BV(TEST_POINT_PB6)

// OUTS

#define TX_PD1 PD1
#define TX_PD1_DDR DDRD |= (1<<TX_PD1)
#define TX_PD1_LOW PORTD &= ~(1<<TX_PD1)
#define TX_PD1_HIGH PORTD |= (1<<TX_PD1)
#define TX_PD1_Z PORTD ^= (1<<TX_PD1)

#define MISO_PB6 PB6
#define MISO_PB6_DDR DDRB |= (1<<MISO_PB6)
#define MISO_PB6_LOW PORTB &= ~(1<<MISO_PB6)
#define MISO_PB6_HIGH PORTB |= (1<<MISO_PB6)
#define MISO_PB6_Z PORTB ^= (1<<MISO_PB6)


#define OUT1_PC6 PC6
#define OUT1_PC6_DDR DDRC |= (1<<OUT1_PC6)
#define OUT1_PC6_LOW PORTC &= ~(1<<OUT1_PC6)
#define OUT1_PC6_HIGH PORTC |= (1<<OUT1_PC6)
#define OUT1_PC6_Z PORTC ^= (1<<OUT1_PC6)

#define OUT2_PC7 PC7
#define OUT2_PC7_DDR DDRC |= (1<<OUT2_PC7)
#define OUT2_PC7_LOW PORTC &= ~(1<<OUT2_PC7)
#define OUT2_PC7_HIGH PORTC |= (1<<OUT2_PC7)
#define OUT2_PC7_Z PORTC ^= (1<<OUT2_PC7)

#define OUT3_PA7 PA7
#define OUT3_PA7_DDR DDRA |= (1<<OUT3_PA7)
#define OUT3_PA7_LOW PORTA &= ~(1<<OUT3_PA7)
#define OUT3_PA7_HIGH PORTA |= (1<<OUT3_PA7)
#define OUT3_PA7_Z PORTA ^= (1<<OUT3_PA7)

#define OUT4_PA6 PA6
#define OUT4_PA6_DDR DDRA |= (1<<OUT4_PA6)
#define OUT4_PA6_LOW PORTA &= ~(1<<OUT4_PA6)
#define OUT4_PA6_HIGH PORTA |= (1<<OUT4_PA6)
#define OUT4_PA6_Z PORTA ^= (1<<OUT4_PA6)

#define OUT5_PA5 PA5
#define OUT5_PA5_DDR DDRA |= (1<<OUT5_PA5)
#define OUT5_PA5_LOW PORTA &= ~(1<<OUT5_PA5)
#define OUT5_PA5_HIGH PORTA |= (1<<OUT5_PA5)
#define OUT5_PA5_Z PORTA ^= (1<<OUT5_PA5)

#define OUT6_PC5 PC5
#define OUT6_PC5_DDR DDRC |= (1<<OUT6_PC5)
#define OUT6_PC5_LOW PORTC &= ~(1<<OUT6_PC5)
#define OUT6_PC5_HIGH PORTC |= (1<<OUT6_PC5)
#define OUT6_PC5_Z PORTC ^= (1<<OUT6_PC5)

#define OUT7_PD7 PD7
#define OUT7_PD7_DDR DDRD |= (1<<OUT7_PD7)
#define OUT7_PD7_LOW PORTD &= ~(1<<OUT7_PD7)
#define OUT7_PD7_HIGH PORTD |= (1<<OUT7_PD7)
#define OUT7_PD7_Z PORTD ^= (1<<OUT7_PD7)

#define OUT8_PD6 PD6
#define OUT8_PD6_DDR DDRD |= (1<<OUT8_PD6)
#define OUT8_PD6_LOW PORTD &= ~(1<<OUT8_PD6)
#define OUT8_PD6_HIGH PORTD |= (1<<OUT8_PD6)
#define OUT8_PD6_Z PORTD ^= (1<<OUT8_PD6)

#define OUT9_PD5 PD5
#define OUT9_PD5_DDR DDRD |= (1<<OUT9_PD5)
#define OUT9_PD5_LOW PORTD &= ~(1<<OUT9_PD5)
#define OUT9_PD5_HIGH PORTD |= (1<<OUT9_PD5)
#define OUT9_PD5_Z PORTD ^= (1<<OUT9_PD5)


#define VGA_SWITCH_PD4 PD4
#define VGA_SWITCH_PD4_DDR DDRD |= (1<<VGA_SWITCH_PD4)
#define VGA_SWITCH_PD4_LOW PORTD &= ~(1<<VGA_SWITCH_PD4)
#define VGA_SWITCH_PD4_HIGH PORTD |= (1<<VGA_SWITCH_PD4)
#define VGA_SWITCH_PD4_Z PORTD ^= (1<<VGA_SWITCH_PD4)

#define RELAY_ONE_PB2 PB2
#define RELAY_ONE_PB2_DDR DDRB |= (1<<RELAY_ONE_PB2)
#define RELAY_ONE_PB2_LOW PORTB &= ~(1<<RELAY_ONE_PB2)
#define RELAY_ONE_PB2_HIGH PORTB |= (1<<RELAY_ONE_PB2)
#define RELAY_ONE_PB2_Z PORTB ^= (1<<RELAY_ONE_PB2)

#define RELAY_TWO_PD2 PD2
#define RELAY_TWO_PD2_DDR DDRD |= (1<<RELAY_TWO_PD2)
#define RELAY_TWO_PD2_LOW PORTD &= ~(1<<RELAY_TWO_PD2)
#define RELAY_TWO_PD2_HIGH PORTD |= (1<<RELAY_TWO_PD2)
#define RELAY_TWO_PD2_Z PORTD ^= (1<<RELAY_TWO_PD2)

#define MUTE_PC4 PC4
#define MUTE_PC4_DDR DDRC |= (1<<MUTE_PC4)
#define MUTE_PC4_LOW PORTC &= ~(1<<MUTE_PC4)
#define MUTE_PC4_HIGH PORTC |= (1<<MUTE_PC4)
#define MUTE_PC4_Z PORTC ^= (1<<MUTE_PC4)

#define ALARM_12V_PD3 PD3
#define ALARM_12V_PD3_DDR DDRD |= (1<<ALARM_12V_PD3)
#define ALARM_12V_PD3_LOW PORTD &= ~(1<<ALARM_12V_PD3)
#define ALARM_12V_PD3_HIGH PORTD |= (1<<ALARM_12V_PD3)
#define ALARM_12V_PD3_Z PORTD ^= (1<<ALARM_12V_PD3)

// FUNCTIONS DECLARATION
void ioInit(void);
//======= MAIN =============

#endif /* MAIN_H_ */
