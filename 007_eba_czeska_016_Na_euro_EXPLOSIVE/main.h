/*
 * main.h
 *
 *  Created on: 02-04-2013
 *       Autor: Arkadiusz Trojanowski
 */

#ifndef MAIN_H_
#define MAIN_H_

#define DDR_rxs_we DDRC &= ~(_BV(rxs_we))
#define PIN_rxs_we PINC & _BV(rxs_we)
#define rxs_we_VCC PORTC |= _BV(rxs_we)
#define rxs_we_GND PORTC &= ~_BV(rxs_we)
#define rxs_we PC3

#define DDR_txs DDRC |= _BV(txs)
#define PORT_txs_0 PORTC &= ~_BV(txs)
#define PORT_txs_1 PORTC |= _BV(txs)
#define PORT_txs_z PORTC ^= _BV(txs)
#define txs PC2



//--------------------------
//-----------------------------------------------------------------------------



#endif /* MAIN_H_ */
