/*
 * main.h
 *
 *  Created on: 02-04-2013
 *       Autor: Arkadiusz Trojanowski
 */

#ifndef MAIN_H_
#define MAIN_H_




#define DDR_jedynka_wy DDRC |= _BV(jedynka_wy)
#define PORT_jedynka_wy_0 PORTC &= ~_BV(jedynka_wy)
#define PORT_jedynka_wy_1 PORTC |= _BV(jedynka_wy)
#define PORT_jedynka_wy_z PORTC ^= _BV(jedynka_wy)
#define jedynka_wy PC5





//---------------------------------------------------------------
//-----------------------------------------------------------------------------



#endif /* MAIN_H_ */
