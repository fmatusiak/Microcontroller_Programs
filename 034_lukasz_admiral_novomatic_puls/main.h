// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3


 #define DDR_COUNTER_IN DDRD &= ~(_BV(COUNTER_IN)) // IN 3
 #define PIN_COUNTER_IN PIND & _BV(COUNTER_IN)
 #define COUNTER_IN_VCC PORTD |= _BV(COUNTER_IN)
 #define COUNTER_IN_GND PORTD &= ~_BV(COUNTER_IN)
 #define COUNTER_IN PD7



#define DDR_START_IN DDRB &= ~(_BV(START_IN)) // IN 4
#define PIN_START_IN PINB & _BV(START_IN)
#define START_IN_VCC PORTB |= _BV(START_IN)
#define START_IN_GND PORTB &= ~_BV(START_IN)
#define START_IN PB0


#define DDR_SWITCH_IN DDRB &= ~(_BV(SWITCH_IN)) // IN 6
#define PIN_SWITCH_IN PINB & _BV(SWITCH_IN)
#define SWITCH_IN_VCC PORTB |= _BV(SWITCH_IN)
#define SWITCH_IN_GND PORTB &= ~_BV(SWITCH_IN)
#define SWITCH_IN PB2

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

#define DDR_OUT_6 DDRC |= _BV(OUT_6)
#define PORT_OUT_6_1 PORTC &= ~_BV(OUT_6)
#define PORT_OUT_6_0 PORTC |= _BV(OUT_6)
#define PORT_OUT_6_z PORTC ^= _BV(OUT_6)
#define OUT_6 PC0

#define DDR_OUT_5 DDRC |= _BV(OUT_5)
#define PORT_OUT_5_1 PORTC &= ~_BV(OUT_5)
#define PORT_OUT_5_0 PORTC |= _BV(OUT_5)
#define PORT_OUT_5_z PORTC ^= _BV(OUT_5)
#define OUT_5 PC1

#define DDR_OUT_4 DDRC |= _BV(OUT_4)
#define PORT_OUT_4_1 PORTC &= ~_BV(OUT_4)
#define PORT_OUT_4_0 PORTC |= _BV(OUT_4)
#define PORT_OUT_4_z PORTC ^= _BV(OUT_4)
#define OUT_4 PC2

//-----------------------------------------------------------------------------

