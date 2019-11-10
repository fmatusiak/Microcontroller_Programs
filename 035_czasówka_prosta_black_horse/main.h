// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3

#define DDR_COUNTER_IN DDRD &= ~(_BV(COUNTER_IN)) // IN 1
#define PIN_COUNTER_IN PIND & _BV(COUNTER_IN)
#define COUNTER_IN_VCC PORTD |= _BV(COUNTER_IN)
#define COUNTER_IN_GND PORTD &= ~_BV(COUNTER_IN)
#define COUNTER_IN PD5


#define DDR_keySwitch_IN DDRD &= ~(_BV(keySwitch_IN)) // IN 3
#define PIN_keySwitch_IN PIND & _BV(keySwitch_IN)
#define keySwitch_IN_VCC PORTD |= _BV(keySwitch_IN)
#define keySwitch_IN_GND PORTD &= ~_BV(keySwitch_IN)
#define keySwitch_IN PD7//keySwitch

// ========================================================================================================



#define DDR_PayOut_OUT DDRB |= _BV(PayOut_OUT)
#define PORT_PayOut_OUT_1 PORTB |= _BV(PayOut_OUT)  //In6
#define PORT_PayOut_OUT_0 PORTB &= ~_BV(PayOut_OUT)
#define PORT_PayOut_OUT_z PORTB ^= _BV(PayOut_OUT)
#define PayOut_OUT PB2//PayOut
//-----------------------------------------------------------------------------

