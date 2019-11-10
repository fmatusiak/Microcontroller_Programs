
#define DDR_coin_we DDRD &= ~(_BV(coin_we))
#define PIN_coin_we PIND & _BV(coin_we)
#define coin_we_VCC PORTD |= _BV(coin_we)
#define coin_we_GND PORTD &= ~_BV(coin_we)
#define coin_we PD4

//#define DDR_coin_we DDRC &= ~(_BV(coin_we))
//#define PIN_coin_we PINC & _BV(coin_we)
//#define coin_we_VCC PORTC |= _BV(coin_we)
//#define coin_we_GND PORTC &= ~_BV(coin_we)
//#define coin_we PC1
//==============================================================================


#define DDR_Inhibit_Out DDRD |= _BV(Inhibit_Out)
#define PORT_Inhibit_Out_1 PORTD &= ~_BV(Inhibit_Out)
#define PORT_Inhibit_Out_0 PORTD |= _BV(Inhibit_Out)
#define PORT_Inhibit_Out_z PORTD ^= _BV(Inhibit_Out)
#define Inhibit_Out PD5


#define DDR_Inhibit_Out_LED DDRC |= _BV(Inhibit_Out_LED)
#define PORT_Inhibit_Out_LED_0 PORTC &= ~_BV(Inhibit_Out_LED)
#define PORT_Inhibit_Out_LED_1 PORTC |= _BV(Inhibit_Out_LED)
#define PORT_Inhibit_Out_LED_z PORTC ^= _BV(Inhibit_Out_LED)
#define Inhibit_Out_LED PC2

#define DDR_Puls_Out_LED DDRC |= _BV(Puls_Out_LED)
#define PORT_Puls_Out_LED_0 PORTC &= ~_BV(Puls_Out_LED)
#define PORT_Puls_Out_LED_1 PORTC |= _BV(Puls_Out_LED)
#define PORT_Puls_Out_LED_z PORTC ^= _BV(Puls_Out_LED)
#define Puls_Out_LED PC3




//-----------------------------------------------------------------------------

