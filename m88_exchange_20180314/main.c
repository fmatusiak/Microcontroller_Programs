//	DOUBLE
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "config.h"
#include "uart.h"
#include "cctalk.h"
#include "lcd_new.h"
#include "lcd_menu.h"
#include "hopper.h"
#include "eeprom.h"
#include "cct_coin.h"


uint8_t pce = 0;
uint8_t cce = 0;

uint8_t buffer[15];
unsigned char timer_flag = 0;
uint8_t byte_count = 0;
uint16_t timer0 = 0;
uint8_t kasa = 0;
uint8_t coins_left = 20;
uint8_t empty_flag = 0;

uint8_t h1ef = 0;
uint8_t h2ef = 0;
uint8_t mode = 0;
uint8_t ud = 0;
uint8_t pmode = 0;
uint8_t h = 0;

ISR(USART_RX_vect){
	if(timer_flag == 0){
		timer_flag = 1;
		byte_count = 0;
		timer_start();
	}
	buffer[byte_count] = uart_rx();
	byte_count++;
	timer_restart();
}
ISR(TIMER0_OVF_vect){
	//625
	if(timer0 > 625){
		timer_stop();
		//check if data is correct (checksum)
		if(checksum(buffer, byte_count)){
			if(buffer[2] == 2){
				cce = buffer[4];

				if(pce == cce){
					kasa = 0;
				}else{
					kasa = analyze_data(buffer);
					pce = buffer[4];
				}
				/*
				if(pce !=  0){
					if(pce == cce){
						kasa = 0;
					}else{
						kasa = analyze_data(buffer);
						pce = buffer[4];
					}
				}else{
					pce = buffer[4];
					kasa = 0;
				}
				*/
			}else{
				kasa = analyze_data(buffer);
			}
			if(kasa > 0){
			bill_take();
			bill_distable();
				//meters in kasa
				set_in(kasa);
				// hopper pay kasa
			if(mode == 1){
				uint8_t to_pay = kasa /C2V;
// payout mode 1
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("Wplacono:");
			convert(kasa);
			lcd_gotoxy(13,0);
			lcd_puts("PLN");
			lcd_gotoxy(0,1);
			lcd_puts("Wyplacono:0");
			lcd_gotoxy(13,1);
			lcd_puts("PLN");
			while(!(to_pay == 0)){
				if(!h2_pay()){
					to_pay--;
					lcd_update(10,1, kasa - (to_pay* C2V) );
					_delay_ms(5);
				}else{
					lcd_clrscr();
					lcd_puts("   Brak monet");
					lcd_gotoxy(0,1);
					convert((to_pay * C2V));
					lcd_puts("PLN z ");
					convert(kasa);
					lcd_puts(" PLN");
					set_out2(kasa - (to_pay*C2V));
					ld_void();
					//while(1);
				}
			}
			set_out2(kasa - (to_pay*C2V));
			pmode = 0;
			ud = 1;
			}else if(mode == 2){
// payout mode 2
				uint8_t to_pay = (kasa /C1V);
				lcd_clrscr();
				lcd_gotoxy(0,0);
				lcd_puts("Wplacono:");
				convert(kasa);
				lcd_gotoxy(13,0);
				lcd_puts("PLN");
				lcd_gotoxy(0,1);
				lcd_puts("Wyplacono:0");
				lcd_gotoxy(13,1);
				lcd_puts("PLN");
				//to_pay++;
				while(!(to_pay == 0)){
					if(!h1_pay()){
						to_pay--;
						lcd_update(10,1, kasa - (to_pay* C1V));
						_delay_ms(5);
					}else{
						lcd_clrscr();
						lcd_puts("   Brak monet");
						lcd_gotoxy(0,1);
						convert((to_pay * C1V));
						lcd_puts("PLN z ");
						convert(kasa);
						lcd_puts(" PLN");
						set_out1(kasa - (to_pay*C1V));
						//while(1);
						ld_void();
					}
				}
				set_out1(kasa - (to_pay*C1V));
				pmode = 0;
				ud = 1;
			}
			else if(mode == 3){
// payout mode 3
				uint8_t empty1 = 0;
				uint8_t empty2 = 0;
				lcd_clrscr();
				lcd_puts("Wybierz:");
				//convert(kasa);
				//lcd_puts(" PLN");
				lcd_gotoxy(0,1);
				convert(C1V);
				lcd_puts(" PLN");
				lcd_puts("     ");
				convert(C2V);
				lcd_puts(" PLN");
				_delay_ms(1000);
				choose:
				while(!((BT1_DOWN) || (BT2_DOWN)));
					if(!BT1_DOWN){
						h = 1;
					}else if(!BT2_DOWN){
						h = 2;
					}
					lcd_clrscr();
					lcd_gotoxy(0,0);
					lcd_puts("Wplacono:");
					convert(kasa);
					lcd_gotoxy(13,0);
					lcd_puts("PLN");
					lcd_gotoxy(0,1);
					lcd_puts("Wyplacono:0");
					lcd_gotoxy(13,1);
					lcd_puts("PLN");
					if(h == 1){
						uint8_t to_pay = (kasa /C1V);
						while(!(to_pay == 0)){
							if(!h1_pay()){
								to_pay--;
								lcd_update(10,1, kasa - (to_pay* C1V));
								_delay_ms(5);
							}else{
								//brak monet w hopperze
								uint8_t left_to_pay = (to_pay * C1V);
								uint8_t payed = kasa - left_to_pay;
								set_out1(payed);
								empty1 = 1;
								if(empty2 == 1){
									lcd_clrscr();
									lcd_puts("2E");
									//while(1);
									ld_void();
								}
								to_pay = (left_to_pay /C2V);
								uint8_t to_pay2 = to_pay;
								while(!(to_pay == 0)){
									if(!h2_pay()){
										to_pay--;
										lcd_update(10,1, kasa - (to_pay* C2V));
										_delay_ms(1000);
									}else{
										uint8_t payed2 = (to_pay2 - to_pay) * C2V;
										lcd_clrscr();
										lcd_puts("   Brak monet");
										lcd_gotoxy(0,1);
										lcd_puts("Pozostalo ");
										convert(kasa - (payed + payed2));
										lcd_puts(" PLN");
										set_out2(payed2);
										//while(1);
										ld_void();
									}
								}
								set_out2(to_pay2 * C2V);
							}
						}
						set_out1(kasa);
						pmode = 0;
						ud = 1;
					}else if(h ==2){
						uint8_t to_pay = (kasa /C2V);
						while(!(to_pay == 0)){
							if(!h2_pay()){
								to_pay--;
								lcd_update(10,1, kasa - (to_pay* C2V));
								_delay_ms(1000);
							}else{
								// brak monet w hopperze
								uint8_t left_to_pay = (to_pay * C2V);
								uint8_t payed = kasa - left_to_pay ;
								set_out2(payed);
								empty2 = 1;
								if(empty1 == 1){
									lcd_clrscr();
									lcd_puts("3EE");
									//while(1);
									ld_void();
								}
								to_pay = (left_to_pay / C1V);
								uint8_t to_pay2 = to_pay;
								while(!(to_pay == 0)){
									if(!h1_pay()){
										to_pay--;
										lcd_update(10,1, kasa - (to_pay* C1V));
										_delay_ms(5);
									}else{
										lcd_clrscr();
										lcd_puts("   Brak monet");
										lcd_gotoxy(0,1);
										lcd_puts("Pozostalo ");
										uint8_t payed2 = (to_pay2 - to_pay) * C1V;
										convert(kasa - (payed + payed2));
										lcd_puts(" PLN");
										set_out1(payed2);
										//while(1);
										ld_void();
									}
								}
								set_out1(to_pay2 * C1V);
							}
						}
						set_out2(kasa);
						pmode = 0;
						ud = 1;
					}else{
						goto choose;
					}

			}
				bill_init();
			}
		}
		//clear buffer'n'count
		byte_count = 0;
		for(int g = 0; g<15; g++){
				buffer[g] = 0;
		}
	}else{
		timer0 ++;
	}
}
void clear_meters(void){
	write(1, 0);
	write(2, 0);
	write(3, 0);
}

void display_cnt(void){
	lcd_clrscr();
	uint32_t in = read_in();
	uint32_t out1 = read_out1();
	uint32_t out2 = read_out2();

	convert(in);
	lcd_gotoxy(0,1);
	convert(out1);
	lcd_gotoxy(7,1);
	convert(out2);
}

int main(void){
	init_all();
	h1_off();
	h2_off();
	timers_init();
	timer_stop();
	uart_init();
	lcd_init(LCD_DISP_ON);
	sei();

	//write(1, 0);
	//write(2, 0);
	//write(3, 0);


	bill_init();
	coin_init();
	while(1){
		//bill_init();
		//_delay_ms(250);
		bill_alive();
		//_delay_ms(10);
		//coin_read();
		//_delay_ms(10);

		_delay_ms(500);
		if(!H1E_DOWN){h1ef = 1;}else{h1ef = 0;}
		if(!H2E_DOWN){h2ef = 1;}else{h2ef = 0;}
		// check operator btn
		if(BTO_DOWN){
			display_cnt();
			uint8_t o_ud = 0;
			uint8_t o_pm = 3;
			uint8_t o_cm = 3;

			uint8_t dump = 0;
			while(BTO_DOWN){
				if(BT1_DOWN && BT2_DOWN){
					lcd_clrscr();
					lcd_puts("Clearing meters");
					_delay_ms(3000);
					if(BT1_DOWN && BT2_DOWN){
						clear_meters();
						lcd_gotoxy(0,1);
						lcd_puts("Done");
					}
					o_ud = 1;
					o_pm = 4;
				}
				if(BT1_DOWN){
					o_cm = 1;
					if(!(o_cm == o_pm)){o_ud = 1;}
					if(o_ud){
						lcd_clrscr();
						lcd_puts("DUMP ");
						convert(C2V);
						lcd_puts(" PLN");

						o_pm = 1;
						o_ud = 0;
					}
					while(BT1_DOWN){
						h1_on();
						lcd_update(0,1, dump);
						if(bit_is_clear(PIND, PD3)){
							// UPDATE LCD
							h1_off();
							dump++;
							ld_blink();
							_delay_ms(100);
							h1_on();
						}
					}
					dump = 0;
					h1_off();
					_delay_ms(250);
					//lcd_puts("A");
				}else if(BT2_DOWN){
					o_cm = 2;
					if(!(o_cm == o_pm)){o_ud = 1;}
					if(o_ud){
						lcd_clrscr();
						lcd_puts("DUMP ");
						convert(C1V);
						lcd_puts(" PLN");

						o_pm = 2;
						o_ud=  0;
					}
					while(BT2_DOWN){
						h1_on();
						lcd_update(0,1, dump);
						if(bit_is_clear(PIND, PD6)){
							// UPDATE LCD
							h1_off();
							dump++;
							ld_blink();
							_delay_ms(100);
							h1_on();
						}
					}
					dump = 0;
					h1_off();
					_delay_ms(250);
					//lcd_puts("B");
				}else{
					o_cm = 3;
					if(!(o_cm == o_pm)){o_ud = 1;}
					if(o_ud){
						lcd_clrscr();
						display_cnt();
						o_pm = 3;
						o_ud = 0;
					}
					//lcd_puts("C");
				}
				ld_blink();
				_delay_ms(100);
			}
			pmode =0;
			mode = 0;
			ud = 1;
		}
		//check if h1'n'h2 are empty, distable machine
		if(h1ef && h2ef){
			lcd_clrscr();
			lcd_puts("   Brak monet");
			pmode = 0; ud = 1;
			//ld_blink();
			while(!H1E_DOWN && !H2E_DOWN){ld_blink();}
			lcd_clrscr();
		}
		// check if h1' or 'h2 are empty, change wotking mode
		if(h1ef){
			mode = 1;
			if(pmode == mode){
				ud = 0;
			}else{
				pmode = 1;
				ud = 1;
			}
		}else if(h2ef){
			mode = 2;
			if(pmode ==mode){
				ud = 0;
			}else{
				pmode =2;
				ud = 1;
			}
		}else{
			mode = 3;
			if(pmode == mode){
				ud = 0;
			}else{
				pmode = 3;
				ud = 1;
			}
		}

		if(ud){
			lcd_clrscr();
			if(mode ==1){
				lcd_puts("  Rozmieniarka");
				lcd_gotoxy(0,1);
				lcd_puts("      ");
				convert(C2V);
				lcd_puts(" PLN");
				bill_init();
			}
			else if(mode ==2){
				lcd_puts("  Rozmieniarka");
				lcd_gotoxy(0,1);
				lcd_puts("     ");
				convert(C1V);
				lcd_puts(" PLN");
				bill_init();
			}else if(mode ==3){
				lcd_puts("  Rozmieniarka");
				lcd_gotoxy(0,1);
				lcd_puts("  ");
				convert(C1V);
				lcd_puts(" PLN ");
				convert(C2V);
				lcd_puts(" PLN");
				bill_init();
			}
		}
	}
}
