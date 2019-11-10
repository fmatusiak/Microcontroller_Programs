#define DDR_puls DDRC |= _BV(puls)
#define PORT_puls_0 PORTC &= ~_BV(puls)
#define PORT_puls_1 PORTC |= _BV(puls)
#define PORT_puls_z PORTC ^= _BV(puls)
#define puls PC0

