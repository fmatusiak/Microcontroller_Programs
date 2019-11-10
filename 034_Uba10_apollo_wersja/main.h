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

#define DDR_puls DDRC |= _BV(puls)
#define PORT_puls_0 PORTC &= ~_BV(puls)
#define PORT_puls_1 PORTC |= _BV(puls)
#define PORT_puls_z PORTC ^= _BV(puls)
#define puls PC5



#define DDR_IN1_IN DDRD &= ~(_BV(IN1_IN)) // IN 1
#define PIN_IN1_IN PIND & _BV(IN1_IN)
#define IN1_IN_VCC PORTD |= _BV(IN1_IN)
#define IN1_IN_GND PORTD &= ~_BV(IN1_IN)
#define IN1_IN PD5
