/*
 * main.h
 *
 *  Created on: 02-04-2013
 *       Autor: Arkadiusz Trojanowski
 */

#ifndef MAIN_H_
#define MAIN_H_


#define DDR_podsluch_we DDRD &= ~(_BV(podsluch_we))
#define PIN_podsluch_we PIND & _BV(podsluch_we)
#define podsluch_we_VCC PORTD |= _BV(podsluch_we)
#define podsluch_we_GND PORTD &= ~_BV(podsluch_we)
#define podsluch_we PD5


// wyjscia

#define DDR_jedynka_wy DDRC |= _BV(jedynka_wy)
#define PORT_jedynka_wy_0 PORTC &= ~_BV(jedynka_wy)
#define PORT_jedynka_wy_1 PORTC |= _BV(jedynka_wy)
#define PORT_jedynka_wy_z PORTC ^= _BV(jedynka_wy)
#define jedynka_wy PC5 // okok







//--------------------------
//-----------------------------------------------------------------------------



#endif /* MAIN_H_ */
