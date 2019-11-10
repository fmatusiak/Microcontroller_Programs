#ifndef HOPPER_HOPPER_H_
#define HOPPER_HOPPER_H_

void power_on(void);
void power_off(void);
void pay(int credits);
void dump_on(void);
void dump_off(void);
void timer0_init(void);
void timer0_reboot(void);



volatile uint16_t tot_overflow;
volatile int coins_to_pay;


#endif
