// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3

#define DDR_BUTTON_IN DDRD &= ~(_BV(BUTTON_IN)) // IN 1
#define PIN_BUTTON_IN PIND & _BV(BUTTON_IN)
#define BUTTON_IN_VCC PORTD |= _BV(BUTTON_IN)
#define BUTTON_IN_GND PORTD &= ~_BV(BUTTON_IN)
#define BUTTON_IN PD5



#define DDR_DOOR_IN DDRD &= ~(_BV(DOOR_IN)) // IN 3
#define PIN_DOOR_IN PIND & _BV(DOOR_IN)
#define DOOR_IN_VCC PORTD |= _BV(DOOR_IN)
#define DOOR_IN_GND PORTD &= ~_BV(DOOR_IN)
#define DOOR_IN PD7



#define DDR_BARMAN_IN DDRB &= ~(_BV(BARMAN_IN)) // IN 4
#define PIN_BARMAN_IN PINB & _BV(BARMAN_IN)
#define BARMAN_IN_VCC PORTB |= _BV(BARMAN_IN)
#define BARMAN_IN_GND PORTB &= ~_BV(BARMAN_IN)
#define BARMAN_IN PB0


// ========================================================================================================


#define DDR_LED_PLUS_OUT DDRC |=  _BV(LED_PLUS_OUT) //OUT6
#define PORT_LED_PLUS_OUT_0 PORTC &= ~_BV(LED_PLUS_OUT)
#define PORT_LED_PLUS_OUT_1 PORTC |= _BV(LED_PLUS_OUT)
#define PORT_LED_PLUS_OUT_z PORTC ^= _BV(LED_PLUS_OUT)
#define LED_PLUS_OUT PC0


#define DDR_PILOT_OFF_OUT DDRC |=  _BV(PILOT_OFF_OUT)//Out1
#define PORT_PILOT_OFF_OUT_0 PORTC &= ~_BV(PILOT_OFF_OUT)
#define PORT_PILOT_OFF_OUT_1 PORTC |= _BV(PILOT_OFF_OUT)
#define PORT_PILOT_OFF_OUT_z PORTC ^= _BV(PILOT_OFF_OUT)
#define PILOT_OFF_OUT PC5

#define DDR_PILOT_ON_OUT DDRC |=  _BV(PILOT_ON_OUT)//OUT2
#define PORT_PILOT_ON_OUT_0 PORTC &= ~_BV(PILOT_ON_OUT)
#define PORT_PILOT_ON_OUT_1 PORTC |= _BV(PILOT_ON_OUT)
#define PORT_PILOT_ON_OUT_z PORTC ^= _BV(PILOT_ON_OUT)
#define PILOT_ON_OUT PC4


//-----------------------------------------------------------------------------

