// 6 in lcd
// 2 in coins
// 2 in buttons
// 1 in switch

// 2 out control

// 1 cctalk





#define DDR_VEND1_IN DDRD &= ~(_BV(VEND1_IN)) // IN 1
#define PIN_VEND1_IN PIND & _BV(VEND1_IN)
#define VEND1_IN_VCC PORTD |= _BV(VEND1_IN)
#define VEND1_IN_GND PORTD &= ~_BV(VEND1_IN)
#define VEND1_IN PD5

#define DDR_VEND2_IN DDRD &= ~(_BV(VEND2_IN)) // IN 2
#define PIN_VEND2_IN PIND & _BV(VEND2_IN)
#define VEND2_IN_VCC PORTD |= _BV(VEND2_IN)
#define VEND2_IN_GND PORTD &= ~_BV(VEND2_IN)
#define VEND2_IN PD6

#define DDR_VEND3_IN DDRD &= ~(_BV(VEND3_IN)) // IN 3
#define PIN_VEND3_IN PIND & _BV(VEND3_IN)
#define VEND3_IN_VCC PORTD |= _BV(VEND3_IN)
#define VEND3_IN_GND PORTD &= ~_BV(VEND3_IN)
#define VEND3_IN PD7

#define DDR_VEND4_IN DDRB &= ~(_BV(VEND4_IN)) // IN 4
#define PIN_VEND4_IN PINB & _BV(VEND4_IN)
#define VEND4_IN_VCC PORTB |= _BV(VEND4_IN)
#define VEND4_IN_GND PORTB &= ~_BV(VEND4_IN)
#define VEND4_IN PB0

#define DDR_VEND5_IN DDRB &= ~(_BV(VEND5_IN)) // IN 5
#define PIN_VEND5_IN PINB & _BV(VEND5_IN)
#define VEND5_IN_VCC PORTB |= _BV(VEND5_IN)
#define VEND5_IN_GND PORTB &= ~_BV(VEND5_IN)
#define VEND5_IN PB1




// ========================================================================================================

#define DDR_puls DDRC |= _BV(puls)
#define PORT_puls_1 PORTC &= ~_BV(puls)
#define PORT_puls_0 PORTC |= _BV(puls)
#define PORT_puls_z PORTC ^= _BV(puls)
#define puls PC5

#define DDR_puls_2 DDRC |= _BV(puls_2)
#define PORT_puls_2_1 PORTC &= ~_BV(puls_2)
#define PORT_puls_2_0 PORTC |= _BV(puls_2)
#define PORT_puls_2_z PORTC ^= _BV(puls_2)
#define puls_2 PC0




//-----------------------------------------------------------------------------

