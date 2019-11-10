
#define DDR_rxs_we DDRC &= ~(_BV(rxs_we))
#define PIN_rxs_we PINC & _BV(rxs_we)
#define rxs_we_VCC PORTC |= _BV(rxs_we)
#define rxs_we_GND PORTC &= ~_BV(rxs_we)
#define rxs_we PC4

#define DDR_coin_we DDRC &= ~(_BV(coin_we))
#define PIN_coin_we PINC & _BV(coin_we)
#define coin_we_VCC PORTC |= _BV(coin_we)
#define coin_we_GND PORTC &= ~_BV(coin_we)
#define coin_we PC1
//==============================================================================

#define DDR_txs DDRC |= _BV(txs)
#define PORT_txs_0 PORTC &= ~_BV(txs)
#define PORT_txs_1 PORTC |= _BV(txs)
#define PORT_txs_z PORTC ^= _BV(txs)
#define txs PC5


#define DDR_nabij DDRC |= _BV(nabij)
#define PORT_nabij_0 PORTC &= ~_BV(nabij)
#define PORT_nabij_1 PORTC |= _BV(nabij)
#define PORT_nabij_z PORTC ^= _BV(nabij)
#define nabij PC2


//-----------------------------------------------------------------------------

