// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3

#define DDR_INHIBIT_IN DDRB &= ~(_BV(INHIBIT_IN)) // IN 6
#define PIN_INHIBIT_IN PINB & _BV(INHIBIT_IN)
#define INHIBIT_IN_VCC PORTB |= _BV(INHIBIT_IN)
#define INHIBIT_IN_GND PORTB &= ~_BV(INHIBIT_IN)
#define INHIBIT_IN PB2


// ========================================================================================================


#define DDR_LINE1_OUT DDRD |= _BV(LINE1_OUT)
#define PORT_LINE1_OUT_1 PORTD |= _BV(LINE1_OUT)  //In1
#define PORT_LINE1_OUT_0 PORTD &= ~_BV(LINE1_OUT)
#define PORT_LINE1_OUT_z PORTD ^= _BV(LINE1_OUT)
#define LINE1_OUT PD5//PayOut
//-----------------------------------------------------------------------------

#define DDR_LINE2_OUT DDRD |= _BV(LINE2_OUT)
#define PORT_LINE2_OUT_1 PORTD |= _BV(LINE2_OUT)  //In2
#define PORT_LINE2_OUT_0 PORTD &= ~_BV(LINE2_OUT)
#define PORT_LINE2_OUT_z PORTD ^= _BV(LINE2_OUT)
#define LINE2_OUT PD6//PayOut

#define DDR_LINE3_OUT DDRD |= _BV(LINE3_OUT)
#define PORT_LINE3_OUT_1 PORTD |= _BV(LINE3_OUT)  //In3
#define PORT_LINE3_OUT_0 PORTD &= ~_BV(LINE3_OUT)
#define PORT_LINE3_OUT_z PORTD ^= _BV(LINE3_OUT)
#define LINE3_OUT PD7//PayOut

#define DDR_LINE4_OUT DDRB |= _BV(LINE4_OUT)
#define PORT_LINE4_OUT_1 PORTB |= _BV(LINE4_OUT)  //In4
#define PORT_LINE4_OUT_0 PORTB &= ~_BV(LINE4_OUT)
#define PORT_LINE4_OUT_z PORTB ^= _BV(LINE4_OUT)
#define LINE4_OUT PB0//PayOut

#define DDR_LINE1_COIN_OUT DDRB |= _BV(LINE1_COIN_OUT)
#define PORT_LINE1_COIN_OUT_1 PORTB |= _BV(LINE1_COIN_OUT)  //In5
#define PORT_LINE1_COIN_OUT_0 PORTB &= ~_BV(LINE1_COIN_OUT)
#define PORT_LINE1_COIN_OUT_z PORTB ^= _BV(LINE1_COIN_OUT)
#define LINE1_COIN_OUT PB1//PayOut

#define DDR_INHIBIT_LED DDRC |= _BV(INHIBIT_LED)
#define PORT_INHIBIT_LED_1 PORTC |= _BV(INHIBIT_LED)  //In7
#define PORT_INHIBIT_LED_0 PORTC &= ~_BV(INHIBIT_LED)
#define PORT_INHIBIT_LED_z PORTC ^= _BV(INHIBIT_LED)
#define INHIBIT_LED PC5//PayOut

#define DDR_PULS_LED DDRC |= _BV(PULS_LED)
#define PORT_PULS_LED_1 PORTC |= _BV(PULS_LED)  //In9
#define PORT_PULS_LED_0 PORTC &= ~_BV(PULS_LED)
#define PORT_PULS_LED_z PORTC ^= _BV(PULS_LED)
#define PULS_LED PC3//PayOut
