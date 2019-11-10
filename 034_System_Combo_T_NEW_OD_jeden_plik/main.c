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
	_delay_ms(500);

	Init_Automat();

	for (;;) {
		Check_Money();
		Check_inhbit();
		Disp_Menu();
	}

}

void Disp_Menu(void) {

	if (!FL_Serwish) {
		if (!Money_In_Automat) {
			Time_Disp++;
			if (Time_Disp < 8) {
				Write_LCD(2);
			} else {
				if (Time_Disp > 16) {
					Time_Disp = 0;
				}
				Write_LCD(3);
			}
		} else {
			Write_LCD(4);
		}
	} else {

	}

}

//
void Check_inhbit(void) {
	if (FL_WPBlock) {
		ccTalk_send(BILL_ACCEPTOR, 2, 231, (uint8_t[] ) { 0, 0 });
		_delay_ms(50);
		ccTalk_send(COIN_ACCEPTOR, 2, 231, (uint8_t[] ) { 0, 0 });
		_delay_ms(50);
		uart_clear();
	}

	else {
		ccTalk_send(COIN_ACCEPTOR, 2, 231, (uint8_t[] ) { 252, 0 });
		_delay_ms(50);
		ccTalk_send(BILL_ACCEPTOR, 2, 231, (uint8_t[] ) { 255, 255 });
		_delay_ms(50);
		uart_clear();

	}

}

void Check_Money(void) {
	Bill_Check_Buffor();
	Coin_check_buffor();
}

void Init_Automat(void) {
	Write_LCD(1);
	_delay_ms(2000);
	Check_Connections();
	IO_Combo_Clear_Escrow();
	Init_Coin_Acceptor();
	Init_Bill_Acceptor();
	uart_clear();
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

uint8_t ccTalk_recive(uint8_t *datarecive, uint8_t from) {
	uint8_t tmp[30] = { 0 };
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
	return false;

}

uint8_t uart_getc(void) {
// Czy w buforze s¹ dane?'
	uint16_t timie_out = 16000;
	while (!uart_ischar()) {

		if (!(--timie_out))
			return 0;
	};
	return UDR;
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
	Expense = 5;
	Expense_16 = 50* Expense;
}
////////////////////////LCD
void Write_LCD(uint8_t n) {
	switch (n) {
//	case 0:
//		LCD_Clear();
//
//		break;
	case 1:
		LCD_Clear();
		Write_LCD_String(" TRWA URUCHAMIANIE  ", 1);
		Write_LCD_String("    PROSZE CZEKAC   ", 2);
		Write_LCD_String("                    ", 3);
		Write_LCD_String("                    ", 4);

		break;
	case 2:

		Write_LCD_String("AUTOMATYCZNY SYSTEM ", 1);
		Write_LCD_String("   OBSLUGI KLIENTA  ", 2);
		Write_LCD_String("       WPROWADZ     ", 3);
		Write_LCD_String(" MONETY LUB BANKNOT ", 4);

		break;
	case 3:
		Write_LCD_String(" AUTOMAT PRZYJMUJE  ", 1);
		Write_LCD_String("   10zl 20zl 50zl   ", 2);
		Write_LCD_String("  50gr 1zl 2zl 5zl  ", 3);

		switch (Expense) {
		case 1:
			Write_LCD_String("    KOSZT  50gr     ", 4);
			break;
		case 2:
			Write_LCD_String("     KOSZT  1zl     ", 4);
			break;
		case 3:
			Write_LCD_String("    KOSZT  1,50zl   ", 4);
			break;
		case 4:
			Write_LCD_String("     KOSZT  2zl     ", 4);
			break;
		case 5:
			Write_LCD_String("    KOSZT  2,50zl    ", 4);
			break;
		case 6:
			Write_LCD_String("     KOSZT  3zl     ", 4);
			break;
		case 7:
			Write_LCD_String("    KOSZT  3,50zl    ", 4);
			break;
		case 8:
			Write_LCD_String("     KOSZT  4zl     ", 4);
			break;
		case 9:
			Write_LCD_String("    KOSZT  4,50zl    ", 4);
			break;
		case 10:
			Write_LCD_String("     KOSZT  5zl     ", 4);
			break;
		}
		break;
	case 4:
		if ((Money_In_Automat) >= Expense_16) {
			Write_LCD_String("    WYBIERZ DRZWI   ", 1);

			Write_LCD_String("1         2        3", 2);
			Write_LCD_String("                    ", 3);
			Write_LCD_String("                    ", 4);
		} else {
			Write_LCD_String("    WPROWADZONO     ", 1);
			Write_LCD_String("   ", 2);
			convert_m(((Money_In_Automat / 100)));
			LCD_WriteText(",");
			convert_m(((Money_In_Automat / 100) - (Money_In_Automat)));
			LCD_WriteText("zl");
			Write_LCD_String("      BRAKUJE       ", 3);
			Write_LCD_String("       ", 4);
			convert_m(((Money_In_Automat / 100)) - (Expense_16/100));
			LCD_WriteText(",");
			convert_m(((Money_In_Automat / 100) - (Money_In_Automat))-Expense_16 );
			LCD_WriteText("zl");
			//Write_LCD_String("       ", 4);

		}

		break;
	case 66:
		Write_LCD_String(" AUTOMAT PRZYJMUJE  ", 1);
		Write_LCD_String("   10zl 20zl 50zl   ", 2);
		Write_LCD_String("  50gr 1zl 2zl 5zl  ", 3);
		Write_LCD_String("     ", 4);
		convert_m(Money_In_Automat);
		break;

	}
}

void Write_LCD_String(char * text, uint8_t pos) {
	LCD_GoTo(pos - 1);
	LCD_WriteText(text);
}

void convert_m(uint16_t m) {
	char str[10];

	utoa(m, str, 10);
	LCD_WriteText(str);
}

void Check_IO_Combo(void) {
	uint8_t datarecive[20] = { 0 };

	Write_LCD_String("      IO COMBO      ", 3);
	Write_LCD_String("                    ", 4);
	_delay_ms(1000);

	ccTalk_send(IO_COMBO, 0, 242, 0);
	if (ccTalk_recive(datarecive, IO_COMBO)) {

		if (((*(datarecive + 4)) == IOCOMBOID_NUMBER_)
				&& ((*(datarecive + 5)) == IOCOMBOID_NUMBER_)
				&& ((*(datarecive + 6)) == IOCOMBOID_NUMBER_)) {
			Write_LCD_String("    IO COMBO OK", 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String("   IO COMBO FAIL   ", 4);
			while (1) {
			}
		}

	} else {
		Write_LCD_String("   IO COMBO ERROR   ", 4);
		while (1) {
		}
	}

}

void IO_Combo_Clear_Escrow(void) {
	ccTalk_send(IO_COMBO, 1, 70, (uint8_t[] ) { 1 });
}

uint8_t checkPin(uint16_t pinIn) {
	if (!(pinIn)) {
		return true;
	} else {
		return false;
	}
}

void Check_IO(uint16_t pinIn, char *text) {
	if (checkPin(pinIn)) {
		_delay_ms(2);
		if (checkPin(pinIn)) {
			FL_KEY_SWITCH = 1;
			while (FL_KEY_SWITCH) {
				Write_LCD_String(text, 4);

				if (checkPin(pinIn) == false) {
					_delay_ms(1);
					if (checkPin(pinIn) == false) {
						FL_KEY_SWITCH = 0;
					}
				}
			}
		}
	}
}

void Check_Button_Machine(void) {
	Write_LCD_String("     IO BUTTON      ", 3);
	Write_LCD_String("                    ", 4);
	_delay_ms(1000);
	Check_IO(PIN_BUTTON_1_IN, "  IO BUTTON 1 ERROR ");
	Check_IO(PIN_BUTTON_2_IN, "  IO BUTTON 2 ERROR ");
	Check_IO(PIN_BUTTON_3_IN, "  IO BUTTON 3 ERROR ");
	Check_IO(PIN_KEY_SWITCH_ADMIN_IN, "   IO KEY 1 ERROR   ");
	Check_IO(PIN_KEY_SWITCH_SERWIS_IN, "   IO KEY 2 ERROR   ");
	Write_LCD_String("    IO BUTTON OK    ", 4);
	_delay_ms(1000);
}

void Check_Hopper(void) {
	uint8_t datarecive[20] = { 0 };
	Write_LCD_String("       HOPPER       ", 3);
	Write_LCD_String("                    ", 4);
	_delay_ms(1000);

	ccTalk_send(HOPPER_5ZL, 0, 242, 0);
	if (ccTalk_recive(datarecive, HOPPER_5ZL)) {

		if (((*(datarecive + 4)) == HOPPER5ID_NUMBER_1)
				&& ((*(datarecive + 5)) == HOPPER5ID_NUMBER_2)
				&& ((*(datarecive + 6)) == HOPPER5ID_NUMBER_3)) {
			Write_LCD_String("    HOPPER 1 OK     ", 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String("   HOPPER 1 FAIL   ", 4);
			while (1) {
			}
		}
	} else {
		Write_LCD_String("   HOPPER 1 ERROR   ", 4);
		while (1) {
		}
	}
	ccTalk_send(HOPPER_1ZL, 0, 242, 0);
	if (ccTalk_recive(datarecive, HOPPER_1ZL)) {

		if (((*(datarecive + 4)) == HOPPER1ID_NUMBER_1)
				&& ((*(datarecive + 5)) == HOPPER1ID_NUMBER_2)
				&& ((*(datarecive + 6)) == HOPPER1ID_NUMBER_3)) {
			Write_LCD_String("    HOPPER 2 OK     ", 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String("   HOPPER 2 FAIL   ", 4);
			while (1) {

			}
		}
	} else {
		Write_LCD_String("   HOPPER 2 ERROR   ", 4);
		while (1) {
		}
	}
	ccTalk_send(HOPPER_50GR, 0, 242, 0);
	if (ccTalk_recive(datarecive, HOPPER_50GR)) {

		if (((*(datarecive + 4)) == HOPPER50ID_NUMBER_1)
				&& ((*(datarecive + 5)) == HOPPER50ID_NUMBER_2)
				&& ((*(datarecive + 6)) == HOPPER50ID_NUMBER_3)) {
			Write_LCD_String("    HOPPER 3 OK     ", 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String("   HOPPER 3 FAIL   ", 4);
			while (1) {

			}
		}
	} else {
		Write_LCD_String("   HOPPER 3 ERROR   ", 4);
		while (1) {
		}
	}

}

//
//uint8_t Hopper_PayOut(uint8_t Count, uint8_t Hopper) {
//	uint8_t Data1, Data2, Data3;
//	uint8_t datarecive[30] = { 0 };
//	HopperSend(Hopper, 1, 164, (uint8_t[] ) { 165 }, datarecive);
//	_delay_ms(20);
//	HopperSend(Hopper, 0, 242, (uint8_t[] ) { 0 }, datarecive);
//	_delay_ms(50);
//	Data1 = datarecive[4];
//	Data2 = datarecive[5];
//	Data3 = datarecive[6];
//	HopperSend(Hopper, 0, 236, (uint8_t[] ) { 0 }, datarecive);
//
//	_delay_ms(50);
//
//	HopperSend(Hopper, 4, 167, (uint8_t[] ) { Data1, Data2, Data3, Count },
//			datarecive);
//	_delay_ms(20);
//	return false;
//}
void Check_Coin_Acceptor(void) {
	uint8_t datarecive[20] = { 0 };
	Write_LCD_String("    COIN ACCEPTOR   ", 3);
	Write_LCD_String("                    ", 4);
	_delay_ms(1000);
	ccTalk_send(COIN_ACCEPTOR, 0, 242, (uint8_t[] ) { 0 });

	if (ccTalk_recive(datarecive, COIN_ACCEPTOR)) {

		if (((*(datarecive + 4)) == X6D2SID_NUMBER_1)
				&& ((*(datarecive + 5)) == X6D2SID_NUMBER_2)
				&& ((*(datarecive + 6)) == X6D2SID_NUMBER_3)) {
			Write_LCD_String("  COIN ACCEPTOR OK  ", 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String("COIN ACCEPTOR FAIL", 4);
			while (1) {
			}
		}

	} else {
		Write_LCD_String(" COIN ACCEPTOR ERROR", 4);
		while (1) {
		}
	}

}

void Init_Coin_Acceptor(void) {

	ccTalk_send(COIN_ACCEPTOR, 0, 254, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 245, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 244, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 3, 2 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 4, 3 });
	_delay_ms(75);
	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 5, 1 });
	_delay_ms(75);
	ccTalk_send(COIN_ACCEPTOR, 2, 210, (uint8_t[] ) { 6, 5 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 192, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 246, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 242, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 241, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 0, 4, (uint8_t[] ) { 0 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 1 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 2 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 3 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 4 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 5 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 6 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 7 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 1, 184, (uint8_t[] ) { 8 });
	_delay_ms(75);

	ccTalk_send(COIN_ACCEPTOR, 2, 231, (uint8_t[] ) { 252, 0 });
	_delay_ms(75);

}

void Coin_check_buffor(void) {
	uint8_t datarecive[20] = { 0 };
	ccTalk_send(COIN_ACCEPTOR, 0, 229, (uint8_t[] ) { 0 });
	ccTalk_recive(datarecive, BILL_ACCEPTOR);
	_delay_ms(25);

}

void Check_Bill_Acceptor(void) {
	uint8_t datarecive[20] = { 0 };
	Write_LCD_String("    BILL ACCEPTOR   ", 3);
	Write_LCD_String("                    ", 4);
	_delay_ms(1000);

	ccTalk_send(BILL_ACCEPTOR, 0, 242, (uint8_t[] ) { 0 });
	if (ccTalk_recive(datarecive, BILL_ACCEPTOR)) {

		if (((*(datarecive + 4)) == NV10ID_NUMBER_1)
				&& ((*(datarecive + 5)) == NV10ID_NUMBER_2)
				&& ((*(datarecive + 6)) == NV10ID_NUMBER_3)
				&& ((*(datarecive + 7)) == NV10ID_NUMBER_4))

				{
			Write_LCD_String("  BILL ACCEPTOR OK  ", 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String(" BILL ACCEPTOR FAIL", 4);
			while (1) {
			}
		}

	} else {
		Write_LCD_String(" BILL ACCEPTOR ERROR", 4);
		while (1) {
		}
	}
}

void Init_Bill_Acceptor(void) {

	ccTalk_send(BILL_ACCEPTOR, 0, 254, (uint8_t[] ) { 0 });
	_delay_ms(50);
	ccTalk_send(BILL_ACCEPTOR, 2, 231, (uint8_t[] ) { 255, 255 });
	_delay_ms(50);
	ccTalk_send(BILL_ACCEPTOR, 1, 228, (uint8_t[] ) { 1 });

	_delay_ms(50);

}

void Bill_Check_Buffor(void) {
	uint8_t datarecive[20] = { 0 };
	ccTalk_send(BILL_ACCEPTOR, 0, 159, (uint8_t[] ) { 0 });

	if (ccTalk_recive(datarecive, BILL_ACCEPTOR)) {
		if (*(datarecive + 4) != BillEvent) {
			BillEvent = *(datarecive + 4);
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 1)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 1 });
				_delay_ms(50);

				Money_In_Automat = 1000;

				FL_WPBlock = true;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 2)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 1 });
				_delay_ms(50);
				Money_In_Automat = 2000;
				FL_WPBlock = true;
			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 3)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 1 });
				_delay_ms(50);
				Money_In_Automat = 5000;
				FL_WPBlock = true;

			}

			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 4)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 0 });
				_delay_ms(50);
			}
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 5)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 0 });
				_delay_ms(50);
			}
			if ((*(datarecive + 6) == 1) && (*(datarecive + 5) == 6)) {
				ccTalk_send(BILL_ACCEPTOR, 1, 154, (uint8_t[] ) { 0 });
				_delay_ms(50);
			}
		}
	}
	uart_clear();
}

///EEPROM

