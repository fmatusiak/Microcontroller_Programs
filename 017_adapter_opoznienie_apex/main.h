
#ifndef MAIN_H_
#define MAIN_H_




//-----------------------------------------------------------------------------

#define DDR_wejscie DDRB &= ~(_BV(wejscie))
#define PIN_wejscie PINB & _BV(wejscie)
#define wejscie_VCC PORTB |= _BV(wejscie)

#define wejscie PB2




#define DDR_wyjscie DDRB |= _BV(wyjscie)
#define PORT_wyjscie_0 PORTB &= ~_BV(wyjscie)
#define PORT_wyjscie_1 PORTB |= _BV(wyjscie)
#define PORT_wyjscie_z PORTB ^= _BV(wyjscie)
#define wyjscie PB3

#define DDR_wyjscie2 DDRB |= _BV(wyjscie2)
#define PORT_wyjscie2_0 PORTB &= ~_BV(wyjscie2)
#define PORT_wyjscie2_1 PORTB |= _BV(wyjscie2)
#define PORT_wyjscie2_z PORTB ^= _BV(wyjscie2)
#define wyjscie2 PB2





// ============================================================================

#endif /* MAIN_H_ */
