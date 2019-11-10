
#ifndef MAIN_H_
#define MAIN_H_

#define DDR_pierwszy_we DDRD &= ~(_BV(pierwszy_we))
#define PIN_pierwszy_we PIND & _BV(pierwszy_we)
#define pierwszy_we_VCC PORTD |= _BV(pierwszy_we)
#define pierwszy_we_GND PORTD &= ~_BV(pierwszy_we)
#define pierwszy_we PD0 //ok

#define DDR_drugi_we DDRD &= ~(_BV(drugi_we))
#define PIN_drugi_we PIND & _BV(drugi_we)
#define drugi_we_VCC PORTD |= _BV(drugi_we)
#define drugi_we_GND PORTD &= ~_BV(drugi_we)
#define drugi_we PD1 //ok

#define DDR_trzeci_we DDRD &= ~(_BV(trzeci_we))
#define PIN_trzeci_we PIND & _BV(trzeci_we)
#define trzeci_we_VCC PORTD |= _BV(trzeci_we)
#define trzeci_we_GND PORTD &= ~_BV(trzeci_we)
#define trzeci_we PD2 //ok

#define DDR_czwarty_we DDRD &= ~(_BV(czwarty_we))
#define PIN_czwarty_we PIND & _BV(czwarty_we)
#define czwarty_we_VCC PORTD |= _BV(czwarty_we)
#define czwarty_we_GND PORTD &= ~_BV(czwarty_we)
#define czwarty_we PD3 //ok

#define DDR_piaty_we DDRD &= ~(_BV(piaty_we))
#define PIN_piaty_we PIND & _BV(piaty_we)
#define piaty_we_VCC PORTD |= _BV(piaty_we)
#define piaty_we_GND PORTD &= ~_BV(piaty_we)
#define piaty_we PD4 // ok


#define DDR_hopper_we DDRB &= ~(_BV(hopper_we))
#define PIN_hopper_we PINB & _BV(hopper_we)
#define hopper_we_VCC PORTB |= _BV(hopper_we)
#define hopper_we_GND PORTB &= ~_BV(hopper_we)
#define hopper_we PB0 // ok

//-----------------------------------------------------------------------------

#define DDR_syrena_wy DDRB |= _BV(syrena_wy)
#define PORT_syrena_wy_0 PORTB &= ~_BV(syrena_wy)
#define PORT_syrena_wy_1 PORTB |= _BV(syrena_wy)
#define PORT_syrena_wy_z PORTB ^= _BV(syrena_wy)
#define syrena_wy PB5

#define DDR_hopper_out DDRB |= _BV(hopper_out)
#define PORT_hopper_out_0 PORTB &= ~_BV(hopper_out)
#define PORT_hopper_out_1 PORTB |= _BV(hopper_out)
#define PORT_hopper_out_z PORTB ^= _BV(hopper_out)
#define hopper_out PB4 //ok

#define DDR_awaria_out DDRB |= _BV(awaria_out)
#define PORT_awaria_out_0 PORTB &= ~_BV(awaria_out)
#define PORT_awaria_out_1 PORTB |= _BV(awaria_out)
#define PORT_awaria_out_z PORTB ^= _BV(awaria_out)
#define awaria_out PB2 //ok


#define DDR_zezwolenie_out DDRB |= _BV(zezwolenie_out)
#define PORT_zezwolenie_out_0 PORTB &= ~_BV(zezwolenie_out)
#define PORT_zezwolenie_out_1 PORTB |= _BV(zezwolenie_out)
#define PORT_zezwolenie_out_z PORTB ^= _BV(zezwolenie_out)
#define zezwolenie_out PB1 //ok


void nabij_kase(uint8_t ile);


// ============================================================================

#endif /* MAIN_H_ */
