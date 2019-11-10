// 6 in lcd
// 1 in przyciks start
// 1 in licznik
// 1 in zarowka
// 1 in stacyjka
// 1 out start_pc pd3

#define DDR_LINE1_IN DDRD &= ~(_BV(LINE1_IN)) // IN 1
#define PIN_LINE1_IN PIND & _BV(LINE1_IN)
#define LINE1_IN_VCC PORTD |= _BV(LINE1_IN)
#define LINE1_IN_GND PORTD &= ~_BV(LINE1_IN)
#define LINE1_IN PD5



// ========================================================================================================



#define DDR_LINE1_OUT DDRC |= _BV(LINE1_OUT)
#define PORT_LINE1_OUT_1 PORTC |= _BV(LINE1_OUT)  //In6
#define PORT_LINE1_OUT_0 PORTC &= ~_BV(LINE1_OUT)
#define PORT_LINE1_OUT_z PORTC ^= _BV(LINE1_OUT)
#define LINE1_OUT PC5//PayOut
//-----------------------------------------------------------------------------

#define DDR_LINE2_OUT DDRC |= _BV(LINE2_OUT)
#define PORT_LINE2_OUT_1 PORTC |= _BV(LINE2_OUT)  //In6
#define PORT_LINE2_OUT_0 PORTC &= ~_BV(LINE2_OUT)
#define PORT_LINE2_OUT_z PORTC ^= _BV(LINE2_OUT)
#define LINE2_OUT PC4//PayOut

#define DDR_LINE3_OUT DDRC |= _BV(LINE3_OUT)
#define PORT_LINE3_OUT_1 PORTC |= _BV(LINE3_OUT)  //In6
#define PORT_LINE3_OUT_0 PORTC &= ~_BV(LINE3_OUT)
#define PORT_LINE3_OUT_z PORTC ^= _BV(LINE3_OUT)
#define LINE3_OUT PC3//PayOut

#define DDR_LINE4_OUT DDRC |= _BV(LINE4_OUT)
#define PORT_LINE4_OUT_1 PORTC |= _BV(LINE4_OUT)  //In6
#define PORT_LINE4_OUT_0 PORTC &= ~_BV(LINE4_OUT)
#define PORT_LINE4_OUT_z PORTC ^= _BV(LINE4_OUT)
#define LINE4_OUT PC2//PayOut
