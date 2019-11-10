#ifndef BNC_BNC_H_
#define BNC_BNC_H_

void bnc_check(void);
int bnc_emp(int a, int b, int c, int d, int a1, int b1, int c1, int d1);
void bnc_turn_on(void);
void bnc_turn_off(void);

volatile int a,b,c,d;
volatile int a1,b1,c1,d1;
volatile int credits;
#endif
