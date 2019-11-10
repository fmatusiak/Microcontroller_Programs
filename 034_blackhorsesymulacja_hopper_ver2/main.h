
#define DDR_wyplata_we DDRC &= ~(_BV(wyplata_we))
#define PIN_wyplata_we PINC & _BV(wyplata_we)
#define wyplata_we_VCC PORTC |= _BV(wyplata_we)
#define wyplata_we_GND PORTC &= ~_BV(wyplata_we)
#define wyplata_we PC2



#define DDR_switch_we DDRD &= ~(_BV(switch_we))
#define PIN_switch_we PIND & _BV(switch_we)
#define switch_we_VCC PORTD |= _BV(switch_we)
#define switch_we_GND PORTD &= ~_BV(switch_we)
#define switch_we PD2
//==============================================================================

#define DDR_coin DDRC |= _BV(coin)
#define PORT_coin_0 PORTC &= ~_BV(coin)
#define PORT_coin_1 PORTC |= _BV(coin)
#define PORT_coin_z PORTC ^= _BV(coin)
#define coin PC3



#define DDR_kanal_3w DDRB |= _BV(kanal_3w)
#define PORT_kanal_3w_0 PORTB &= ~_BV(kanal_3w)
#define PORT_kanal_3w_1 PORTB |= _BV(kanal_3w)
#define PORT_kanal_3w_z PORTB ^= _BV(kanal_3w)
#define kanal_3w PB3


#define DDR_nabij DDRC |= _BV(nabij)
#define PORT_nabij_0 PORTC &= ~_BV(nabij)
#define PORT_nabij_1 PORTC |= _BV(nabij)
#define PORT_nabij_z PORTC ^= _BV(nabij)
#define nabij PC1


//-----------------------------------------------------------------------------

