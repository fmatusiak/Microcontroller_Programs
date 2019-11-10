// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3
#define DDR_IN_1 DDRD &= ~(_BV(IN_1))
#define PIN_IN_1 PIND & _BV(IN_1)
#define IN_1_VCC PORTD |= _BV(IN_1)
#define IN_1_GND PORTD &= ~_BV(IN_1)
#define IN_1 PD5

#define DDR_IN_2 DDRD &= ~(_BV(IN_2))
#define PIN_IN_2 PIND & _BV(IN_2)
#define IN_2_VCC PORTD |= _BV(IN_2)
#define IN_2_GND PORTD &= ~_BV(IN_2)
#define IN_2 PD6

#define DDR_IN_3 DDRD &= ~(_BV(IN_3))
#define PIN_IN_3 PIND & _BV(IN_3)
#define IN_3_VCC PORTD |= _BV(IN_3)
#define IN_3_GND PORTD &= ~_BV(IN_3)
#define IN_3 PD7

#define DDR_IN_4 DDRB &= ~(_BV(IN_4))
#define PIN_IN_4 PINB & _BV(IN_4)
#define IN_4_VCC PORTB |= _BV(IN_4)
#define IN_4_GND PORTB &= ~_BV(IN_4)
#define IN_4 PB0

#define DDR_IN_5 DDRB &= ~(_BV(IN_5))
#define PIN_IN_5 PINB & _BV(IN_5)
#define IN_5_VCC PORTB |= _BV(IN_5)
#define IN_5_GND PORTB &= ~_BV(IN_5)
#define IN_5 PB1

// ========================================================================================================



#define DDR_OUT_6 DDRC |= _BV(OUT_6)
#define PORT_OUT_6_0 PORTC &= ~_BV(OUT_6)
#define PORT_OUT_6_1 PORTC |= _BV(OUT_6)
#define PORT_OUT_6_z PORTC ^= _BV(OUT_6)
#define OUT_6 PC0


#define DDR_OUT_1 DDRC |= _BV(OUT_1)
#define PORT_OUT_1_0 PORTC &= ~_BV(OUT_1)
#define PORT_OUT_1_1 PORTC |= _BV(OUT_1)
#define PORT_OUT_1_z PORTC ^= _BV(OUT_1)
#define OUT_1 PC5


//-----------------------------------------------------------------------------

