
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


//-----------------------------------------------------------------------------

