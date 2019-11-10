#ifndef MAIN_H_
#define MAIN_H_




#define DDR_dwojka_wy DDRD |= _BV(dwojka_wy)
#define PORT_dwojka_wy_0 PORTD &= ~_BV(dwojka_wy)
#define PORT_dwojka_wy_1 PORTD |= _BV(dwojka_wy)
#define PORT_dwojka_wy_z PORTD ^= _BV(dwojka_wy)
#define dwojka_wy PD5




//--------------------------
//-----------------------------------------------------------------------------



#endif /* MAIN_H_ */
