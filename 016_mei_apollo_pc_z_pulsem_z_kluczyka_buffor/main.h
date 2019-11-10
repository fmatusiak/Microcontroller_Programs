


#define DDR_rxs_we DDRC &= ~(_BV(rxs_we))
#define PIN_rxs_we PINC & _BV(rxs_we)
#define rxs_we_VCC PORTC |= _BV(rxs_we)
#define rxs_we_GND PORTC &= ~_BV(rxs_we)
#define rxs_we PC2

#define DDR_txs DDRC |= _BV(txs)
#define PORT_txs_0 PORTC &= ~_BV(txs)
#define PORT_txs_1 PORTC |= _BV(txs)
#define PORT_txs_z PORTC ^= _BV(txs)
#define txs PC3


#define DDR_Key_plus DDRB &= ~(_BV(Key_plus))
#define PIN_Key_plus PINB & _BV(Key_plus)
#define Key_plus_VCC PORTB |= _BV(Key_plus)
#define Key_plus_GND PORTB &= ~_BV(Key_plus)
#define Key_plus PB5






//-----------------------------------------------------------------------------

