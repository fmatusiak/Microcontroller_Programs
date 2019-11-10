/*
 * main.h
 *
 *  Created on: 02-04-2013
 *       Autor: Arkadiusz Trojanowski
 */

#ifndef MAIN_H_
#define MAIN_H_



#define DDR_czworka DDRB &= ~(_BV(czworka))
#define PIN_czworka PINB & _BV(czworka)
#define czworka_VCC PORTB |= _BV(czworka)
#define czworka_GND PORTB &= ~_BV(czworka)
#define czworka PB2




// wyjscia

#define DDR_jedynka_wy DDRB |= _BV(jedynka_wy)
#define PORT_jedynka_wy_0 PORTB &= ~_BV(jedynka_wy)
#define PORT_jedynka_wy_1 PORTB |= _BV(jedynka_wy)
#define PORT_jedynka_wy_z PORTB ^= _BV(jedynka_wy)
#define jedynka_wy PB0



//--------------------------
//-----------------------------------------------------------------------------



#endif /* MAIN_H_ */
