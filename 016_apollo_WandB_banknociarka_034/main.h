
#define DDR_rxs_we DDRD &= ~(_BV(rxs_we))
#define PIN_rxs_we PIND & _BV(rxs_we)
#define rxs_we_VCC PORTD |= _BV(rxs_we)
#define rxs_we_GND PORTD &= ~_BV(rxs_we)
#define rxs_we PD3

#define DDR_coin_we DDRB &= ~(_BV(coin_we))
#define PIN_coin_we PINB & _BV(coin_we)
#define coin_we_VCC PORTB |= _BV(coin_we)
#define coin_we_GND PORTB &= ~_BV(coin_we)
#define coin_we PB2
//==============================================================================

#define DDR_txs DDRD |= _BV(txs)
#define PORT_txs_0 PORTD &= ~_BV(txs)
#define PORT_txs_1 PORTD |= _BV(txs)
#define PORT_txs_z PORTD ^= _BV(txs)
#define txs PD2


#define DDR_nabij DDRC |= _BV(nabij)
#define PORT_nabij_0 PORTC &= ~_BV(nabij)
#define PORT_nabij_1 PORTC |= _BV(nabij)
#define PORT_nabij_z PORTC ^= _BV(nabij)
#define nabij PC0


//-----------------------------------------------------------------------------

