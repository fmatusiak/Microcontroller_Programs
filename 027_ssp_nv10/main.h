

#define DDR_kanal_1_we DDRC &= ~(_BV(kanal_1_we))
#define PIN_kanal_1_we PINC & _BV(kanal_1_we)
#define kanal_1_we_VCC PORTC |= _BV(kanal_1_we)
#define kanal_1_we_GND PORTC &= ~_BV(kanal_1_we)
#define kanal_1_we PC0 // ok


//==============================================================================


#define DDR_banknociarka_wy DDRD |= _BV(banknociarka_wy)
#define PORT_banknociarka_wy_0 PORTD &= ~_BV(banknociarka_wy)
#define PORT_banknociarka_wy_1 PORTD |= _BV(banknociarka_wy)
#define PORT_banknociarka_wy_z PORTD ^= _BV(banknociarka_wy)
#define banknociarka_wy PD1

//-----------------------------------------------------------------------------
