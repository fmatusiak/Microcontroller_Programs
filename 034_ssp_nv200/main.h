#define DDR_w_gry DDRC |= _BV(w_gry)
#define PORT_w_gry_0 PORTC &= ~_BV(w_gry)
#define PORT_w_gry_1 PORTC |= _BV(w_gry)
#define PORT_w_gry_z PORTC ^= _BV(w_gry)
#define w_gry PC5


#define DDR_puls DDRC |= _BV(puls)
#define PORT_puls_1 PORTC &= ~_BV(puls)
#define PORT_puls_0 PORTC |= _BV(puls)
#define PORT_puls_z PORTC ^= _BV(puls)
#define puls PC5

//-----------------------------------------------------------------------------






//-----------------------------------------------------------------------------
