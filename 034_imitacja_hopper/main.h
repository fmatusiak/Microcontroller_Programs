// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3

#define DDR_KEY_SWITCH_IN DDRD &= ~(_BV(KEY_SWITCH_IN)) // IN 3
#define PIN_KEY_SWITCH_IN PIND & _BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN_VCC PORTD |= _BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN_GND PORTD &= ~_BV(KEY_SWITCH_IN)
#define KEY_SWITCH_IN PD7



#define DDR_MOTOR_HOPPER_CONTROL_IN DDRB &= ~(_BV(MOTOR_HOPPER_CONTROL_IN)) // IN 4
#define PIN_MOTOR_HOPPER_CONTROL_IN PINB & _BV(MOTOR_HOPPER_CONTROL_IN)
#define MOTOR_HOPPER_CONTROL_IN_VCC PORTB |= _BV(MOTOR_HOPPER_CONTROL_IN)
#define MOTOR_HOPPER_CONTROL_IN_GND PORTB &= ~_BV(MOTOR_HOPPER_CONTROL_IN)
#define MOTOR_HOPPER_CONTROL_IN PB0


// ========================================================================================================


#define DDR_PAYOUT_OUT DDRC |=  _BV(PAYOUT_OUT)//Out1
#define PORT_PAYOUT_OUT_0 PORTC &= ~_BV(PAYOUT_OUT)
#define PORT_PAYOUT_OUT_1 PORTC |= _BV(PAYOUT_OUT)
#define PORT_PAYOUT_OUT_z PORTC ^= _BV(PAYOUT_OUT)
#define PAYOUT_OUT PC5

#define DDR_HOPPER_COIN_OUT DDRC |=  _BV(HOPPER_COIN_OUT)//OUT2
#define HOPPER_PULS_OUT_LOW PORTC &= ~_BV(HOPPER_COIN_OUT)
#define HOPPER_PULS_OUT_HIGH PORTC |= _BV(HOPPER_COIN_OUT)
#define PORT_HOPPER_COIN_OUT_z PORTC ^= _BV(HOPPER_COIN_OUT)
#define HOPPER_COIN_OUT PC4


//-----------------------------------------------------------------------------

