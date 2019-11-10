
#define DDR_coin_we DDRB &= ~(_BV(coin_we))
#define PIN_coin_we PINB & _BV(coin_we)
#define coin_we_VCC PORTB |= _BV(coin_we)
#define coin_we_GND PORTB &= ~_BV(coin_we)
#define coin_we PB2

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

//-----------------------------------------------------------------------------

