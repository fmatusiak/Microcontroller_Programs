#ifndef INIT_INIT_H_
#define INIT_INIT_H_

/*	COIN VALUE	*/
#define COIN_VAL 	2	// 1 =1PLN; 2 =2PLN; 5 =5PLN
#define HOPPER_TIME	38	// 3.8/s (38->10s; 47->15s; 72->20s; 190->30s)
#define COUNTER_TIME 33
#define EMP_DETECTION_TIME 15
#define COIN_IMPULSE_TIME 100

/*	BNC	*/
#define VEND1		PB0	//	INPUT	10CR
#define VEND2		PC0	//	INPUT	20CR
#define VEND3		PC1	//	INPUT	50CR
#define VEND4		PC2	//	INPUT	100CR
#define INH			PC3	//	OUTPUT


/*	HOPPER	*/
#define H_POW		PD5	//	OUTPUT
#define H_IN3		PB4	//	OUTPUT
#define H_SEN		PD4	//	INPUT

/*	METERS/USER_SW	*/
#define METER_IN	PB7	// OUTPUT
#define METER_OUT	PD7	// OUTPUT
#define SW			PD6	// INPUT

/*	FUNCTIONS	*/
void init(void);
void set_ports(void);
int check_ports(void);

#endif
