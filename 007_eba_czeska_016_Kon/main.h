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
/*
#define DDR_rxs DDRD &= ~(_BV(rxs))
#define PIN_rxs PIND & _BV(rxs)
#define rxs_VCC PORTD |= _BV(rxs)
#define rxs_GND PORTD &= ~_BV(rxs)
#define rxs PD0

#define DDR_txs DDRD |= _BV(txs)
#define PORT_txs_0 PORTD &= ~(_BV(txs))
#define PORT_txs_1 PORTD |= _BV(txs)
#define PORT_txs_Z PORTD ^= _BV(txs)
#define txs PD1
*/

#define DDR_stacyjka DDRB &= ~(_BV(stacyjka))
#define PIN_stacyjka PINB & _BV(stacyjka)
#define stacyjka_VCC PORTB |= _BV(stacyjka)
#define stacyjka_GND PORTB &= ~_BV(stacyjka)
#define stacyjka PB0 //2

#define DDR_jedynka DDRD &= ~(_BV(jedynka))
#define PIN_jedynka PIND & _BV(jedynka)
#define jedynka_VCC PORTD |= _BV(jedynka)
#define jedynka_GND PORTD &= ~_BVjedynka)
#define jedynka PD6 //2



#define DDR_trojka DDRD &= ~(_BV(trojka))
#define PIN_trojka PIND & _BV(trojka)
#define trojka_VCC PORTD |= _BV(trojka)
#define trojka_GND PORTD &= ~_BV(trojka)
#define trojka PD4 // 5

#define DDR_czworka DDRD &= ~(_BV(czworka))
#define PIN_czworka PIND & _BV(czworka)
#define czworka_VCC PORTD |= _BV(czworka)
#define czworka_GND PORTD &= ~_BV(czworka)
#define czworka PD3

#define DDR_kanal_1b DDRB &= ~(_BV(kanal_1b))
#define PIN_kanal_1b PINB & _BV(kanal_1b)
#define kanal_1b_VCC PORTB |= _BV(kanal_1b)
#define kanal_1b_GND PORTB &= ~_BV(kanal_1b)
#define kanal_1b PB4

#define DDR_kanal_5s DDRC &= ~(_BV(kanal_5s))
#define PIN_kanal_5s PINC & _BV(kanal_5s)
#define kanal_5s_VCC PORTC |= _BV(kanal_5s)
#define kanal_5s_GND PORTC &= ~_BV(kanal_5s)
#define kanal_5s PC0

#define DDR_hr1 DDRC &= ~(_BV(hr1))
#define PIN_hr1 PINC & _BV(hr1)
#define hr1_VCC PORTC |= _BV(hr1)
#define hr1_GND PORTC &= ~_BV(hr1)
#define hr1 PC4



// wyjscia

#define DDR_jedynka_wy DDRD |= _BV(jedynka_wy)
#define PORT_jedynka_wy_0 PORTD &= ~_BV(jedynka_wy)
#define PORT_jedynka_wy_1 PORTD |= _BV(jedynka_wy)
#define PORT_jedynka_wy_z PORTD ^= _BV(jedynka_wy)
#define jedynka_wy PD7

#define DDR_dwojka_wy DDRD |= _BV(dwojka_wy)
#define PORT_dwojka_wy_0 PORTD &= ~_BV(dwojka_wy)
#define PORT_dwojka_wy_1 PORTD |= _BV(dwojka_wy)
#define PORT_dwojka_wy_z PORTD ^= _BV(dwojka_wy)
#define dwojka_wy PD5

#define DDR_trojka_wy DDRB |= _BV(trojka_wy)
#define PORT_trojka_wy_0 PORTB &= ~_BV(trojka_wy)
#define PORT_trojka_wy_1 PORTB |= _BV(trojka_wy)
#define PORT_trojka_wy_z PORTB ^= _BV(trojka_wy)
#define trojka_wy PB3

#define DDR_czworka_wy DDRB |= _BV(czworka_wy)
#define PORT_czworka_wy_0 PORTB &= ~_BV(czworka_wy)
#define PORT_czworka_wy_1 PORTB |= _BV(czworka_wy)
#define PORT_czworka_wy_z PORTB ^= _BV(czworka_wy)
#define czworka_wy PB2




//--------------------------
//-----------------------------------------------------------------------------



#endif /* MAIN_H_ */
