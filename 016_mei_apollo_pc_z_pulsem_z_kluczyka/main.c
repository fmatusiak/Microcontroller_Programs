/*
 Zabezpieczenie nv10 nri z kwarcem wersja finalana
 zegar kwarcowy 8 MHZ
 */
// banknoty apollo  mei
//
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"

volatile uint16_t buffer[21], bank = 0, event = -1, firstRun = 1, d = 0, g = 0,
		i = 0, counter = 0, n1 = 0, m1 = 0, n2 = 0, m2 = 0, n3 = 0, m3 = 0, n4 =
				0, m4 = 0, n5 = 0, m5 = 0, stop = 0, coin = 0, coinh = 0,
		buffers[21], j = 0, monety = 0, l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0,
		l6 = 0, l7 = 0, l8 = 0, bezwrzutnika = 0, start = 0, dawaj = 1,
		czascoin = 0, banknot = 0, step = 0, startnabij = 0, bandalej = 0,
		banknoty = 0, c = 0, starter = 0, kolejny = 1, dawajek = 1,
		stoosiem = 0, punkty = 0, FL_Key_switch = 0;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t);
int czytaj_bajt();
void uart_putc(uint8_t);
void uart_putc_s(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
void uartPutz(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t,
		uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t,
		uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t,
		uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
void uartPutS(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
void convert_m(uint16_t);
int bufferEq(void);
void wyj1Flash(int count);

int main(void) {

	DDR_rxs_we;
	rxs_we_VCC;
	DDR_txs;
	PORT_txs_1;
	DDR_Key_plus;
	Key_plus_VCC;

	uart_init(RS_UBRR);
	_delay_ms(2000);

	uart_putc_s(2);
	uart_putc_s(8);
	uart_putc_s(97);
	uart_putc_s(127);
	uart_putc_s(127);
	uart_putc_s(127);
	uart_putc_s(3);
	uart_putc_s(22);
	int klops = 0;
	while (0) {
		klops += 1;
		_delay_ms(1);
		if (klops == 200) {
			uart_putc_s(2);
			uart_putc_s(8);
			uart_putc_s(17);
			uart_putc_s(0);
			uart_putc_s(28);
			uart_putc_s(4);
			uart_putc_s(3);
			uart_putc_s(1);
			klops = 0;
		}
	}

	_delay_ms(226);
	/*
	 uart_putc_s(2);
	 uart_putc_s(8);
	 uart_putc_s(16);
	 uart_putc_s(0);
	 uart_putc_s(28);
	 uart_putc_s(4);
	 uart_putc_s(3);
	 uart_putc_s(0);

	 _delay_ms(529);

	 uart_putc_s(2);
	 uart_putc_s(8);
	 uart_putc_s(17);
	 uart_putc_s(0);
	 uart_putc_s(28);
	 uart_putc_s(4);
	 uart_putc_s(3);
	 uart_putc_s(1);

	 _delay_ms(226);*/

	uart_putc_s(2);
	uart_putc_s(8);
	uart_putc_s(16);
	uart_putc_s(0);
	uart_putc_s(28);
	uart_putc_s(4);
	uart_putc_s(3);
	uart_putc_s(0);

	_delay_ms(740);

	uart_putc_s(2);
	uart_putc_s(8);
	uart_putc_s(17);
	uart_putc_s(0);
	uart_putc_s(28);
	uart_putc_s(4);
	uart_putc_s(3);
	uart_putc_s(1);

	_delay_ms(226);

	uart_putc_s(2);
	uart_putc_s(8);
	uart_putc_s(16);
	uart_putc_s(0);
	uart_putc_s(28);
	uart_putc_s(4);
	uart_putc_s(3);
	uart_putc_s(0);

	_delay_ms(226);

	uart_putc_s(2);
	uart_putc_s(8);
	uart_putc_s(17);
	uart_putc_s(0);
	uart_putc_s(28);
	uart_putc_s(4);
	uart_putc_s(3);
	uart_putc_s(1);

	_delay_ms(226);

	uart_putc_s(2);
	uart_putc_s(8);
	uart_putc_s(16);
	uart_putc_s(0);
	uart_putc_s(28);
	uart_putc_s(4);
	uart_putc_s(3);
	uart_putc_s(0);

	_delay_ms(226);

	uart_putc_s(2);
	uart_putc_s(8);
	uart_putc_s(17);
	uart_putc_s(0);
	uart_putc_s(28);
	uart_putc_s(4);
	uart_putc_s(3);
	uart_putc_s(1);

	_delay_ms(226);

	uart_putc_s(2);
	uart_putc_s(8);
	uart_putc_s(16);
	uart_putc_s(127);
	uart_putc_s(28);
	uart_putc_s(4);
	uart_putc_s(3);
	uart_putc_s(127);

	_delay_ms(226);

	uart_putc_s(2);
	uart_putc_s(8);
	uart_putc_s(17);
	uart_putc_s(127);
	uart_putc_s(28);
	uart_putc_s(4);
	uart_putc_s(3);
	uart_putc_s(126);

	_delay_ms(226);

	uart_putc_s(2);
	uart_putc_s(17);
	uart_putc_s(112);
	uart_putc_s(8);
	uart_putc_s(127);
	uart_putc_s(92);
	uart_putc_s(4);
	uart_putc_s(0);
	uart_putc_s(0);
	uart_putc_s(0);
	uart_putc_s(0);
	uart_putc_s(0);
	uart_putc_s(14);
	uart_putc_s(86);
	uart_putc_s(26);
	uart_putc_s(3);
	uart_putc_s(12);

	_delay_ms(226);

	while (1) {
		if (banknot == 0) {
			if (!(PIN_Key_plus)) {
							_delay_ms(2);
							if (!(PIN_Key_plus)) {
								FL_Key_switch = 0;
								banknoty = 1;
							}

						}


			if (banknoty) {
				banknot = 1;

			}
		}
		buffer[i] = uart_getc();
		if (banknot) {
			if ((buffer[i] == 105) && (bandalej > 20)) {
				_delay_ms(3);
				_delay_ms(3);
				uartPut(2, 11, 32, 2, (uint8_t[]) {16,0,0,84,30,3,115});
				bandalej = bandalej + 1;
			}
			if ((buffer[i] == 104) && (bandalej > 20)) { // 3
				_delay_ms(3);
				_delay_ms(3);
				if ((bandalej == 25) || (bandalej == 26)) {
					if (banknoty == 1) {
						uart_putc(2);
						uart_putc(30);
						uart_putc(112);
						uart_putc(2);
						uart_putc(17);
						uart_putc(16);
						uart_putc(0);
						uart_putc(0);
						uart_putc(84);
						uart_putc(30);
						uart_putc(0);
						uart_putc(67);
						uart_putc(90);
						uart_putc(75);
						uart_putc(48);
						uart_putc(48);
						uart_putc(49);
						uart_putc(43);
						uart_putc(48);
						uart_putc(50);
						uart_putc(0);
						uart_putc(67);
						uart_putc(65);
						uart_putc(66);
						uart_putc(65);
						uart_putc(0);
						uart_putc(0);
						uart_putc(0);
						uart_putc(3);
						uart_putc(108);
						/*uartPut(
						 2,
						 30,
						 113,
						 2,
						 (uint8_t[]) {17,16,0,0,84,30,0,67,90,75,48,48,49,43,48,50,0,67,65,66,65,0,0,0,3,107});*/
					}

					if (banknoty == 2) {
						uartPutz(2, 30, 113, 2, 17, 16, 0, 0, 84, 30, 0, 67, 90,
								75, 48, 48, 50, 43, 48, 50, 1, 66, 65, 66, 65,
								0, 0, 0, 3, 110); //dwie
					}
					if (banknoty == 3) {
						uartPutz(2, 30, 112, 2, 17, 16, 0, 0, 84, 30, 0, 67, 90,
								75, 48, 48, 49, 43, 48, 51, 0, 67, 65, 66, 66,
								0, 0, 0, 3, 110); // stowa
					}
					if (banknoty == 4) {
						uartPutz(2, 30, 112, 2, 17, 16, 0, 0, 84, 30, 0, 67, 90,
								75, 48, 48, 53, 43, 48, 50, 3, 68, 65, 66, 66,
								0, 0, 0, 3, 111); // PIEC
					}
					if (banknoty == 5) {
						uartPutz(2, 30, 112, 2, 17, 16, 0, 0, 84, 30, 0, 67, 90,
								75, 48, 48, 50, 43, 48, 51, 0, 65, 65, 66, 66,
								0, 0, 0, 3, 112); // dwie stowy
					}
					banknoty = 0;
					banknot = 0;
				} else {
					uartPut(2, 11, 33, 2, (uint8_t[]) {16,0,0,84,30,3,114});
							bandalej = bandalej + 1;

						}

					}
			if ((buffer[i] == 104) && (bandalej > 8) && (bandalej < 21)) { // 1
				_delay_ms(3);
				_delay_ms(3);
				if (banknoty == 1) {
					uartPutz(2, 30, 113, 2, 4, 16, 0, 0, 84, 30, 0, 67, 90, 75,
							48, 48, 49, 43, 48, 50, 0, 67, 65, 66, 65, 0, 0, 0,
							3, 120);
				}
				if (banknoty == 2) {
					uartPutz(2, 30, 112, 2, 4, 16, 0, 0, 84, 30, 0, 67, 90, 75,
							48, 48, 50, 43, 48, 50, 1, 66, 65, 66, 65, 0, 0, 0,
							3, 122); // dwie
				}
				if (banknoty == 3) {
					uartPutz(2, 30, 113, 2, 4, 16, 0, 0, 84, 30, 0, 67, 90, 75,
							48, 48, 49, 43, 48, 51, 0, 67, 65, 66, 66, 0, 0, 0,
							3, 122); // stowa
				}
				if (banknoty == 4) {
					uartPutz(2, 30, 113, 2, 4, 16, 0, 0, 84, 30, 0, 67, 90, 75,
							48, 48, 53, 43, 48, 50, 3, 68, 65, 66, 66, 0, 0, 0,
							3, 123); // piec
				}
				if (banknoty == 5) {
					uartPutz(2, 30, 113, 2, 4, 16, 0, 0, 84, 30, 0, 67, 90, 75,
							48, 48, 50, 43, 48, 51, 0, 65, 65, 66, 66, 0, 0, 0,
							3, 123); // dwie stowy
				}
				bandalej = 21;
			}

			if ((buffer[i] == 105) && (bandalej < 15)) {
				_delay_ms(3);
				_delay_ms(3);
				uart_putc(2);
				uart_putc(11);
				uart_putc(32);
				uart_putc(2);
				uart_putc(16);
				uart_putc(0);
				uart_putc(0);
				uart_putc(84);
				uart_putc(30);
				uart_putc(3);
				uart_putc(115);

				//	uartPut(2, 11, 32, 2, (uint8_t[]) {16,0,0,84,30,3,115});
				bandalej = bandalej + 1;
			}
			if ((buffer[i] == 104) && (bandalej < 15)) {
				_delay_ms(3);
				_delay_ms(3);
				uart_putc(2);
				uart_putc(11);
				uart_putc(33);
				uart_putc(2);
				uart_putc(16);
				uart_putc(0);
				uart_putc(0);
				uart_putc(84);
				uart_putc(30);
				uart_putc(3);
				uart_putc(114);
				//	uartPut(2, 11, 33, 2, (uint8_t[]) {16,0,0,84,30,3,114});
				bandalej = bandalej + 1;
			}
			if ((buffer[i] == 73) || (buffer[i] == 72)) { // 2
				_delay_ms(3);
				if (banknoty == 1) { //ok

					uartPutz(2, 30, 112, 2, 4, 16, 0, 0, 84, 30, 0, 67, 90, 75,
							48, 48, 49, 43, 48, 50, 0, 67, 65, 66, 65, 0, 0, 0,
							3, 121);

				}
				if (banknoty == 2) {
					uartPutz(2, 30, 113, 2, 4, 16, 0, 0, 84, 30, 0, 67, 90, 75,
							48, 48, 50, 43, 48, 50, 1, 66, 65, 66, 65, 0, 0, 0,
							3, 123); // dwie
				}
				if (banknoty == 3) {
					uartPutz(2, 30, 112, 2, 4, 16, 0, 0, 84, 30, 0, 67, 90, 75,
							48, 48, 49, 43, 48, 51, 0, 67, 65, 66, 66, 0, 0, 0,
							3, 123); //stowa
				}
				if (banknoty == 4) {
					uartPutz(2, 30, 113, 2, 4, 16, 0, 0, 84, 30, 0, 67, 90, 75,
							48, 48, 53, 43, 48, 50, 3, 68, 65, 66, 66, 0, 0, 0,
							3, 123); // piec
				}
				if (banknoty == 5) {
					uartPutz(2, 30, 112, 2, 4, 16, 0, 0, 84, 30, 0, 67, 90, 75,
							48, 48, 50, 43, 48, 51, 0, 65, 65, 66, 66, 0, 0, 0,
							3, 124); // dwie stowy
				}

			}
			if (banknot == 0) {
				bandalej = 0;
			}
		}

		else {
			if (start == 1) {
				if (buffer[i] == 105) {
					_delay_ms(3);
					_delay_ms(3);
					uartPut(2, 11, 32, 1, (uint8_t[]) {16,0,0,84,30,3,112});
					uart_putc_s(2);
					uart_putc_s(8);
					uart_putc_s(17);
					uart_putc_s(127);
					uart_putc_s(28);
					uart_putc_s(4);
					uart_putc_s(3);
					uart_putc_s(126);
				}
				if (buffer[i] == 104) {
					_delay_ms(3);
					_delay_ms(3);
					uartPut(2, 11, 33, 1, (uint8_t[]) {16,0,0,84,30,3,113});
					uart_putc_s(2);
					uart_putc_s(8);
					uart_putc_s(16);
					uart_putc_s(127);
					uart_putc_s(28);
					uart_putc_s(4);
					uart_putc_s(3);
					uart_putc_s(127);
					c = czytaj_bajt();
					c = czytaj_bajt();
					c = czytaj_bajt();
					c = czytaj_bajt();
					//	c = czytaj_bajt();
					//	c = czytaj_bajt();
					//	c = czytaj_bajt();

					d = czytaj_bajt();
					d = czytaj_bajt();
					//	c = uart_getc();
					_delay_ms(10);
					uart_putc_s(c);
					uart_putc_s(d);
					//napisz(2);
					if ((c == 4) && (d != 40)) {
						_delay_ms(30);

						uart_putc_s(2);
						uart_putc_s(8);
						uart_putc_s(17);
						uart_putc_s(127);
						uart_putc_s(60);
						uart_putc_s(4);
						uart_putc_s(3);
						uart_putc_s(94);
						starter = 1;

					}
					if (starter) {
						starter = 0;


					}

				}

				if (buffer[i] == 97) {
					_delay_ms(8);
					uartPut(
							2,
							37,
							97,
							67,
							(uint8_t[]) {90,75,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,22});
					stoosiem = 1;
				}
				if (buffer[i] == 96) {

					uart_getc();
					uart_getc();
					uart_getc();
					uart_getc();
					_delay_ms(8);
					uartPut(
							2,
							37,
							97,
							67,
							(uint8_t[]) {90,75,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,22});
					stoosiem = 1;
				}
				if ((buffer[i] == 108) && (stoosiem)) {
					_delay_ms(8);
					uartPut(
							2,
							25,
							96,
							115,
							(uint8_t[]) {99,56,53,48,55,0,127,127,127,127,127,127,127,127,127,127,127,127,127,3,28});

								}
					//					}

				if (buffer[i] == 20) {
					_delay_ms(3);
					_delay_ms(3);

					uartPut(2, 11, 32, 1, (uint8_t[]) {16, 0, 0, 84, 30, 3, 112});
				}
				if (buffer[i] == 21) {
					_delay_ms(3);
					_delay_ms(3);

					uartPut(2, 11, 33, 1, (uint8_t[]) {16, 0, 0, 84, 30, 3, 113});

				}

			}

// ===================================================== start start == 0 ===============================================
			if (start == 0) {
				if (buffer[i] == 20) {
					_delay_ms(3);
					_delay_ms(3);
					start = 1;

					uartPut(2, 11, 32, 1, (uint8_t[]) {16, 0, 0, 84, 30, 3, 112});
				}
				if (buffer[i] == 21) {
					_delay_ms(3);
					_delay_ms(3);
					start = 1;
					uartPut(2, 11, 33, 1, (uint8_t[]) {16, 0, 0, 84, 30, 3, 113});

				}
				if (buffer[i] == 105) {
					_delay_ms(3);
					_delay_ms(3);
					uartPut(2, 11, 32, 0, (uint8_t[]) {16,1,0,84,30,3,112});
				}
				if (buffer[i] == 104) {
					_delay_ms(3);
					_delay_ms(3);
					uartPut(2, 11, 33, 0, (uint8_t[]) {16,1,0,84,30,3,113});
				}
				if ((buffer[i] == 16) && (dawajek == 1)) {
					buffer[i] = uart_getc();
					if (buffer[i] == 0) {
						_delay_ms(3);
						_delay_ms(3);
						_delay_ms(10);
						uartPut(2, 11, 32, 0, (uint8_t[]) {16,1,0,84,30,3,112});
						_delay_ms(2);
						buffer[i] = uart_getc();
						buffer[i] = uart_getc();
						buffer[i] = uart_getc();
						buffer[i] = uart_getc();
					}

					//	if (buffer[i] == 113) {
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					if (buffer[i] == 1) {
						_delay_ms(3);
						_delay_ms(10);
						uartPut(2, 30, 113, 2, (uint8_t[]) {0,16,1,0,84,30,1,67,90,75,48,48,49,43,48,50,0,67,65,66,65,0,0,0,3,124});
						_delay_ms(2);
					}
					//}
					//	if (buffer[i] == 112) {
					//	buffer[i] = uart_getc();
					//	buffer[i] = uart_getc();
					//	buffer[i] = uart_getc();
					//	buffer[i] = uart_getc();
					if (buffer[i] == 2) {
						_delay_ms(3);
						_delay_ms(10);
						uartPut(2, 30, 112, 2, (uint8_t[]) {0,16,1,0,84,30,2,67,90,75,48,48,50,43,48,50,0,66,65,66,65,0,0,0,3,124});
						_delay_ms(2);
					}
					//}
					//	if (buffer[i] == 113) {
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					if (buffer[i] == 3) {
						_delay_ms(3);
						_delay_ms(10);
						uartPut(2, 30, 113, 2, (uint8_t[]) {0,16,1,0,84,30,3,67,90,75,48,48,53,43,48,50,0,66,65,66,66,0,0,0,3,120});
						_delay_ms(2);
					}
					//	}
					//	if (buffer[i] == 112) {
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					if (buffer[i] == 4) {
						_delay_ms(3);
						_delay_ms(10);
						uartPut(2, 30, 112, 2, (uint8_t[]) {0,16,1,0,84,30,4,67,90,75,48,48,53,43,48,50,0,68,65,66,66,0,0,0,3,120});
						_delay_ms(2);
					}
					//	}
					//		if (buffer[i] == 113) {
					//			buffer[i] = uart_getc();
					//			buffer[i] = uart_getc();
					//			buffer[i] = uart_getc();
					//			buffer[i] = uart_getc();
					if (buffer[i] == 5) {
						_delay_ms(3);
						_delay_ms(10);

						uartPut(2, 30, 113, 2, (uint8_t[]) {0,16,1,0,84,30,5,67,90,75,48,48,49,43,48,51,0,67,65,66,66,0,0,0,3,122});
						_delay_ms(2);
					}
					//	}
					//	if (buffer[i] == 112) {
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					if (buffer[i] == 6) {
						_delay_ms(3);
						_delay_ms(10);
						uartPut(2, 30, 112, 2, (uint8_t[]) {0,16,1,0,84,30,6,67,90,75,48,48,50,43,48,51,0,65,65,66,66,0,0,0,3,121});
						_delay_ms(2);
					}
					//	}
					//	if (buffer[i] == 113) {
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					if (buffer[i] == 7) {
						_delay_ms(3);
						_delay_ms(10);
						uartPut(2, 30, 113, 2, (uint8_t[]) {0,16,1,0,84,30,7,67,90,75,48,48,50,43,48,51,0,66,65,66,66,0,0,0,3,122});
						_delay_ms(2);
					}
					//	}
					//		if (buffer[i] == 112) {
					//		buffer[i] = uart_getc();
					//		buffer[i] = uart_getc();
					//	buffer[i] = uart_getc();
					//	buffer[i] = uart_getc();
					if (buffer[i] == 8) {
						_delay_ms(3);

						_delay_ms(3);
						_delay_ms(10);

						uartPut(2, 30, 112, 2, (uint8_t[]) {0,16,1,0,84,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,55});
						_delay_ms(2);
						dawajek = 0;

					}

				}

			}
// ================================================== end start == 0 ========================================

		}
	} //
}
// =================================== koniec nri cctalk wrzutnik ==========================================

// FUNCTIONS

void uart_init(uint16_t ubrr) {
// Ustawienie prêdkoœci transmisji
	UBRRH = (uint8_t) (ubrr >> 8);
	UBRRL = (uint8_t) ubrr;

// W³¹czenie nadajnika i odbiornika
	UCSRB = (1 << RXEN) | (1 << TXEN);

// Ustawienie formatu ramki:
// 7 bitów danych, 1 b it stopu, even bit
	UCSRC = (1 << URSEL) | (2 << UCSZ0) | (1 << UPM1);

}

void uart_putc(uint8_t data) {
// Oczekiwanie na zakoñczenie nadawania
	while (!(UCSRA & (1 << UDRE)))
		;

// Wys³anie danych
	UDR = data;
}

uint8_t uart_ischar() {
// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc() {
// Czy w buforze s¹ dane?
	while (!uart_ischar()) {
	}

	return UDR;
}

void uartPut(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,
		uint8_t *data) {
	uart_putc(from);
	uart_putc(dataCount);
	uart_putc(to);
	uart_putc(command);
	uint8_t checkSum = from + to + command + dataCount;
	for (int i = 0; i < dataCount - 4; i++) {
		uart_putc(data[i]);
		checkSum += data[i];
	}
	checkSum %= 256;
	checkSum = 256 - checkSum;
//uart_putc(checkSum);
}
void uartPutz(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,
		uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4, uint8_t a5, uint8_t a6,
		uint8_t a7, uint8_t a8, uint8_t a9, uint8_t a10, uint8_t a11,
		uint8_t a12, uint8_t a13, uint8_t a14, uint8_t a15, uint8_t a16,
		uint8_t a17, uint8_t a18, uint8_t a19, uint8_t a20, uint8_t a21,
		uint8_t a22, uint8_t a23, uint8_t a24, uint8_t a25, uint8_t a26) {
	uart_putc(from);
	uart_putc(dataCount);
	uart_putc(to);
	uart_putc(command);
	uart_putc(a1);
	uart_putc(a2);
	uart_putc(a3);
	uart_putc(a4);
	uart_putc(a5);
	uart_putc(a6);
	uart_putc(a7);
	uart_putc(a8);
	uart_putc(a9);
	uart_putc(a10);
	uart_putc(a11);
	uart_putc(a12);
	uart_putc(a13);
	uart_putc(a14);
	uart_putc(a15);
	uart_putc(a16);
	uart_putc(a17);
	uart_putc(a18);
	uart_putc(a19);
	uart_putc(a20);
	uart_putc(a21);
	uart_putc(a22);
	uart_putc(a23);
	uart_putc(a24);
	uart_putc(a25);
	uart_putc(a26);

}

void uartPutS(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,
		uint8_t *data) {
	uart_putc_s(from);
	uart_putc_s(dataCount);
	uart_putc_s(to);
	uart_putc_s(command);
	uint8_t checkSum = from + to + command + dataCount;
	for (int i = 0; i < dataCount; i++) {
		uart_putc_s(data[i]);
		checkSum += data[i];
	}
	checkSum %= 256;
	checkSum = 256 - checkSum;
	uart_putc_s(checkSum);
}
// ========================================================================

// ========================================================================
void uart_putc_s(uint8_t data) {
	int c, k, parity = 0;

	PORT_txs_0;
	_delay_us(103);
	for (c = 0; c <= 6; c++) {
		k = data >> c;

		if (k & 1) {
			PORT_txs_1;
			_delay_us(103);
			parity = parity + 1;
		}

		else {
			PORT_txs_0;
			_delay_us(103);
		}

	}
	if (parity % 2 == 0) {

		PORT_txs_0;
		_delay_us(103);
	} else {

		PORT_txs_1;
		_delay_us(103);
	}

	PORT_txs_1;
	_delay_us(103);

}
int czytaj_bajt() {
	int i = 0;
	while (0) {
	}
	i = 0;
	for (int i = 0; i < 103; i++) {

		if ((i > 11) && (i < 23)) {
			if (PIN_rxs_we) {
				l1 += 1;

			}
		}
		if ((i > 23) && (i < 34)) {
			if (PIN_rxs_we) {
				l2 += 1;
			}
		}
		if ((i > 34) && (i < 45)) {
			if (PIN_rxs_we) {
				l3 += 1;

			}
		}
		if ((i > 45) && (i < 56)) {
			if (PIN_rxs_we) {
				l4 += 1;

			}
		}
		if ((i > 56) && (i < 67)) {
			if (PIN_rxs_we) {
				l5 += 1;

			}
		}
		if ((i > 67) && (i < 78)) {
			if (PIN_rxs_we) {
				l6 += 1;

			}
		}
		if ((i > 78) && (i < 89)) {
			if (PIN_rxs_we) {
				l7 += 1;

			}
		}

		_delay_us(2);
	}
	int liczba = 0;
	if (l1 > 5) {
		liczba += 1;
	}
	if (l2 > 5) {
		liczba += 2;
	}
	if (l3 > 5) {
		liczba += 4;
	}
	if (l4 > 5) {
		liczba += 8;
	}
	if (l5 > 5) {
		liczba += 16;
	}
	if (l6 > 5) {
		liczba += 32;
	}
	if (l7 > 5) {
		liczba += 64;
	}

	l1 = 0;
	l2 = 0;
	l3 = 0;
	l4 = 0;
	l5 = 0;
	l6 = 0;
	l7 = 0;
	l8 = 0;

	return liczba;

// =============

}

