/*
 * main.h
 *
 *  Created on: 02-04-2013
 *       Autor: Arkadiusz Trojanowski
 */

#ifndef MAIN_H_
#define MAIN_H_





// wyjscia


#define DDR_dwojka_wy DDRC |= _BV(dwojka_wy)
#define PORT_dwojka_wy_0 PORTC &= ~_BV(dwojka_wy)
#define PORT_dwojka_wy_1 PORTC |= _BV(dwojka_wy)
#define PORT_dwojka_wy_z PORTC ^= _BV(dwojka_wy)
#define dwojka_wy PC5




//--------------------------
//-----------------------------------------------------------------------------



#endif /* MAIN_H_ */
