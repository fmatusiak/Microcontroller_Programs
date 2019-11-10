// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3


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

#define DDR_IN1 DDRD &= ~(_BV(IN1))
#define PIN_IN1 PIND & _BV(IN1)
#define IN1_VCC PORTD |= _BV(IN1)
#define IN1_GND PORTD &= ~_BV(IN1)
#define IN1 PD5


//-----------------------------------------------------------------------------

