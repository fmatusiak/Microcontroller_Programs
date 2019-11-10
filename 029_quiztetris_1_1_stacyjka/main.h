
#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "stdlib.h"

#define F_CPU 16000000UL
#define RS_BAUD 9600
#define CREDIT_DELAY 200
#define CREDITHS_DELAY 100
#define RS_UBRR 103

// INS

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

#define IN3_25_PC6 PC6
#define IN3_25_PC6_DDR DDRC &= ~(1<<IN3_25_PC6)
#define IN3_25_PC6_VCC PORTC |= (1<<IN3_25_PC6)
#define IN3_25_PC6_GND PORTC &= ~(1<<IN3_25_PC6)
#define IN3_25_PC6_HIGH PINC & (1<<IN3_25_PC6)
#define IN3_25_PC6_LOW !(PINC & (1<<IN3_25_PC6))

#define IN4_26_PC7 PC7
#define IN4_26_PC7_DDR DDRC &= ~(1<<IN4_26_PC7)
#define IN4_26_PC7_VCC PORTC |= (1<<IN4_26_PC7)
#define IN4_26_PC7_GND PORTC &= ~(1<<IN4_26_PC7)
#define IN4_26_PC7_HIGH PINC & (1<<IN4_26_PC7)
#define IN4_26_PC7_LOW !(PINC & (1<<IN4_26_PC7))

#define DDR_IN5 DDRB &= ~(_BV(IN5))
#define PIN_IN5 PINB & _BV(IN5)
#define IN5_VCC PORTB |= _BV(IN5)
#define IN5_GND PORTB &= ~_BV(IN5)
#define IN5 PB0

#define HS_ON_OFF_36_PA1 PA1 // p1
#define HS_ON_OFF_36_PA1_DDR DDRA &= ~(1<<HS_ON_OFF_36_PA1)
#define HS_ON_OFF_36_PA1_VCC PORTA |= (1<<HS_ON_OFF_36_PA1)
#define HS_ON_OFF_36_PA1_GND PORTA &= ~(1<<HS_ON_OFF_36_PA1)
#define HS_ON_OFF_36_PA1_HIGH PINA & (1<<HS_ON_OFF_36_PA1)
#define HS_ON_OFF_36_PA1_LOW !(PINA & (1<<HS_ON_OFF_36_PA1))

#define BARMAN_35_PA2 PA2 // p2
#define BARMAN_35_PA2_DDR DDRA &= ~(1<<BARMAN_35_PA2)
#define BARMAN_35_PA2_VCC PORTA |= (1<<BARMAN_35_PA2)
#define BARMAN_35_PA2_GND PORTA &= ~(1<<BARMAN_35_PA2)
#define BARMAN_35_PA2_HIGH PINA & (1<<BARMAN_35_PA2)
#define BARMAN_35_PA2_LOW !(PINA & (1<<BARMAN_35_PA2))

#define DOOR_34_PA3 PA3 //p3
#define DOOR_34_PA3_DDR DDRA &= ~(1<<DOOR_34_PA3)
#define DOOR_34_PA3_VCC PORTA |= (1<<DOOR_34_PA3)
#define DOOR_34_PA3_GND PORTA &= ~(1<<DOOR_34_PA3)
#define DOOR_34_PA3_HIGH PINA & (1<<DOOR_34_PA3)
#define DOOR_34_PA3_LOW !(PINA & (1<<DOOR_34_PA3))

#define WE1_32_PA5 PA5 // stac in
#define WE1_32_PA5_DDR DDRA &= ~(1<<WE1_32_PA5)
#define WE1_32_PA5_VCC PORTA |= (1<<WE1_32_PA5)
#define WE1_32_PA5_GND PORTA &= ~(1<<WE1_32_PA5)
#define WE1_32_PA5_HIGH PINA & (1<<WE1_32_PA5)
#define WE1_32_PA5_LOW !(PINA & (1<<WE1_32_PA5))

#define RX_DO_RP_41_PB1 PB1 // pi in
#define RX_DO_RP_41_PB1_DDR DDRB &= ~(1<<RX_DO_RP_41_PB1)
#define RX_DO_RP_41_PB1_VCC PORTB |= (1<<RX_DO_RP_41_PB1)
#define RX_DO_RP_41_PB1_GND PORTB &= ~(1<<RX_DO_RP_41_PB1)
#define RX_DO_RP_41_PB1_HIGH PINB & (1<<RX_DO_RP_41_PB1)
#define RX_DO_RP_41_PB1_LOW !(PINB & (1<<RX_DO_RP_41_PB1))

#define WE2_33_PA4 PA4 // dwa
#define WE2_33_PA4_DDR DDRA &= ~(1<<WE2_33_PA4)
#define WE2_33_PA4_VCC PORTA |= (1<<WE2_33_PA4)
#define WE2_33_PA4_GND PORTA &= ~(1<<WE2_33_PA4)
#define WE2_33_PA4_HIGH PINA & (1<<WE2_33_PA4)
#define WE2_33_PA4_LOW !(PINA & (1<<WE2_33_PA4))

#define RX2_11_PD2 PD2 // dwa
#define RX2_11_PD2_DDR DDRD &= ~(1<<RX2_11_PD2)
#define RX2_11_PD2_VCC PORTD |= (1<<RX2_11_PD2)
#define RX2_11_PD2_GND PORTD &= ~(1<<RX2_11_PD2)
#define RX2_11_PD2_HIGH PIND & (1<<RX2_11_PD2)
#define RX2_11_PD2_LOW !(PIND & (1<<RX2_11_PD2))

// OUTS
#define DDR_OUT1 DDRC |= _BV(OUT1)
#define PORT_OUT1_0 PORTC &= ~(_BV(OUT1))
#define PORT_OUT1_1 PORTC |= _BV(OUT1)
#define OUT1 PC0


#define DDR_OUT2 DDRC |= _BV(OUT2)
#define PORT_OUT2_0 PORTC &= ~(_BV(OUT2))
#define PORT_OUT2_1 PORTC |= _BV(OUT2)
#define OUT2 PC1

#define OUT3_21_PC2 PC2
#define DDR_OUT3_21_PC2 DDRC |= _BV(OUT3_21_PC2)
#define OUT3_21_PC2_LOW PORTC &= ~(_BV(OUT3_21_PC2))
#define OUT3_21_PC2_HIGH PORTC |= _BV(OUT3_21_PC2)

#define DDR_OUT4 DDRC |= _BV(OUT4)
#define PORT_OUT4_0 PORTC &= ~(_BV(OUT4))
#define PORT_OUT4_1 PORTC |= _BV(OUT4)
#define OUT4 PC3

#define DDR_OUT5 DDRA |= _BV(OUT5)
#define PORT_OUT5_0 PORTA &= ~(_BV(OUT5))
#define PORT_OUT5_1 PORTA |= _BV(OUT5)
#define OUT5 PA0

#define RASP_CREDIT PB3
#define RASP_CREDIT_DDR DDRB |= (1<<RASP_CREDIT) // ok
#define RASP_CREDIT_LOW PORTB &= ~(1<<RASP_CREDIT) // ok
#define RASP_CREDIT_HIGH PORTB |= (1<<RASP_CREDIT)

#define TX_DO_RP_42_PB2 PB2 //rasp_conf
#define TX_DO_RP_42_PB2_DDR DDRB |= (1<<TX_DO_RP_42_PB2)
#define TX_DO_RP_42_PB2_LOW PORTB &= ~(1<<TX_DO_RP_42_PB2)
#define TX_DO_RP_42_PB2_HIGH PORTB|= (1<<TX_DO_RP_42_PB2)

#define WBA_RES_14_PD5 PD5 // wba reset
#define WBA_RES_14_PD5_DDR DDRD |= (1<<WBA_RES_14_PD5)
#define WBA_RES_14_PD5_LOW PORTD &= ~(1<<WBA_RES_14_PD5)
#define WBA_RES_14_PD5_HIGH PORTD |= (1<<WBA_RES_14_PD5)

#define WBA12V_15_PD6 PD6
#define WBA12V_15_PD6_DDR DDRD |= (1<<WBA12V_15_PD6)
#define WBA12V_15_PD6_LOW PORTD &= ~(1<<WBA12V_15_PD6)
#define WBA12V_15_PD6_HIGH PORTD |= (1<<WBA12V_15_PD6)

#define WBA_PRZE_13_PD4 PD4 // wba switch
#define WBA_PRZE_13_PD4_DDR DDRD |= (1<<WBA_PRZE_13_PD4)
#define WBA_PRZE_13_PD4_LOW PORTD &= ~(1<<WBA_PRZE_13_PD4)
#define WBA_PRZE_13_PD4_HIGH PORTD |= (1<<WBA_PRZE_13_PD4)

#define PRZEL_VGA_44_PB4 PB4 // vga switch
#define PRZEL_VGA_44_PB4_DDR DDRB |= (1<<PRZEL_VGA_44_PB4)
#define PRZEL_VGA_44_PB4_LOW PORTB &= ~(1<<PRZEL_VGA_44_PB4)
#define PRZEL_VGA_44_PB4_HIGH PORTB |= (1<<PRZEL_VGA_44_PB4)

#define JP_SCREEN_SWITCH_PB5 PB5
#define JP_SCREEN_SWITCH_PB5_DDR DDRB |= (1<<JP_SCREEN_SWITCH_PB5)
#define JP_SCREEN_SWITCH_PB5_LOW PORTB &= ~(1<<JP_SCREEN_SWITCH_PB5)
#define JP_SCREEN_SWITCH_PB5_HIGH PORTB |= (1<<JP_SCREEN_SWITCH_PB5)
#define JP_SCREEN_SWITCH_PB5_Z PORTB ^= (1<<JP_SCREEN_SWITCH_PB5)

#define V12_OUT_16_PD7 PD7
#define V12_OUT_16_PD7_DDR DDRD |= (1<<V12_OUT_16_PD7)
#define V12_OUT_16_PD7_LOW PORTD &= ~(1<<V12_OUT_16_PD7)
#define V12_OUT_16_PD7_HIGH PORTD |= (1<<V12_OUT_16_PD7)

#define TX2_12_PD3 PD3
#define TX2_12_PD3_DDR DDRD |= (1<<TX2_12_PD3)
#define TX2_12_PD3_LOW PORTD &= ~(1<<TX2_12_PD3)
#define TX2_12_PD3_HIGH PORTD |= (1<<TX2_12_PD3)

// FUNCTIONS DECLARATION

void credits();
void jackpotCredits();
void jackpotSwitch();
void settings();
void switchOn();
void ioInit(void);
void uart_init(uint16_t ubrr) ;
void addRaspCredits(uint8_t);
void addHsCredits(uint8_t);
uint8_t uart_getc(void);
uint8_t uartIsChar(void);
void uart_putc(uint8_t);
void uartPutData(uint8_t, uint8_t*);
void turnOnRasp(void);
void check_quiz_payout(void);
void check_light(void);


// GLOBAL VARIABLES

volatile uint16_t counter = 0, jackpot = 1;
volatile int dataFrame[13];
volatile uint8_t uart = 0;
volatile uint8_t vga = 0;
volatile char hotSpotOn = 0,min = 0, start = 0;
volatile uint8_t c =0 ,FL_settings = 0;

#endif /* MAIN_H_ */
