#ifndef OPERATOR_OPERATOR_H_
#define OPERATOR_OPERATOR_H_

/*	Functions	*/
void operator_check(void);

#define DDR_SW2_IN DDRB &= ~(_BV(SW2_IN))
#define PIN_SW2_IN PINB & _BV(SW2_IN)
#define SW2_IN_VCC PORTB |= _BV(SW2_IN)
#define SW2_IN_GND PORTB &= ~_BV(SW2_IN)
#define SW2_IN PB3

#endif
