
#define DDR_rxs_we DDRD &= ~(_BV(rxs_we))
#define PIN_rxs_we PIND & _BV(rxs_we)
#define rxs_we_VCC PORTD |= _BV(rxs_we)
#define rxs_we_GND PORTD &= ~_BV(rxs_we)
#define rxs_we PD3

#define DDR_txs DDRD |= _BV(txs)
#define PORT_txs_0 PORTD &= ~_BV(txs)
#define PORT_txs_1 PORTD |= _BV(txs)
#define PORT_txs_z PORTD ^= _BV(txs)
#define txs PD2



#define DDR_w_gry DDRC |= _BV(w_gry)
#define PORT_w_gry_0 PORTC &= ~_BV(w_gry)
#define PORT_w_gry_1 PORTC |= _BV(w_gry)
#define PORT_w_gry_z PORTC ^= _BV(w_gry)
#define w_gry PC5

#define DDR_IN6_IN DDRB &= ~(_BV(IN6_IN)) // IN 6
#define PIN_IN6_IN PINB & _BV(IN6_IN)
#define IN6_IN_VCC PORTB |= _BV(IN6_IN)
#define IN6_IN_GND PORTB &= ~_BV(IN6_IN)
#define IN6_IN PB2

//-----------------------------------------------------------------------------






//-----------------------------------------------------------------------------
