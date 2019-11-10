// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3

#define DDR_LINE1_IN DDRD &= ~(_BV(LINE1_IN)) // IN 1
#define PIN_LINE1_IN PIND & _BV(LINE1_IN)
#define LINE1_IN_VCC PORTD |= _BV(LINE1_IN)
#define LINE1_IN_GND PORTD &= ~_BV(LINE1_IN)
#define LINE1_IN PD5

#define DDR_LINE2_IN DDRD &= ~(_BV(LINE2_IN)) // IN 2
#define PIN_LINE2_IN PIND & _BV(LINE2_IN)
#define LINE2_IN_VCC PORTD |= _BV(LINE2_IN)
#define LINE2_IN_GND PORTD &= ~_BV(LINE2_IN)
#define LINE2_IN PD6

#define DDR_LINE3_IN DDRD &= ~(_BV(LINE3_IN)) // IN 3
#define PIN_LINE3_IN PIND & _BV(LINE3_IN)
#define LINE3_IN_VCC PORTD |= _BV(LINE3_IN)
#define LINE3_IN_GND PORTD &= ~_BV(LINE3_IN)
#define LINE3_IN PD7

#define DDR_LINE4_IN DDRB &= ~(_BV(LINE4_IN)) // IN 4
#define PIN_LINE4_IN PINB & _BV(LINE4_IN)
#define LINE4_IN_VCC PORTB |= _BV(LINE4_IN)
#define LINE4_IN_GND PORTB &= ~_BV(LINE4_IN)
#define LINE4_IN PB0

#define DDR_COIN_IN DDRB &= ~(_BV(COIN_IN)) // IN 5
#define PIN_COIN_IN PINB & _BV(COIN_IN)
#define COIN_IN_VCC PORTB |= _BV(COIN_IN)
#define COIN_IN_GND PORTB &= ~_BV(COIN_IN)
#define COIN_IN PB2

#define DDR_SERVICE_IN DDRB &= ~(_BV(SERVICE_IN)) // IN 6
#define PIN_SERVICE_IN PINB & _BV(SERVICE_IN)
#define SERVICE_IN_VCC PORTB |= _BV(SERVICE_IN)
#define SERVICE_IN_GND PORTB &= ~_BV(SERVICE_IN)
#define SERVICE_IN PB1


// ========================================================================================================

#define DDR_HOPPER_MOTOR_OUT DDRC |= _BV(HOPPER_MOTOR_OUT)
#define PORT_HOPPER_MOTOR_OUT_0 PORTC |= _BV(HOPPER_MOTOR_OUT)  //
#define PORT_HOPPER_MOTOR_OUT_1 PORTC &= ~_BV(HOPPER_MOTOR_OUT)
#define PORT_HOPPER_MOTOR_OUT_z PORTC ^= _BV(HOPPER_MOTOR_OUT)
#define HOPPER_MOTOR_OUT PC5//

#define DDR_INHIBIT_OUT_OUT DDRC |= _BV(INHIBIT_OUT)
#define PORT_INHIBIT_OUT_0 PORTC |= _BV(INHIBIT_OUT)  //
#define PORT_INHIBIT_OUT_1 PORTC &= ~_BV(INHIBIT_OUT)
#define INHIBIT_OUT PC4//



//-----------------------------------------------------------------------------

