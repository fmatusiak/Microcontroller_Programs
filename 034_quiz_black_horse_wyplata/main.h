// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3


#define DDR_KEY_0_IN DDRD &= ~(_BV(KEY_0_IN)) // IN 1
#define PIN_KEY_0_IN PIND & _BV(KEY_0_IN)
#define KEY_0_IN_VCC PORTD |= _BV(KEY_0_IN)
#define KEY_0_IN_GND PORTD &= ~_BV(KEY_0_IN)
#define KEY_0_IN PD5

#define DDR_KEY_AG_IN DDRD &= ~(_BV(KEY_AG_IN)) // IN 2
#define PIN_KEY_AG_IN PIND & _BV(KEY_AG_IN)
#define KEY_AG_IN_VCC PORTD |= _BV(KEY_AG_IN)
#define KEY_AG_IN_GND PORTD &= ~_BV(KEY_AG_IN)
#define KEY_AG_IN PD6

#define DDR_KEY_WP_IN DDRD &= ~(_BV(KEY_WP_IN)) // IN 3
#define PIN_KEY_WP_IN PIND & _BV(KEY_WP_IN)
#define KEY_WP_IN_VCC PORTD |= _BV(KEY_WP_IN)
#define KEY_WP_IN_GND PORTD &= ~_BV(KEY_WP_IN)
#define KEY_WP_IN PD7

#define DDR_KEY_9_IN DDRB &= ~(_BV(KEY_9_IN)) // IN 4
#define PIN_KEY_9_IN PINB & _BV(KEY_9_IN)
#define KEY_9_IN_VCC PORTB |= _BV(KEY_9_IN)
#define KEY_9_IN_GND PORTB &= ~_BV(KEY_9_IN)
#define KEY_9_IN PB0


#define DDR_PAY_OUT DDRC |= _BV(PAY_OUT)
#define PORT_PAY_OUT_1 PORTC &= ~_BV(PAY_OUT)
#define PORT_PAY_OUT_0 PORTC |= _BV(PAY_OUT)
#define PORT_PAY_OUT_z PORTC ^= _BV(PAY_OUT)
#define PAY_OUT PC5


//-----------------------------------------------------------------------------

