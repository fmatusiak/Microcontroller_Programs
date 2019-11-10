
#define DDR_coin_we DDRD &= ~(_BV(coin_we))
#define PIN_coin_we PIND & _BV(coin_we)
#define coin_we_VCC PORTD |= _BV(coin_we)
#define coin_we_GND PORTD &= ~_BV(coin_we)
#define coin_we PD5

//#define DDR_coin_we DDRC &= ~(_BV(coin_we))
//#define PIN_coin_we PINC & _BV(coin_we)
//#define coin_we_VCC PORTC |= _BV(coin_we)
//#define coin_we_GND PORTC &= ~_BV(coin_we)
//#define coin_we PC1
//==============================================================================
#define DDR_Inhibit_Out DDRB |= _BV(Inhibit_Out)
#define PORT_Inhibit_Out_0 PORTB &= ~_BV(Inhibit_Out)
#define PORT_Inhibit_Out_1 PORTB |= _BV(Inhibit_Out)
#define PORT_Inhibit_Out_z PORTB ^= _BV(Inhibit_Out)
#define Inhibit_Out PB1

#define DDR_PULS_Out DDRC |= _BV(PULS_Out)
#define PORT_PULS_Out_1 PORTC &= ~_BV(PULS_Out)
#define PORT_PULS_Out_0 PORTC |= _BV(PULS_Out)
#define PORT_PULS_Out_z PORTC ^= _BV(PULS_Out)
#define PULS_Out PC5

//-----------------------------------------------------------------------------

