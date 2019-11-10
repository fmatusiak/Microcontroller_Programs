#include "main.h"

//uint32_t EEMEM Money_In_EEPROM = 0;
//uint8_t EEMEM Last_Transaction_EEPROM = 0;
//uint8_t EEMEM Expense_EEPROM = 0;
//uint16_t EEMEM Money_5zl_EEPROM = 0;
//uint16_t EEMEM Money_1zl_EEPROM = 0;
//uint16_t EEMEM Money_50gr_EEPROM = 0;

int main(void) {
	LCD_Initalize();
	uart_init(RS_UBRR);

	gpioInit();

	//eeprom_write_byte(&Expense_EEPROM, (5));
	//initEEprom();

	_delay_ms(500);

	//Init_Automat();
	//
	for(;;){
		Check_Money();
		Disp_Menu();
		//	Check_Button();
//		Check_Payout();
		//Check_Key_Switch();

	}

}
//
void Check_Money(void) {
	if (FL_WPBlock == false) {
		Coin_Acceptor_unhibit();
		Bill_Acceptor_unhibit();

		Coin_check_buffor();
		Bill_Check_Buffor();

	} else {
		Coin_Acceptor_inhibit();
		Bill_Acceptor_inhibit();
	}

}

void Disp_Menu(void) {

	if (!(FL_Serwish)) {
		if (FL_WPBlock == false) {
			Time_Disp++;
			if (Time_Disp < 4) {
				convert_m(FL_WPBlock);
			} else {
				Write_LCD(3);
				if (Time_Disp > 4) {
					Time_Disp = 0;
				}
			}

		}
		_delay_ms(20);
		uart_putc(FL_WPBlock);
		_delay_ms(20);
	} else {
		convert_m(FL_WPBlock);
	}

}

//void Check_Key_Switch() {
//	if ((!(PIN_KEY_SWITCH_SERWIS_IN)) && (PIN_KEY_SWITCH_ADMIN_IN)) {
//		_delay_ms(2);
//		if ((!(PIN_KEY_SWITCH_SERWIS_IN)) && (PIN_KEY_SWITCH_ADMIN_IN)) {
//			while (1) {
//				Write_LCD(10);
//				Refil();
//			}
//			RESET_MACHINE();
//		}
//	}
//
//	if (((PIN_KEY_SWITCH_SERWIS_IN)) && (!(PIN_KEY_SWITCH_ADMIN_IN))) {
//		Write_LCD(10);
//		Refil();
//		Dump();
//
//	}
//
//}
void Refil(void) {

}
//void save_counters(uint32_t Money_In_Fun, uint16_t Money_5zl_Fun,
//		uint16_t Money_1zl_Fun, uint16_t Money_50gr_Fun) {
//
//	if (Money_In_Fun) {
//		Money_In += Money_In_Fun;
//		eeprom_write_dword(&Money_In_EEPROM, (Money_In));
//	}
//
//	if (Money_5zl_Fun) {
//		Money_5zl += Money_5zl_Fun;
//		eeprom_write_word(&Money_5zl_EEPROM, (Money_5zl));
//	}
//
//	if (Money_1zl_Fun) {
//		Money_1zl += Money_1zl_Fun;
//		eeprom_write_word(&Money_1zl_EEPROM, (Money_1zl));
//	}
//
//	if (Money_50gr_Fun) {
//		Money_50gr += Money_50gr_Fun;
//		eeprom_write_word(&Money_50gr_EEPROM, (Money_50gr));
//	}
//}
//
//void read_counters_eeprom(void) {
//	Money_In = eeprom_read_dword(&Money_In_EEPROM);
//	Money_5zl = eeprom_read_word(&Money_5zl_EEPROM);
//	Money_1zl = eeprom_read_word(&Money_1zl_EEPROM);
//	Money_50gr = eeprom_read_word(&Money_50gr_EEPROM);
//
//}
//
//void read_settings_eeprom(void) {
//	Expense = eeprom_read_byte(&Expense_EEPROM);
//}
//
//void save_settings_eeprom(void) {
//	eeprom_write_byte(&Expense_EEPROM, (Expense));
//}
//
//void initEEprom(void) {
//	read_settings_eeprom();
//	read_counters_eeprom();
//	save_counters(0, 0, 0, 0);
//	save_settings_eeprom();
//
//}

void RESET_MACHINE(void) {
	LCD_Clear();
	Init_Automat();
}

void Init_Automat(void) {
	Write_LCD(1);
	delayS(2);
	Check_Connections();
	IO_Combo_Clear_Escrow();
	Init_Coin_Acceptor();
	Init_Bill_Acceptor();

}

void Check_Connections(void) {

	Check_Button_Machine();
	Check_Hopper();
	Check_Bill_Acceptor();
	Check_Coin_Acceptor();
	Check_IO_Combo();

}

////UART
void uartPut(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,
		uint8_t *data) {

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
	while (!(UCSRA & (1 << UDRE)))
		;

	// Wys³anie danych
	UDR = data;
}

uint8_t uart_ischar(void) {
	// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

void uart_clear(void) {
	uint8_t clr;
	while ( UCSRA & (1 << RXC)) {
		clr = UDR;
	}
}


uint8_t ccTalk_send(uint8_t dataCount, uint8_t command, uint8_t *data,
		uint8_t *datarecive, uint8_t from) {
	uint8_t tmp[30];

	for (uint8_t l = 0; l < 5; l++) {
		uart_putc(from);
		uart_putc(dataCount);
		uart_putc(CONTROLER);
		uart_putc(command);
		uint8_t checkSum = from + CONTROLER + command + dataCount;

		for (uint8_t i = 0; i < dataCount; i++) {
			uart_putc(data[i]);
			checkSum += data[i];
		}
		checkSum = 256 - checkSum;

		uart_putc(checkSum);

		for (uint8_t i = 0; i < 10; i++) {
			tmp[i] = uart_getc();
		}

		for (uint8_t i = 0; i < (tmp[1] + tmp[6 + tmp[1]]); i++) {
			tmp[i + 10] = uart_getc();
		}

		_delay_ms(30);

		if ((tmp[5 + tmp[1]] == CONTROLER) && (tmp[7 + tmp[1]] == from)) {
			for (uint8_t i = 0; i < 5 + tmp[6 + tmp[1]]; i++) {
				datarecive[i] = tmp[i + 5 + tmp[1]];
			}

			return true;
		}

	}
	return false;
}

uint16_t uart_getc(void) {
	// Czy w buforze s¹ dane?'
	uint16_t timie_out = 13000;
	while (!uart_ischar()) {
		timie_out--;
		if (!timie_out)
			return 1000;
	};
	return UDR;
}

void delayS(uint8_t time) {
	for (uint8_t i = 0; i < time; i++) {
		_delay_ms(1000);
	}
}

void gpioInit() {
	DDR_BUTTON_1_IN;
	DDR_BUTTON_2_IN;
	DDR_BUTTON_3_IN;
	DDR_KEY_SWITCH_ADMIN_IN;
	DDR_KEY_SWITCH_SERWIS_IN;

	RELAY_1_OUT_DDR;
	RELAY_2_OUT_DDR;
	RELAY_3_OUT_DDR;
	HPOW_OUT_DDR;

	BUTTON_1_IN_VCC;
	BUTTON_2_IN_VCC;
	BUTTON_3_IN_VCC;
	KEY_SWITCH_ADMIN_IN_VCC;
	KEY_SWITCH_SERWIS_IN_VCC;

	RELAY_1_OUT_LOW;
	RELAY_2_OUT_LOW;
	RELAY_3_OUT_LOW;

	HPOW_OUT_HIGH;

	_delay_ms(100);
	FL_KEY_SWITCH = 1;
	FL_Serwish = 0;
	Time_Disp = 1;
	FL_WPBlock = false;
	BillEvent = 0;
	Money_In_Automat = 0;
}
////////////////////////LCD

///EEPROM

