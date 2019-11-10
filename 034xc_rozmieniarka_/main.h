// 6 in lcd
// 2 in coins
// 2 in buttons
// 1 in switch

// 2 out control

// 1 cctalk





#define DDR_BUTTON1_IN DDRD &= ~(_BV(BUTTON1_IN)) // IN 1
#define PIN_BUTTON1_IN PIND & _BV(BUTTON1_IN)
#define BUTTON1_IN_VCC PORTD |= _BV(BUTTON1_IN)
#define BUTTON1_IN_GND PORTD &= ~_BV(BUTTON1_IN)
#define BUTTON1_IN PD5

#define DDR_BUTTON2_IN DDRD &= ~(_BV(BUTTON2_IN)) // IN 2
#define PIN_BUTTON2_IN PIND & _BV(BUTTON2_IN)
#define BUTTON2_IN_VCC PORTD |= _BV(BUTTON2_IN)
#define BUTTON2_IN_GND PORTD &= ~_BV(BUTTON2_IN)
#define BUTTON2_IN PD6

#define DDR_SWITCH_IN DDRD &= ~(_BV(SWITCH_IN)) // IN 3
#define PIN_SWITCH_IN PIND & _BV(SWITCH_IN)
#define SWITCH_IN_VCC PORTD |= _BV(SWITCH_IN)
#define SWITCH_IN_GND PORTD &= ~_BV(SWITCH_IN)
#define SWITCH_IN PD7

#define DDR_COIN1_IN DDRB &= ~(_BV(COIN1_IN)) // IN 4
#define PIN_COIN1_IN PINB & _BV(COIN1_IN)
#define COIN1_IN_VCC PORTB |= _BV(COIN1_IN)
#define COIN1_IN_GND PORTB &= ~_BV(COIN1_IN)
#define COIN1_IN PB0

#define DDR_COIN2_IN DDRB &= ~(_BV(COIN2_IN)) // IN 5
#define PIN_COIN2_IN PINB & _BV(COIN2_IN)
#define COIN2_IN_VCC PORTB |= _BV(COIN2_IN)
#define COIN2_IN_GND PORTB &= ~_BV(COIN2_IN)
#define COIN2_IN PB1




// ========================================================================================================

#define DDR_HOPPERON1_OUT DDRB |= _BV(HOPPERON1_OUT) // IN 6
#define PORT_HOPPERON1_OUT_0 PORTB &= ~_BV(HOPPERON1_OUT)
#define PORT_HOPPERON1_OUT_1 PORTB |= _BV(HOPPERON1_OUT)
#define PORT_HOPPERON1_OUT_z PORTB ^= _BV(HOPPERON1_OUT)
#define HOPPERON1_OUT PB2

#define DDR_HOPPERON2_OUT DDRD |= _BV(HOPPERON2_OUT)
#define PORT_HOPPERON2_OUT_0 PORTD &= ~_BV(HOPPERON2_OUT) // TX3
#define PORT_HOPPERON2_OUT_1 PORTD |= _BV(HOPPERON2_OUT)
#define PORT_HOPPERON2_OUT_z PORTD ^= _BV(HOPPERON2_OUT)
#define HOPPERON2_OUT PD2



//-----------------------------------------------------------------------------

