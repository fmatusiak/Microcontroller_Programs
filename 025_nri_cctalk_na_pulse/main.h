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



// wyjscia

#define DDR_jedynka_wy DDRC |= _BV(jedynka_wy)
#define PORT_jedynka_wy_1 PORTC &= ~_BV(jedynka_wy)
#define PORT_jedynka_wy_0 PORTC |= _BV(jedynka_wy)
#define PORT_jedynka_wy_z PORTC ^= _BV(jedynka_wy)
#define jedynka_wy PC3 // okok




//--------------------------
//-----------------------------------------------------------------------------



#endif /* MAIN_H_ */
