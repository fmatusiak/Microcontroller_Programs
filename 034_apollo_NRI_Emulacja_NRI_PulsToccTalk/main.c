/*
 Zabezpieczenie nv10 nri z kwarcem wersja finalana
 zegar kwarcowy 8 MHZ
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "main.h"

volatile uint8_t data[40];

volatile uint8_t money = 0, FL_coin = 0, event = 0, Inhibit = 1;
volatile uint8_t res_1A = 0, res_1B = 0, res_2A = 0, res_2B = 0, res_3A = 0,
		res_3B = 0, res_4A = 0, res_4B = 0, res_5A = 0, res_5B = 0;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51
#define Host 1
#define Device 2

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void check_is_money(void);
void send_command(uint8_t, uint8_t, uint8_t*);
void Set_inhibit(void);
void uart_clear(void);
void check_money(void);


void Simple_poll_ans(void);
void Request_manufacturer_id_ans(void);
void Reset_device_ans(void);
void Request_serial_number_ans(void);
void Request_software_version_ans(void);
void Request_coin_id_ans(void);
void Request_sorter_paths_ans(void);
void Request_coin_id_ans_v2(void);
void Request_coin_id_ans_v3(void);
void Request_coin_id_ans_v4(void);
void Request_coin_id_ans_v5(void);
void Request_coin_id_ans_v6(void);
void Request_coin_id_ans_v7(void);
void Request_coin_id_ans_v8(void);
void Request_coin_id_ans_v9(void);
void Request_coin_id_ans_v10(void);
void Request_coin_id_ans_v11(void);
void Request_coin_id_ans_v12(void);
void Request_coin_id_ans_v13(void);
void Request_coin_id_ans_v14(void);
void Request_coin_id_ans_v15(void);
void Request_coin_id_ans_v16(void);

void Read_buffor_credit_ans(void);
int main(void) {

	DDR_coin_we;
	coin_we_VCC;
	DDR_Inhibit_Out;
	PORT_Inhibit_Out_0;

	uart_init(RS_UBRR);
	_delay_ms(2000);

	for (uint8_t i = 0; i < 40; i++) {
		data[i] = 0;
	}

	while (1) {
		check_is_money();

		data[0] = uart_getc();
		check_is_money();
		if (data[0] == 2) {
			data[1] = uart_getc();
			data[2] = uart_getc();

			if ((data[0] == 2) && (data[2] == 1)) {

				data[3] = uart_getc();
				data[4] = uart_getc();

				for (uint8_t i = 0; i < data[1]; i++) {
					data[i + 5] = uart_getc();
				}
				check_is_money();

				if ((data[0] == 2) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 254) && (data[4] == 255)) {
					Simple_poll_ans();
				}

				if ((data[0] == 2) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 246) && (data[4] == 7)) {
					Request_manufacturer_id_ans();
				}

				if ((data[0] == 2) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 1) && (data[4] == 252)) {
					Reset_device_ans();
				}

				if ((data[0] == 2) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 242) && (data[4] == 11)) {
					Request_serial_number_ans();
				}

				if ((data[0] == 2) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 241) && (data[4] == 12)) {
					Request_software_version_ans();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 1)
						&& (data[5] == 67)) {
					Request_coin_id_ans();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 209) && (data[4] == 1)
						&& (data[5] == 42)) {
					Request_sorter_paths_ans();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 2)
						&& (data[5] == 66)) {
					Request_coin_id_ans_v2();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 209) && (data[4] == 2)
						&& (data[5] == 41)) {
					Request_sorter_paths_ans();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 3)
						&& (data[5] == 65)) {
					Request_coin_id_ans_v3();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 209) && (data[4] == 3)
						&& (data[5] == 40)) {
					Request_sorter_paths_ans();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 4)
						&& (data[5] == 64)) {
					Request_coin_id_ans_v4();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 209) && (data[4] == 4)
						&& (data[5] == 39)) {
					Request_sorter_paths_ans();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 209) && (data[4] == 5)
						&& (data[5] == 38)) {
					Request_sorter_paths_ans();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 209) && (data[4] == 6)
						&& (data[5] == 37)) {
					Request_sorter_paths_ans();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 4)
						&& (data[5] == 64)) {
					Request_coin_id_ans_v4();
				}
				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 5)
						&& (data[5] == 63)) {
					Request_coin_id_ans_v5();
				}
				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 6)
						&& (data[5] == 62)) {
					Request_coin_id_ans_v6();
				}
				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 7)
						&& (data[5] == 61)) {
					Request_coin_id_ans_v7();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 8)
						&& (data[5] == 60)) {
					Request_coin_id_ans_v8();
				}
				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 9)
						&& (data[5] == 59)) {
					Request_coin_id_ans_v9();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 10)
						&& (data[5] == 58)) {
					Request_coin_id_ans_v10();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 11)
						&& (data[5] == 57)) {
					Request_coin_id_ans_v11();
				}
				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 12)
						&& (data[5] == 56)) {
					Request_coin_id_ans_v12();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 13)
						&& (data[5] == 55)) {
					Request_coin_id_ans_v13();
				}
				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 14)
						&& (data[5] == 54)) {
					Request_coin_id_ans_v14();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 15)
						&& (data[5] == 53)) {
					Request_coin_id_ans_v15();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 184) && (data[4] == 16)
						&& (data[5] == 52)) {
					Request_coin_id_ans_v16();
				}
				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 222) && (data[4] == 255)
						&& (data[5] == 31)) {
					Reset_device_ans();
				}

				if ((data[0] == 2) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 222) && (data[4] == 0)) {
					Reset_device_ans();
				}

				if ((data[0] == 2) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 229) && (data[4] == 24)) {
					Read_buffor_credit_ans();
				}

				if ((data[0] == 2) && (data[1] == 2) && (data[2] == 1)
						&& (data[3] == 231) && (data[4] == 0) && (data[5] == 0)
						&& (data[6] == 20)) {
					Reset_device_ans();

					Inhibit = 1;
					Set_inhibit();
				}

				if ((data[0] == 2) && (data[1] == 2) && (data[2] == 1)
						&& (data[3] == 231) && (data[4] == 32) && (data[5] == 0)
						&& (data[6] == 244)) {
					Reset_device_ans();
					Inhibit = 0;
				}
				Set_inhibit();
				check_is_money();

				uart_clear();
			}
		}

		for (uint8_t i = 0; i < 40; i++) {
			data[i] = 0;
		}
	}
}

// =================================== koniec nri cctalk wrzutnik ==========================================

void uart_clear(void) {
	uint8_t flu;
	while ( UCSRA & (1 << RXC)) {
		flu = UDR;
	}
}

//Comends

//Header 254
void Simple_poll_ans(void) {

	send_command(0, 2, 0);
	check_is_money();
}

//Header 246
void Request_manufacturer_id_ans(void) {

	send_command(3, 0, (uint8_t[] ) { 78, 82, 73 });
	check_is_money();
}

//Header 1
void Reset_device_ans(void) {

	send_command(0, 0, 0);
	check_is_money();
}

//Header 242
void Request_serial_number_ans(void) {

	send_command(3, 0, (uint8_t[] ) { 204, 239, 31 });
	check_is_money();
}
//Header 241
void Request_software_version_ans(void) {

	send_command(5, 0, (uint8_t[] ) { 53, 50, 46, 48, 53 });
	check_is_money();
}

//Header 184
void Request_coin_id_ans(void) {

	send_command(6, 0, (uint8_t[] ) { 80, 76, 48, 49, 48, 65 });
	check_is_money();
}

//Header 209
void Request_sorter_paths_ans(void) {

	send_command(4, 0, (uint8_t[] ) { 1, 1, 1, 1 });
	check_is_money();
}

//Header 184
void Request_coin_id_ans_v2(void) {

	send_command(6, 0, (uint8_t[] ) { 80, 76, 48, 50, 48, 65 });
	check_is_money();
}

//Header 184
void Request_coin_id_ans_v3(void) {

	send_command(6, 0, (uint8_t[] ) { 80, 76, 48, 53, 48, 65 });
	check_is_money();
}

//Header 184
void Request_coin_id_ans_v4(void) {

	send_command(6, 0, (uint8_t[] ) { 80, 76, 49, 48, 48, 65 });
	check_is_money();
}

//Header 184
void Request_coin_id_ans_v5(void) {

	send_command(6, 0, (uint8_t[] ) { 80, 76, 50, 48, 48, 65 });
	check_is_money();
}
//Header 184
void Request_coin_id_ans_v6(void) {

	send_command(6, 0, (uint8_t[] ) { 80, 76, 53, 48, 48, 65 });
	check_is_money();
}
//Header 184
void Request_coin_id_ans_v7(void) {

	send_command(6, 0, (uint8_t[] ) { 84, 77, 48, 48, 48, 65 });
	check_is_money();
}
//Header 184
void Request_coin_id_ans_v8(void) {

	send_command(6, 0, (uint8_t[] ) { 46, 46, 46, 46, 46, 46 });
	check_is_money();
}
//Header 184
void Request_coin_id_ans_v9(void) {

	send_command(6, 0, (uint8_t[] ) { 46, 46, 46, 46, 46, 46 });
	check_is_money();
}
//Header 184
void Request_coin_id_ans_v10(void) {

	send_command(6, 0, (uint8_t[] ) { 46, 46, 46, 46, 46, 46 });
	check_is_money();
}
//Header 184
void Request_coin_id_ans_v11(void) {

	send_command(6, 0, (uint8_t[] ) { 46, 46, 46, 46, 46, 46 });
	check_is_money();
}
//Header 184
void Request_coin_id_ans_v12(void) {

	send_command(6, 0, (uint8_t[] ) { 46, 46, 46, 46, 46, 46 });
	check_is_money();
}
//Header 184
void Request_coin_id_ans_v13(void) {

	send_command(6, 0, (uint8_t[] ) { 46, 46, 46, 46, 46, 46 });
	check_is_money();
}
//Header 184
void Request_coin_id_ans_v14(void) {

	send_command(6, 0, (uint8_t[] ) { 46, 46, 46, 46, 46, 46 });
	check_is_money();
}

//Header 184
void Request_coin_id_ans_v15(void) {

	send_command(6, 0, (uint8_t[] ) { 46, 46, 46, 46, 46, 46 });
	check_is_money();
}

//Header 184
void Request_coin_id_ans_v16(void) {

	send_command(6, 0, (uint8_t[] ) { 46, 46, 46, 46, 46, 46 });
	check_is_money();
}
////

//Header 229

void Read_buffor_credit_ans(void) {
	send_command(11, 0, (uint8_t[] ) { event, res_1A, res_1B, res_2A, res_2B,
					res_3A, res_3B, res_4A, res_4B, res_5A, res_5B });
	check_is_money();
}

void check_money(void) {
	if (money) {
		money--;
		event++;
		res_1A = 6;
		res_1B = 1;
		res_2A = res_1A;
		res_2B = res_1B;
		res_3A = res_2A;
		res_3B = res_2B;
		res_4A = res_3A;
		res_4B = res_3B;
		res_5A = res_4A;
		res_5B = res_4B;
	}
}

void send_command(uint8_t count, uint8_t command, uint8_t * data) {

	uint8_t checksum = 0;

	uart_putc(Host);
	uart_putc(count);
	uart_putc(Device);
	uart_putc(command);

	for (uint8_t i = 0; i < count; i++) {
		uart_putc(data[i]);
		checksum += data[i];
	}

	checksum = checksum + Host + count + Device + command;
	checksum = 256 - checksum;

	uart_putc(checksum);

}

void Set_inhibit(void) {

	if (Inhibit == 1) {
		PORT_Inhibit_Out_1;
	} else {
		PORT_Inhibit_Out_0;
	}

}

void check_is_money(void) {
	Set_inhibit();
	if (PIN_coin_we) {
		FL_coin = 1;
	}

	if ((!(PIN_coin_we)) && (FL_coin)) {
		_delay_us(5);
		if (!(PIN_coin_we)) {
			//Time_out = 0;
			money++;
			FL_coin = 0;
		}
	}
	if (PIN_coin_we) {
		FL_coin = 1;
	}
	check_money();
}
void uart_init(uint16_t ubrr) {
// Ustawienie prêdkoœci transmisji
	UBRRH = (uint8_t) (ubrr >> 8);
	UBRRL = (uint8_t) ubrr;

// W³¹czenie nadajnika i odbiornika
	UCSRB = (1 << RXEN) | (1 << TXEN);

// Ustawienie formatu ramki:
// 8 bitów danych, 1 b it stopu, brak parzystoœci
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

void uart_putc(uint8_t data) {
// Oczekiwanie na zakoñczenie nadawania
	while (!(UCSRA & (1 << UDRE))) {

	}

// Wys³anie danych
	UDR = data;
}

uint8_t uart_ischar(void) {
// Czy w buforze s¹ dane?

	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc(void) {
// Czy w buforze s¹ dane?
	uint8_t x = 0;
	while (!uart_ischar()) {
		x++;
		check_is_money();
		if (x > 15000) {
			check_is_money();
			return 0;

		}
	}

	return UDR;
}

