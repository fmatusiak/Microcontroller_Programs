


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


#define DDR_Key_plus DDRB &= ~(_BV(Key_plus))
#define PIN_Key_plus PINB & _BV(Key_plus)
#define Key_plus_VCC PORTB |= _BV(Key_plus)
#define Key_plus_GND PORTB &= ~_BV(Key_plus)
#define Key_plus PB2






//-----------------------------------------------------------------------------

