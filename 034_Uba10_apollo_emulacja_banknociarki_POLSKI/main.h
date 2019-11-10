


#define DDR_IN1_IN DDRD &= ~(_BV(IN1_IN)) // IN 1
#define PIN_IN1_IN PIND & _BV(IN1_IN)
#define IN1_IN_VCC PORTD |= _BV(IN1_IN)
#define IN1_IN_GND PORTD &= ~_BV(IN1_IN)
#define IN1_IN PD5
