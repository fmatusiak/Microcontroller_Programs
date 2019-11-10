
#define DDR_coin_we DDRB &= ~(_BV(coin_we))
#define PIN_coin_we PINB & _BV(coin_we)
#define coin_we_VCC PORTB |= _BV(coin_we)
#define coin_we_GND PORTB &= ~_BV(coin_we)
#define coin_we PB2


//==============================================================================
#define DDR_Inhibit_Out DDRD |= _BV(Inhibit_Out)
#define PORT_Inhibit_Out_0 PORTD &= ~_BV(Inhibit_Out)
#define PORT_Inhibit_Out_1 PORTD |= _BV(Inhibit_Out)
#define PORT_Inhibit_Out_z PORTD ^= _BV(Inhibit_Out)
#define Inhibit_Out PD2

//-----------------------------------------------------------------------------

