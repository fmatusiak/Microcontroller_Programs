
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
#define DDR_LED_CCTALKT DDRC |= _BV(LED_CCTALKT)
#define PORT_LED_CCTALKT_0 PORTC &= ~_BV(LED_CCTALKT)
#define PORT_LED_CCTALKT_1 PORTC |= _BV(LED_CCTALKT)
#define PORT_LED_CCTALKT_z PORTC ^= _BV(LED_CCTALKT)
#define LED_CCTALKT PC5

//-----------------------------------------------------------------------------

