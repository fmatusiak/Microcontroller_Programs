/*
 * main.h
 *
 *  Created on: 02-04-2013
 *       Autor: Arkadiusz Trojanowski
 */

#ifndef MAIN_H_
#define MAIN_H_

#define DDR_rxd DDRD &= ~(_BV(rxd))
#define PIN_rxd PIND & _BV(rxd)
#define rxd_VCC PORTD |= _BV(rxd)
#define rxd_GND PORTD &= ~_BV(rxd)
#define rxd PD0

#define DDR_txd DDRD |= _BV(txd)
#define PORT_txd_0 PORTD &= ~(_BV(txd))
#define PORT_txd_1 PORTD |= _BV(txd)
#define PORT_txd_Z PORTD ^= _BV(txd)
#define txd PD1

#define DDR_switch_1 DDRB &= ~(_BV(switch_1))
#define PIN_switch_1 PINB & _BV(switch_1)
#define switch_1_VCC PORTB |= _BV(switch_1)
#define switch_1_GND PORTB &= ~_BV(switch_1)
#define switch_1 PB0 //2

#define DDR_switch_2 DDRD &= ~(_BV(switch_2))
#define PIN_switch_2 PIND & _BV(switch_2)
#define switch_2_VCC PORTD |= _BV(switch_2)
#define switch_2_GND PORTD &= ~_BV(switch_2)
#define switch_2 PD7 //2

#define DDR_switch_3 DDRD &= ~(_BV(switch_3))
#define PIN_switch_3 PIND & _BV(switch_3)
#define switch_3_VCC PORTD |= _BV(switch_3)
#define switch_3_GND PORTD &= ~_BV(switch_3)
#define switch_3 PD6//4

#define DDR_switch_4 DDRD &= ~(_BV(switch_4))
#define PIN_switch_4 PIND & _BV(switch_4)
#define switch_4_VCC PORTD |= _BV(switch_4)
#define switch_4_GND PORTD &= ~_BV(switch_4)
#define switch_4 PD5 // 5


// wyjscia

#define DDR_jedynka_wy DDRB |= _BV(jedynka_wy)
#define PORT_jedynka_wy_0 PORTB &= ~_BV(jedynka_wy)
#define PORT_jedynka_wy_1 PORTB |= _BV(jedynka_wy)
#define PORT_jedynka_wy_z PORTB ^= _BV(jedynka_wy)
#define jedynka_wy PB1





//---------------------------------------------------------------
//-----------------------------------------------------------------------------



#endif /* MAIN_H_ */
