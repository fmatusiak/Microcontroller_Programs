// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3


#define DDR_KEY_1_IN DDRD &= ~(_BV(KEY_1_IN)) // IN 1
#define PIN_KEY_1_IN PIND & _BV(KEY_1_IN)
#define KEY_1_IN_VCC PORTD |= _BV(KEY_1_IN)
#define KEY_1_IN_GND PORTD &= ~_BV(KEY_1_IN)
#define KEY_1_IN PD5

#define DDR_KEY_2_IN DDRD &= ~(_BV(KEY_2_IN)) // IN 2
#define PIN_KEY_2_IN PIND & _BV(KEY_2_IN)
#define KEY_2_IN_VCC PORTD |= _BV(KEY_2_IN)
#define KEY_2_IN_GND PORTD &= ~_BV(KEY_2_IN)
#define KEY_2_IN PD6

#define DDR_KEYSWITCH_OUT DDRC |= _BV(KEYSWITCH_OUT)
#define PORT_KEYSWITCH_OUT_1 PORTC &= ~_BV(KEYSWITCH_OUT)
#define PORT_KEYSWITCH_OUT_0 PORTC |= _BV(KEYSWITCH_OUT)
#define PORT_KEYSWITCH_OUT_z PORTC ^= _BV(KEYSWITCH_OUT)
#define KEYSWITCH_OUT PC5


#define DDR_KEY_2_OUT DDRC |= _BV(KEY_2_OUT)
#define PORT_KEY_2_OUT_1 PORTC &= ~_BV(KEY_2_OUT)
#define PORT_KEY_2_OUT_0 PORTC |= _BV(KEY_2_OUT)
#define PORT_KEY_2_OUT_z PORTC ^= _BV(KEY_2_OUT)
#define KEY_2_OUT PC4


//-----------------------------------------------------------------------------

