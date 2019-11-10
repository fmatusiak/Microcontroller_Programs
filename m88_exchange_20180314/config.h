// DOUBLE

#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU 8000000UL
#define BAUD 9600
#define BP ((F_CPU / (BAUD * 16UL))-1)

#define C1V	1
#define C2V	1

//BTN_1
#define BT1	(1<<PB1)
	#define BT1_INIT	PORTB |= BT1
	#define BT1_DOWN	!(PINB & BT1)
//BTN_2
#define BT2	(1<<PB2)
	#define BT2_INIT	PORTB |= BT2
	#define BT2_DOWN	!(PINB & BT2)
//BTN_OPERATOR
#define BTO	(1<<PB3)
	#define BTO_INIT	PORTB |= BTO
	#define BTO_DOWN	!(PINB & BTO)
/*
// H_POWER
#define HP	(1<<PB4)
	#define HP_INIT 	DDRB |= HP
	#define HP_OFF		PORTB &= ~HP
	#define	HP_ON		PORTB |= HP
	#define HP_TOG		PORTB ^= HP
*/
//H1_MOTOR
#define H1M	(1<<PD7)
	#define H1M_INIT 	DDRD |= H1M
	#define H1M_ON		PORTD &= ~H1M
	#define	H1M_OFF		PORTD |= H1M
	#define H1M_TOG		PORTD ^= H1M
//H1_CNT
#define H1C	(1<<PD6)
	#define H1C_INIT	PORTD |= H1C
	#define H1C_DOWN	!(PIND & H1C)
//H1_E
#define H1E	(1<<PB0)
	#define H1E_INIT	PORTB |= H1E
	#define H1E_DOWN	!(PINB & H1E)


//H2_MOTOR
#define H2M	(1<<PD4)
	#define H2M_INIT 	DDRD |= H2M
	#define H2M_ON		PORTD &= ~H2M
	#define	H2M_OFF		PORTD |= H2M
	#define H2M_TOG		PORTD ^= H2M
//H2_CNT
#define H2C	(1<<PD3)
	#define H2C_INIT	PORTD |= H2C
	#define H2C_DOWN	!(PIND & H2C)
//H2_E
#define H2E	(1<<PD5)
	#define H2E_INIT	PORTD |= H2E
	#define H2E_DOWN	!(PIND & H2E)

//OUTP_LED
#define LD	(1<<PC4)
	#define LD_INIT 	DDRC |= LD
	#define LD_OFF		PORTC &= ~LD
	#define	LD_ON		PORTC |= LD
	#define LD_TOG		PORTC ^= LD
#define METER (1<<PB4)
	#define METER_INIT	DDRB |= METER
	#define METER_OFF	PORTB &= ~METER
	#define METER_ON	PORTB |= METER
	#define METER_TOG	PORTB ^=METER

void init_all(void);
void h1_on(void);
void h1_off(void);
void h2_on(void);
void h2_off(void);

void ld_blink(void);
void meter_puls(void);
void ld_void(void);




#endif /* CONFIG_H_ */
