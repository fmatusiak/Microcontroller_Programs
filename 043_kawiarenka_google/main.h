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
#define ZASILANIE PD0
#define DDR_ZASILANIE DDRD &= ~(1<<ZASILANIE)
#define PIN_ZASILANIE PIND & _BV(ZASILANIE)
#define ZASILANIE_VCC PORTD |= _BV(ZASILANIE)
#define ZASILANIE_GND PORTD &= ~_BV(ZASILANIE)


#define DOTYK PB5
#define DDR_DOTYK DDRB &= ~(1<<DOTYK)
#define PIN_DOTYK PINB & _BV(DOTYK)
#define DOTYK_VCC PORTB |= _BV(DOTYK)
#define DOTYK_GND PORTB &= ~_BV(DOTYK)


//*************************************
#define DOTYK_REL Relay_2_PD2
#define DOTYK_REL_DDR DDRD |= (1<<DOTYK_REL)
#define DOTYK_REL_LOW PORTD &= ~(1<<DOTYK_REL)
#define DOTYK_REL_HIGH PORTD |= (1<<DOTYK_REL)
#define DOTYK_REL_Z PORTD ^= (1<<DOTYK_REL)

#define POWER_REL PRZEL_VGA_PB2
#define POWER_REL_DDR DDRB |= (1<<POWER_REL)
#define POWER_REL_LOW PORTB &= ~(1<<POWER_REL)
#define POWER_REL_HIGH PORTB |= (1<<POWER_REL)
#define POWER_REL_Z PORTB ^= (1<<POWER_REL)

#define SCREEN_SWITCH_OUT JP_SCREEN_SWITCH_PD4
#define SCREEN_SWITCH_OUT_DDR DDRD |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_LOW PORTD &= ~(1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_HIGH PORTD |= (1<<SCREEN_SWITCH_OUT)
#define SCREEN_SWITCH_OUT_Z PORTD ^= (1<<SCREEN_SWITCH_OUT)


// FUNCTIONS DECLARATION
//======= MAIN =============
void ioInit(void);


#endif /* MAIN_H_ */
