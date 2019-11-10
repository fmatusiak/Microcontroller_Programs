// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3


#define DDR_KANAL_1_IN DDRD &= ~(_BV(KANAL_1_IN)) // IN 1
#define PIN_KANAL_1_IN PIND & _BV(KANAL_1_IN)
#define KANAL_1_IN_VCC PORTD |= _BV(KANAL_1_IN)
#define KANAL_1_IN_GND PORTD &= ~_BV(KANAL_1_IN)
#define KANAL_1_IN PD5

#define DDR_KANAL_2_IN DDRD &= ~(_BV(KANAL_2_IN)) // IN 2
#define PIN_KANAL_2_IN PIND & _BV(KANAL_2_IN)
#define KANAL_2_IN_VCC PORTD |= _BV(KANAL_2_IN)
#define KANAL_2_IN_GND PORTD &= ~_BV(KANAL_2_IN)
#define KANAL_2_IN PD6

#define DDR_KANAL_3_IN DDRD &= ~(_BV(KANAL_3_IN)) // IN 3
#define PIN_KANAL_3_IN PIND & _BV(KANAL_3_IN)
#define KANAL_3_IN_VCC PORTD |= _BV(KANAL_3_IN)
#define KANAL_3_IN_GND PORTD &= ~_BV(KANAL_3_IN)
#define KANAL_3_IN PD7

#define DDR_KANAL_4_IN DDRB &= ~(_BV(KANAL_4_IN)) // IN 4
#define PIN_KANAL_4_IN PINB & _BV(KANAL_4_IN)
#define KANAL_4_IN_VCC PORTB |= _BV(KANAL_4_IN)
#define KANAL_4_IN_GND PORTB &= ~_BV(KANAL_4_IN)
#define KANAL_4_IN PB0


#define DDR_PULS_1_OUT DDRC |= _BV(PULS_1_OUT)
#define PORT_PULS_1_OUT_1 PORTC &= ~_BV(PULS_1_OUT)
#define PORT_PULS_1_OUT_0 PORTC |= _BV(PULS_1_OUT)
#define PORT_PULS_1_OUT_z PORTC ^= _BV(PULS_1_OUT)
#define PULS_1_OUT PC5


#define DDR_PULS_2_OUT DDRC |= _BV(PULS_2_OUT)
#define PORT_PULS_2_OUT_1 PORTC &= ~_BV(PULS_2_OUT)
#define PORT_PULS_2_OUT_0 PORTC |= _BV(PULS_2_OUT)
#define PORT_PULS_2_OUT_z PORTC ^= _BV(PULS_2_OUT)
#define PULS_2_OUT PC4


//-----------------------------------------------------------------------------

