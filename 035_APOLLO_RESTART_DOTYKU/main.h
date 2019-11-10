// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3





#define DDR_PULS_LED DDRC |= _BV(PULS_LED)
#define PORT_PULS_LED_1 PORTC |= _BV(PULS_LED)  //In9
#define PORT_PULS_LED_0 PORTC &= ~_BV(PULS_LED)
#define PORT_PULS_LED_z PORTC ^= _BV(PULS_LED)
#define PULS_LED PC0//PayOut
