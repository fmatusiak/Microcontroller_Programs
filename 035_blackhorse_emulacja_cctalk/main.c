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

volatile uint8_t FL_coin = 0, event = 0, FL_Route_bill = 1,
		FL_Inhibit = 0, GiveMoney = 0;
volatile uint8_t res_1A = 0, res_1B = 0, res_2A = 0, res_2B = 0, res_3A = 0,
		res_3B = 0, res_4A = 0, res_4B = 0, res_5A = 0, res_5B = 0;

volatile uint16_t money = 0;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51
#define Host 1
#define Device 40

void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void check_is_money(void);
void send_command(uint8_t, uint8_t, uint8_t*);
void uart_clear(void);
void check_money(void);

void Request_equipment_category_id(void);
void Modify_master_inhibit_status(void);
void Modify_inhibit_status(void);
void Request_serial_number_ans(void);
void Request_product_code(void);

void Request_bill_id_data_1(void);
void Request_bill_id_data_2(void);
void Request_bill_id_data_3(void);
void Request_bill_id_data_4(void);
void Request_bill_id_data_5(void);
void Request_bill_id_data_6(void);
void Request_bill_id_data_7(void);
void Request_bill_id_data_8(void);
void Request_bill_id_data_9(void);
void Request_bill_id_data_10(void);
void Request_bill_id_data_11(void);
void Request_bill_id_data_12(void);
void Request_bill_id_data_13(void);
void Request_bill_id_data_14(void);
void Request_bill_id_data_15(void);
void Request_bill_id_data_16(void);

void Request_country_scaling_factor(void);
void Request_software_version(void);
void Request_manufacturer_id(void);
void Request_master_inhibit_status(void);
void Perform_self_check(void);
void Route_bill(void);

void Read_buffor_credit_ans(void);

int main(void) {

	DDR_coin_we;
	coin_we_VCC;
	DDR_LED_CCTALKT;
	PORT_LED_CCTALKT_0;

	uart_init(RS_UBRR);
	_delay_ms(2000);

	for (uint8_t i = 0; i < 40; i++) {
		data[i] = 0;
	}

	while (1) {
		check_is_money();
		data[0] = uart_getc();

		if (data[0] == 0) {
			data[0] = uart_getc();
			if (data[0] == 0) {
				data[0] = uart_getc();
				if (data[0] == 1) {
					data[0] = uart_getc();
					if (data[0] == 253) {
						data[0] = uart_getc();
						if (data[0] == 2) {
							_delay_ms(162);
							uart_putc(40);
						}
					}
				}

			}
		}
		if (data[0] == 40) {
			data[1] = uart_getc();
			data[2] = uart_getc();

			if ((data[0] == 40) && (data[2] == 1)) {

				data[3] = uart_getc();
				data[4] = uart_getc();

				for (uint8_t i = 0; i < data[1]; i++) {
					data[i + 5] = uart_getc();
				}

				if ((data[0] == 40) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 252) && (data[4] == 219)) {
					_delay_ms(162);
					uart_putc(40);
				}


				if ((data[0] == 40) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 246) && (data[4] == 225)) {
					Request_manufacturer_id();
				}




				if ((data[0] == 40) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 245) && (data[4] == 226)) {
					Request_equipment_category_id();
				}

				if ((data[0] == 40) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 244) && (data[4] == 227)) {
					Request_product_code();
				}

				if ((data[0] == 40) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 242) && (data[4] == 229)) {
					Request_serial_number_ans();
				}

				if ((data[0] == 40) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 241) && (data[4] == 230)) {
					Request_software_version();
				}

				if ((data[0] == 40) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 232) && (data[4] == 239)) {
					Perform_self_check();
				}

				if ((data[0] == 40) && (data[1] == 2) && (data[2] == 1)
						&& (data[3] == 231) && (data[4] == 0) && (data[5] == 0)
						&& (data[6] == 238)) {
					FL_Inhibit = 1;
					Modify_inhibit_status();

				}

				if ((data[0] == 40) && (data[1] == 2) && (data[2] == 1)
						&& (data[3] == 231) && (data[4] != 0)
						&& (data[5] == 0)) {
					FL_Inhibit = 0;
					Modify_inhibit_status();

				}

				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 228) && (data[4] == 0)
						&& (data[5] == 242)) {
					FL_Inhibit = 1;
					Modify_master_inhibit_status();
				}

				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 228) && (data[4] == 1)
						&& (data[5] == 241)) {
					FL_Inhibit = 0;
					Modify_master_inhibit_status();
				}

				if ((data[0] == 40) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 227) && (data[4] == 244)) {
					Request_master_inhibit_status();
				}

				if ((data[0] == 40) && (data[1] == 0) && (data[2] == 1)
						&& (data[3] == 159) && (data[4] == 56)) {
					Read_buffor_credit_ans();
				}

				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 1)
						&& (data[5] == 56)) {
					Request_bill_id_data_1();
				}

				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 2)
						&& (data[5] == 55)) {
					Request_bill_id_data_2();
				}

				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 3)
						&& (data[5] == 54)) {
					Request_bill_id_data_3();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 4)
						&& (data[5] == 53)) {
					Request_bill_id_data_4();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 5)
						&& (data[5] == 52)) {
					Request_bill_id_data_5();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 6)
						&& (data[5] == 51)) {
					Request_bill_id_data_6();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 7)
						&& (data[5] == 50)) {
					Request_bill_id_data_7();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 8)
						&& (data[5] == 49)) {
					Request_bill_id_data_8();
				}

				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 9)
						&& (data[5] == 48)) {
					Request_bill_id_data_9();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 10)
						&& (data[5] == 47)) {
					Request_bill_id_data_10();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 11)
						&& (data[5] == 46)) {
					Request_bill_id_data_11();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 12)
						&& (data[5] == 45)) {
					Request_bill_id_data_12();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 13)
						&& (data[5] == 44)) {
					Request_bill_id_data_13();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 14)
						&& (data[5] == 43)) {
					Request_bill_id_data_14();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 15)
						&& (data[5] == 42)) {
					Request_bill_id_data_15();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 157) && (data[4] == 16)
						&& (data[5] == 41)) {
					Request_bill_id_data_16();
				}
				if ((data[0] == 40) && (data[1] == 2) && (data[2] == 1)
						&& (data[3] == 156) && (data[4] == 80)
						&& (data[5] == 76) && (data[6] == 157)) {
					Request_country_scaling_factor();
				}
				if ((data[0] == 40) && (data[1] == 1) && (data[2] == 1)
						&& (data[3] == 154) && (data[4] == 1)
						&& (data[5] == 59)) {
					Route_bill();
				}

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

//Header 246
void Request_manufacturer_id(void) {

	send_command(3, 0, (uint8_t[] ) { 73, 84, 76 });
	check_is_money();
}

//Header 245
void Request_equipment_category_id(void) {

	send_command(14, 0, (uint8_t[] ) { 66, 105, 108, 108, 32, 86, 97, 108, 105,
					100, 97, 116, 111, 114, 128 });
	check_is_money();
}

//Header 244
void Request_product_code(void) {

	send_command(4, 0, (uint8_t[] ) { 78, 86, 49, 48 });
	check_is_money();
}
//Header 242
void Request_serial_number_ans(void) {

	send_command(4, 0, (uint8_t[] ) { 242, 143, 4, 0 });
	check_is_money();
}

//Header 241
void Request_software_version(void) {

	send_command(9, 0, (uint8_t[] ) { 78, 86, 49, 48, 51, 50, 57, 48, 55 });
	check_is_money();
}
//Header 232
void Perform_self_check(void) {

	send_command(1, 0, (uint8_t[] ) { 0 });
	check_is_money();
}
//Header 231
void Modify_inhibit_status(void) {

	send_command(0, 0, (uint8_t[] ) { 0 });
	check_is_money();
}

//Header 228
void Modify_master_inhibit_status(void) {

	send_command(0, 0, (uint8_t[] ) { 0 });
	check_is_money();
}

//Header 227
void Request_master_inhibit_status(void) {

	send_command(1, 0, (uint8_t[] ) { 0 });
	check_is_money();
}

//Header 159

void Read_buffor_credit_ans(void) {

	send_command(11, 0, (uint8_t[] ) { event, res_1A, res_1B, res_2A, res_2B,
					res_3A, res_3B, res_4A, res_4B, res_5A, res_5B });
	check_money();
}

//Header 157
void Request_bill_id_data_1(void) {

	send_command(7, 0, (uint8_t[] ) { 80, 76, 48, 48, 49, 48, 65 });
	check_is_money();
}
//Header 157
void Request_bill_id_data_2(void) {

	send_command(7, 0, (uint8_t[] ) { 80, 76, 48, 48, 50, 48, 65 });
	check_is_money();
}
//Header 157
void Request_bill_id_data_3(void) {

	send_command(7, 0, (uint8_t[] ) { 80, 76, 48, 48, 53, 48, 65 });
	check_is_money();
}
//Header 157
void Request_bill_id_data_4(void) {

	send_command(7, 0, (uint8_t[] ) { 80, 76, 48, 49, 48, 48, 65 });
	check_is_money();
}
//Header 157
void Request_bill_id_data_5(void) {

	send_command(7, 0, (uint8_t[] ) { 80, 76, 48, 50, 48, 48, 65 });
	check_is_money();
}
//Header 157
void Request_bill_id_data_6(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
}

//Header 157
void Request_bill_id_data_7(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
}

//Header 157
void Request_bill_id_data_8(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
}
//Header 157
void Request_bill_id_data_9(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
} //Header 157
void Request_bill_id_data_10(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
} //Header 157
void Request_bill_id_data_11(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
} //Header 157
void Request_bill_id_data_12(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
} //Header 157
void Request_bill_id_data_13(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
} //Header 157
void Request_bill_id_data_14(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
} //Header 157
void Request_bill_id_data_15(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
} //Header 157
void Request_bill_id_data_16(void) {

	send_command(7, 0, (uint8_t[] ) { 0, 0, 0, 0, 0, 0, 0 });
	check_is_money();
}
//Header 156
void Request_country_scaling_factor(void) {
	send_command(3, 0, (uint8_t[] ) { 100, 0, 2 });
	check_is_money();
}

//Header 154
void Route_bill(void) {
	send_command(0, 0, (uint8_t[] ) { 0 });

	FL_Route_bill = 1;
}

//*********************************************

void check_money(void) {
	if (money) {
		money--;
		event++;
		if (event == 0) {
			event++;
		}

		res_5B = res_4B;
		res_5A = res_4A;
		res_4B = res_3B;
		res_4A = res_3A;
		res_3B = res_2B;
		res_3A = res_2A;
		res_2B = res_1B;
		res_2A = res_1A;
		res_1B = 0;
		res_1A = 5;

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

void check_is_money(void) {

	if (PIN_coin_we) {
		FL_coin = 1;
	}

	if ((!(PIN_coin_we)) && (FL_coin)) {
		_delay_us(5);
		if (!(PIN_coin_we)) {
			//Time_out = 0;

			if (FL_Inhibit == 0) {

				money += 250;
			}
			FL_coin = 0;
		}
	}
	if (PIN_coin_we) {
		FL_coin = 1;
	}

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
		if (x > 15000) {
			PORT_LED_CCTALKT_0;
			return 0;
		}
	}
	PORT_LED_CCTALKT_1;
	return UDR;
}

