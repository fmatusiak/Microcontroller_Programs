/*
 * main.h
 *
 *  Created on: 02-04-2013
 *       Autor: Arkadiusz Trojanowski
 */

#ifndef MAIN_H_
#define MAIN_H_



// wyjscia




#define DDR_RESET_OUT DDRD |= _BV(RESET_OUT)
#define PORT_RESET_OUT_0 PORTD &= ~_BV(RESET_OUT)
#define PORT_RESET_OUT_1 PORTD |= _BV(RESET_OUT)
#define PORT_RESET_OUT_z PORTD ^= _BV(RESET_OUT)
#define RESET_OUT PD3



//--------------------------
//-----------------------------------------------------------------------------



#endif /* MAIN_H_ */
