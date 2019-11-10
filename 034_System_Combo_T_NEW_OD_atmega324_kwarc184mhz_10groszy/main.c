#include "main.h"
//uint16_t EEMEM Money_In_EEPROM = 0;
uint8_t EEMEM First_Run_EEPROM = 0;
uint8_t EEMEM Expense_EEPROM = 0;
uint16_t EEMEM Money_5zl_EEPROM = 0;
uint16_t EEMEM Money_1zl_EEPROM = 0;
uint16_t EEMEM Money_50gr_EEPROM = 0;

int main(void) {
	LCD_Initalize();
	uart_init(RS_UBRR);

	gpioInit();
	StanVar();
	_delay_ms(500);

	Check_Admin_Start();
	Init_Automat();

	for (;;) {
		Check_Button_Door();
		Check_inhbit();
		Set_Hopper_Opto();
		Set_Sorter();
		Set_Expense_Hopper();
		Check_Button_Door();
		Check_Admin();
		Check_Time_Out_Money();
		Set_Open_Door();
		Check_Button_Door();

		if (FL_Dead_Comm) {
			while (true) {
				Write_LCD(13);
			}

		}

		if ((FL_Serwish == 0) && (FL_Adminh == 0) && (FL_Blocked)) {
			if ((Door_One == 0) && (Door_Two == 0) && (Door_Three == 0)) {
				Write_LCD(6);
			}
		}

		if (FL_Serwish) {
			Write_LCD_String_FLASH(PSTR("   STACYJKA SERWIS   "), 1);
			Refil();
			FL_Restart = 1;
		}

		if ((FL_Serwish == 0) && (FL_Adminh == 0) && (FL_Blocked == 0)) {
			Check_Money();
			Check_Button_Door();
			Disp_Menu();

			Set_Expense_Hopper();
		}

		if ((FL_Restart == 1) && (FL_Adminh == 0) && (FL_Serwish == 0)) {
			FL_Restart = 0;
			Save_Money_Hopper();
			Init_Automat();
		}

		if (FL_Adminh) {
			Write_LCD_String_FLASH(PSTR("   STACYJKA ADMIN   "), 1);
			Refil();
			Dumpowanie();
			FL_Restart = 1;

		}

	}

}

void Check_Button_Door(void) {

	if (Money_In_Automat == 0) {
		if ((checkPin(PIN_BUTTON_1_IN)) && (FL_Key_One)) {
			_delay_ms(1);
			if ((checkPin(PIN_BUTTON_1_IN))) {
				FL_Key_One = 0;
				IO_Combo_Claer_Acceptor();
			}
		}

		if ((!(checkPin(PIN_BUTTON_1_IN))) && (FL_Key_One == 0)) {
			FL_Key_One = 1;
		}

		if ((checkPin(PIN_BUTTON_2_IN)) && (FL_Key_Two)) {
			_delay_ms(1);
			if (checkPin(PIN_BUTTON_2_IN)) {
				FL_Key_Two = 0;
				IO_Combo_Claer_Acceptor();
			}
		}

		if ((!(checkPin(PIN_BUTTON_2_IN))) && (FL_Key_Two == 0)) {
			FL_Key_Two = 1;
		}

		if ((checkPin(PIN_BUTTON_3_IN)) && (FL_Key_Three)) {
			_delay_ms(1);
			if (checkPin(PIN_BUTTON_3_IN)) {
				FL_Key_Three = 0;
				IO_Combo_Claer_Acceptor();
			}
		}

		if ((!(checkPin(PIN_BUTTON_3_IN))) && (FL_Key_Three == 0)) {
			FL_Key_Three = 1;
		}
	}

	if (Money_In_Automat >= Expense_Atmega) {
		if (checkPin(PIN_BUTTON_1_IN)) {
			_delay_ms(1);
			if (checkPin(PIN_BUTTON_1_IN)) {

				PayOut();
				Door_One = 1;
			}
		}

		if (checkPin(PIN_BUTTON_2_IN)) {
			_delay_ms(1);
			if (checkPin(PIN_BUTTON_2_IN)) {

				PayOut();
				Door_Two = 1;
			}
		}
		if (checkPin(PIN_BUTTON_3_IN)) {
			_delay_ms(1);
			if (checkPin(PIN_BUTTON_3_IN)) {

				PayOut();
				Door_Three = 1;
			}
		}
	}
}

void Check_Time_Out_Money(void) {

	if (IS_TIME_OUT) {
		if (Money_In_Automat) {
			Time_out_Money++;

			if (Time_out_Money >= TIME_OUT_MONEY) {
				Time_out_Money = 0;
				Money_In_Automat = 0;
				Save_Money_Hopper();
				IO_Combo_Clear_Escrow();
			}

		}
	}
}

void error_payout(void) {
	if (FL_ERROR) {

		while (FL_ERROR) {
			Write_LCD(11);
			_delay_ms(1500);
			Write_LCD(12);
			_delay_ms(1500);
			Check_Admin();

			if (FL_Adminh || FL_Serwish) {
				FL_ERROR = 0;
			}
		}
	}
}

void Set_Open_Door(void) {
	if (Door_One) {
		Tmp_Time_Door++;
		RELAY_1_OUT_HIGH;
		Write_LCD(8);
		if (Tmp_Time_Door >= 11) {
			Tmp_Time_Door = 0;
			Door_One = 0;
			RELAY_1_OUT_LOW;
			error_payout();
		}
	}

	if (Door_Two) {
		Tmp_Time_Door++;
		RELAY_2_OUT_HIGH;
		Write_LCD(9);
		if (Tmp_Time_Door >= 11) {
			Tmp_Time_Door = 0;
			Door_Two = 0;
			RELAY_2_OUT_LOW;
			error_payout();
		}
	}

	if (Door_Three) {
		Tmp_Time_Door++;
		RELAY_3_OUT_HIGH;
		Write_LCD(10);
		if (Tmp_Time_Door >= 11) {
			Tmp_Time_Door = 0;
			Door_Three = 0;
			RELAY_3_OUT_LOW;
			error_payout();
		}
	}

}

void Disp_Menu(void) {

	if ((FL_Serwish == 0) && (FL_Adminh == 0)) {
		if (!Money_In_Automat) {

			if ((Door_One == 0) && (Door_Two == 0) && (Door_Three == 0)) {
				Time_Disp++;
				if (Time_Disp < 8) {
					Write_LCD(1);
				} else {
					if (Time_Disp > 16) {
						Time_Disp = 0;
					}
					Write_LCD(2);
				}
			}
		} else {
			if (Money_In_Automat >= Expense_Atmega) {

				Time_Disp++;
				if (Time_Disp < 8) {
					Write_LCD(7);
				} else {
					if (Time_Disp > 16) {
						Time_Disp = 0;
					}
					Write_LCD(14);
				}

			}

			else {
				Write_LCD(4);
			}
		}
	}

}

//

void Check_Admin(void) {
	if ((checkPin(PIN_KEY_SWITCH_SERWIS_IN))
			&& (!(checkPin(PIN_KEY_SWITCH_ADMIN_IN)))) {
		_delay_ms(2);
		if ((checkPin(PIN_KEY_SWITCH_SERWIS_IN))
				&& (!(checkPin(PIN_KEY_SWITCH_ADMIN_IN)))) {
			FL_Serwish = 1;
		}
	} else {
		FL_Serwish = 0;
	}

	if (!(checkPin(PIN_KEY_SWITCH_SERWIS_IN))
			&& ((checkPin(PIN_KEY_SWITCH_ADMIN_IN)))) {
		_delay_ms(2);
		if (!(checkPin(PIN_KEY_SWITCH_SERWIS_IN))
				&& ((checkPin(PIN_KEY_SWITCH_ADMIN_IN)))) {
			FL_Adminh = 1;
		}
	} else {
		FL_Adminh = 0;
	}

}
void Check_inhbit(void) {
	if ((FL_WPBlock) || (FL_Blocked)) {
		ccTalk_send(BILL_ACCEPTOR, 2, 231, (uint8_t[] ) { 0, 0 });
		_delay_ms(50);
		ccTalk_send(COIN_ACCEPTOR, 2, 231, (uint8_t[] ) { 0, 0 });
		_delay_ms(50);
		uart_clear();
	}

	else {
		ccTalk_send(COIN_ACCEPTOR, 2, 231, (uint8_t[] ) { Inhibit_Coin, 0 }); //252
		_delay_ms(50);
		ccTalk_send(BILL_ACCEPTOR, 2, 231, (uint8_t[] ) { 255, 255 });
		_delay_ms(50);
		uart_clear();
	}

}

void Check_Money(void) {
	Bill_Check_Buffor();
	Coin_check_buffor();

	if (Money_In_Automat >= Expense_Atmega) {
		FL_WPBlock = true;
	} else {
		FL_WPBlock = false;
	}

}

void Init_Automat(void) {
	StanVar();
	LCD_Clear();
	Write_LCD_String_FLASH(PSTR(" TRWA URUCHAMIANIE  "), 1);
	Write_LCD_String_FLASH(PSTR("    PROSZE CZEKAC   "), 2);

	_delay_ms(2000);
	Check_Connections();
	Init_Dev();
	Init_EEProm();

	uart_clear();
	LCD_Clear();
}

void Init_Dev(void) {
	IO_Combo_Clear_Escrow();
	Set_Hopper_Opto();
	Coin_check_buffor();
	Coin_Clear_buffor();
	Bill_Clear_buffor();
	Init_Coin_Acceptor();
	Init_Bill_Acceptor();
}

void Check_Connections(void) {
	Check_Button_Machine();
	Check_Bill_Acceptor();
	Check_Coin_Acceptor();
	Check_Hopper();
	Check_IO_Combo();

}

////UART

void uart_init(uint16_t ubrr) {
	// Ustawienie prêdkoœci transmisji
	UBRR0H = (uint8_t) (ubrr >> 8);
	UBRR0L = (uint8_t) ubrr;

	// W³¹czenie nadajnika i odbiornika
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// Ustawienie formatu ramki:
	// 8 bitów danych, 1 b it stopu, brak parzystoœci
	UCSR0C = (1 << UCSZ01) | (3 << UCSZ00);
}

void uart_putc(uint8_t data) {
	// Oczekiwanie na zakoñczenie nadawania
	while (!(UCSR0A & (1 << UDRE0))) {
	};

	// Wys³anie danych
	UDR0 = data;
}

uint8_t uart_ischar(void) {
	// Czy w buforze s¹ dane?
	return (UCSR0A & (1 << RXC0));
}

void uart_clear(void) {
	uint8_t clr;
	while ( UCSR0A & (1 << RXC0)) {
		clr = UDR0;
	}
}

void ccTalk_send(uint8_t from, uint8_t dataCount, uint8_t command,
		uint8_t *data) {
	uart_clear();
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

}

uint8_t ccTalk_recive_no_timeout(uint8_t *datarecive, uint8_t from) {
	uint8_t tmp[30] = { 0 };

	for (uint8_t ziet = 0; ziet < 5; ziet++) {

		for (uint8_t i = 0; i < 10; i++) {
			tmp[i] = uart_getc_no_timeout();
		}

		for (uint8_t i = 0; i < (tmp[1] + tmp[6 + tmp[1]]); i++) {
			tmp[i + 10] = uart_getc_no_timeout();
		}

		if ((tmp[5 + tmp[1]] == CONTROLER) && (tmp[7 + tmp[1]] == from)) {
			for (uint8_t i = 0; i < 5 + tmp[6 + tmp[1]]; i++) {
				datarecive[i] = tmp[i + 5 + tmp[1]];
			}
			_delay_ms(60);
			uart_clear();
			return true;
		}
		_delay_ms(60);
	}
	FL_Dead_Comm = 1;
	uart_clear();
	return false;

}

uint8_t uart_getc_no_timeout(void) {
	// Czy w buforze s¹ dane?'
	uint32_t timie_out = 80000;

	while (!uart_ischar()) {
		if (!(--timie_out))
			return 0;
	};
	return UDR0;
}

uint8_t uart_getc(void) {
	// Czy w buforze s¹ dane?'
	uint16_t timie_out = 45000;
	while (!uart_ischar()) {

		if (!(--timie_out))
			return 0;
	};
	return UDR0;
}

uint8_t ccTalk_recive(uint8_t *datarecive, uint8_t from) {
	uint8_t tmp[30] = { 0 };

	for (uint8_t ziet = 0; ziet < 5; ziet++) {

		for (uint8_t i = 0; i < 10; i++) {
			tmp[i] = uart_getc();
		}

		for (uint8_t i = 0; i < (tmp[1] + tmp[6 + tmp[1]]); i++) {
			tmp[i + 10] = uart_getc();
		}

		if ((tmp[5 + tmp[1]] == CONTROLER) && (tmp[7 + tmp[1]] == from)) {
			for (uint8_t i = 0; i < 5 + tmp[6 + tmp[1]]; i++) {
				datarecive[i] = tmp[i + 5 + tmp[1]];
			}
			_delay_ms(50);
			uart_clear();
			return true;
		}
		_delay_ms(50);
		uart_clear();
	}
	FL_Dead_Comm = 1;
	return false;

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

	_delay_ms(50);

}
////////////////////////LCD

///EEPROM

void Init_EEProm(void) {

	Money_5zl_Atmega = 0;
	Money_1zl_Atmega = 0;
	Money_50gr_Atmega = 0;
	Expense_Atmega = 0;
	Last_Transaction_Atmega = 0;
	First_Run = 0;

	First_Run = eeprom_read_byte(&First_Run_EEPROM);
	if (First_Run != 2) {
		First_Run = 2;
		eeprom_write_byte(&First_Run_EEPROM, First_Run);

		Money_5zl_Atmega = 0;
		Money_1zl_Atmega = 0;
		Money_50gr_Atmega = 0;
		Expense_Atmega = 25;

		eeprom_write_word(&Money_5zl_EEPROM, Money_5zl_Atmega);
		eeprom_write_word(&Money_1zl_EEPROM, Money_1zl_Atmega);
		eeprom_write_word(&Money_50gr_EEPROM, Money_50gr_Atmega);
		eeprom_write_byte(&Expense_EEPROM, Expense_Atmega);
	}

	Expense_Atmega = eeprom_read_byte(&Expense_EEPROM);

	Money_5zl_Atmega = eeprom_read_word(&Money_5zl_EEPROM);
	Money_1zl_Atmega = eeprom_read_word(&Money_1zl_EEPROM);
	Money_50gr_Atmega = eeprom_read_word(&Money_50gr_EEPROM);

	if (Money_5zl_Atmega >= 65535) {
		Money_5zl_Atmega++;
	}

	if (Money_1zl_Atmega >= 65535) {
		Money_1zl_Atmega++;
	}
	if (Money_50gr_Atmega >= 65535) {
		Money_50gr_Atmega++;
	}

	Save_Money_Hopper();
}

void Save_Money_Hopper(void) {
	eeprom_write_word(&Money_5zl_EEPROM, Money_5zl_Atmega);
	eeprom_write_word(&Money_1zl_EEPROM, Money_1zl_Atmega);
	eeprom_write_word(&Money_50gr_EEPROM, Money_50gr_Atmega);

}

void Check_Admin_Start(void) {
	if (checkPin(PIN_KEY_SWITCH_ADMIN_IN)) {
		SterWhile = 1;
		Expense_Atmega = 25;
		LCD_Clear();
		Write_LCD(5);
		while (SterWhile) {

			if (checkPin(PIN_BUTTON_1_IN) && (FL_Button_1)) {
				if (Expense_Atmega <= 95) {
					Expense_Atmega += 5;
					FL_Button_1 = 0;
					Write_LCD(5);
				}
			}

			if (!(checkPin(PIN_BUTTON_1_IN)) && (FL_Button_1 == 0)) {
				FL_Button_1 = 1;
			}

			if (checkPin(PIN_BUTTON_3_IN) && (FL_Button_3)) {
				if (Expense_Atmega > 5) {
					Expense_Atmega -= 5;
					FL_Button_3 = 0;
					Write_LCD(5);
				}
			}

			if (!(checkPin(PIN_BUTTON_3_IN)) && (FL_Button_3 == 0)) {
				FL_Button_3 = 1;
			}

			if (checkPin(!(PIN_KEY_SWITCH_ADMIN_IN))) {
				_delay_ms(2);
				if (checkPin(!(PIN_KEY_SWITCH_ADMIN_IN))) {
					SterWhile = 0;
				}
			}
		}
		eeprom_write_byte(&Expense_EEPROM, Expense_Atmega);

	}
}

uint8_t RNG(void) {
	Seed_RNG = (Seed_RNG_A * Seed_RNG + Seed_RNG_C);
	return Seed_RNG % 257;
}

void StanVar(void) {
	FL_Serwish = 0;
	FL_Adminh = 0;

	Time_Disp = 1;
	FL_WPBlock = false;
	BillEvent = 0;
	FL_KEY_SWITCH = 0;
	Money_In_Automat = 0;
	Expense_Atmega = 0;
	Last_Transaction_Atmega = 0;
	FL_Button_1 = 0;
	FL_Button_2 = 0;
	FL_Button_3 = 0;
	Time_out_Money = 0;
	FL_Dead_Comm = 0;
	Stan_Hopper = 0;
	Inhibit_Coin = 252;
	Seed_RNG = 10;

	Money_5zl_Atmega = 0;
	Money_1zl_Atmega = 0;
	Money_50gr_Atmega = 0;
	CoinEvent = 0;
	SterWhile = 0;
	Tmp_Time_Door = 0;
	Door_One = 0;
	Door_Two = 0;
	Door_Three = 0;
	FL_Blocked = 0;
	FL_ERROR = 0;
	FL_Cena_UP = 0;

	Hopper_One_Opto = 3;
	Hopper_Two_Opto = 3;
	Hopper_Three_Opto = 3;
	FL_Restart = 0;
}
