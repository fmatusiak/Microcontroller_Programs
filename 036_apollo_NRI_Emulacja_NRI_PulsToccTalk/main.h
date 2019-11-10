
#define DDR_coin_we DDRD &= ~(_BV(coin_we))
#define PIN_coin_we PIND & _BV(coin_we)
#define coin_we_VCC PORTD |= _BV(coin_we)
#define coin_we_GND PORTD &= ~_BV(coin_we)
#define coin_we PD4

#define DDR_coin_we_2 DDRD &= ~(_BV(coin_we_2))
#define PIN_coin_we_2 PIND & _BV(coin_we_2)
#define coin_we_2_VCC PORTD |= _BV(coin_we_2)
#define coin_we_2_GND PORTD &= ~_BV(coin_we_2)
#define coin_we_2 PD6
//==============================================================================


#define DDR_Inhibit_Out DDRD |= _BV(Inhibit_Out)
#define PORT_Inhibit_Out_1 PORTD &= ~_BV(Inhibit_Out)
#define PORT_Inhibit_Out_0 PORTD |= _BV(Inhibit_Out)
#define PORT_Inhibit_Out_z PORTD ^= _BV(Inhibit_Out)
#define Inhibit_Out PD5

#define DDR_Inhibit_Out_NRI DDRB |= _BV(Inhibit_Out_NRI)
#define PORT_Inhibit_Out_NRI_1 PORTB &= ~_BV(Inhibit_Out_NRI)
#define PORT_Inhibit_Out_NRI_0 PORTB |= _BV(Inhibit_Out_NRI)
#define PORT_Inhibit_Out_NRI_z PORTB ^= _BV(Inhibit_Out_NRI)
#define Inhibit_Out_NRI PB1


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

