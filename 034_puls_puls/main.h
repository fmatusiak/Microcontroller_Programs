// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3

/*
#define DDR_COUNTER_IN DDRD &= ~(_BV(COUNTER_IN)) // IN 3
#define PIN_COUNTER_IN PIND & _BV(COUNTER_IN)
#define COUNTER_IN_VCC PORTD |= _BV(COUNTER_IN)
#define COUNTER_IN_GND PORTD &= ~_BV(COUNTER_IN)
#define COUNTER_IN PD7
*/

/*
#define DDR_START_IN DDRB &= ~(_BV(START_IN)) // IN 4
#define PIN_START_IN PINB & _BV(START_IN)
#define START_IN_VCC PORTB |= _BV(START_IN)
#define START_IN_GND PORTB &= ~_BV(START_IN)
#define START_IN PB0
*/


#define DDR_SWITCH_IN DDRD &= ~(_BV(SWITCH_IN)) // IN 6
#define PIN_SWITCH_IN PIND & _BV(SWITCH_IN)
#define SWITCH_IN_VCC PORTD |= _BV(SWITCH_IN)
#define SWITCH_IN_GND PORTD &= ~_BV(SWITCH_IN)
#define SWITCH_IN PD6


// ========================================================================================================

/*
#define DDR_START_OUT DDRD |= _BV(START_OUT)
#define PORT_START_OUT_0 PORTD &= ~_BV(START_OUT) // tX3
#define PORT_START_OUT_1 PORTD |= _BV(START_OUT)
#define PORT_START_OUT_z PORTD ^= _BV(START_OUT)
#define START_OUT PD2

*/


/*
#define DDR_START_OUT DDRD |= _BV(START_OUT)
#define PORT_START_OUT_0 PORTD |= _BV(START_OUT)  // tX3
#define PORT_START_OUT_1 PORTD &= ~_BV(START_OUT)
#define PORT_START_OUT_z PORTD ^= _BV(START_OUT)
#define START_OUT PD2
*/


#define DDR_LED_ONE_OUT DDRC |= _BV(LED_ONE_OUT)
#define PORT_LED_ONE_OUT_0 PORTC &= ~_BV(LED_ONE_OUT)
#define PORT_LED_ONE_OUT_1 PORTC |= _BV(LED_ONE_OUT)
#define PORT_LED_ONE_OUT_z PORTC ^= _BV(LED_ONE_OUT)
#define LED_ONE_OUT PC0


#define DDR_LED_TWO_OUT DDRB |= _BV(LED_TWO_OUT)
#define PORT_LED_TWO_OUT_0 PORTB &= ~_BV(LED_TWO_OUT)
#define PORT_LED_TWO_OUT_1 PORTB |= _BV(LED_TWO_OUT)
#define PORT_LED_TWO_OUT_z PORTB ^= _BV(LED_TWO_OUT)
#define LED_TWO_OUT PB0


#define DDR_RELAY_OUT DDRC |= _BV(RELAY_OUT)
#define PORT_RELAY_OUT_0 PORTC &= ~_BV(RELAY_OUT)
#define PORT_RELAY_OUT_1 PORTC |= _BV(RELAY_OUT)
#define PORT_RELAY_OUT_z PORTC ^= _BV(RELAY_OUT)
#define RELAY_OUT PC5


//-----------------------------------------------------------------------------

