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
				Write_LCD_String(PSTR("AUTOMATYCZNY SYSTEM "), 1);
				Write_LCD_String(PSTR("   OBSLUGI KLIENTA  "), 2);
				Write_LCD_String(PSTR("       WPROWADZ     "), 3);
				Write_LCD_String(PSTR(" MONETY LUB BANKNOT "), 4);
			} else {
				if (Time_Disp > 16) {
					Time_Disp = 0;
				}
				Write_LCD_String(PSTR(" AUTOMAT PRZYJMUJE  "), 1);
				Write_LCD_String(PSTR("   10zl 20zl 50zl   "), 2);
				Write_LCD_String(PSTR("  50gr 1zl 2zl 5zl  "), 3);
				switch (Expense) {
				case 5:
					Write_LCD_String(PSTR("    KOSZT  50gr     "), 4);
					break;
				case 10:
					Write_LCD_String(PSTR("     KOSZT  1zl     "), 4);
					break;
				case 15:
					Write_LCD_String(PSTR("    KOSZT  1,50zl   "), 4);
					break;
				case 20:
					Write_LCD_String(PSTR("     KOSZT  2zl     "), 4);
					break;
				case 25:
					Write_LCD_String(PSTR("    KOSZT  2,50zl    "), 4);
					break;
				case 30:
					Write_LCD_String(PSTR("     KOSZT  3zl     "), 4);
					break;
				case 35:
					Write_LCD_String(PSTR("    KOSZT  3,50zl    "), 4);
					break;
				case 40:
					Write_LCD_String(PSTR("     KOSZT  4zl     "), 4);
					break;
				case 45:
					Write_LCD_String(PSTR("    KOSZT  4,50zl    "), 4);
					break;
				case 50:
					Write_LCD_String(PSTR("     KOSZT  5zl     "), 4);
					break;
				}
			}
		} else {
			if(Money_In_Automat >= Expense)
			{
				Write_LCD_String(PSTR("    WYBIERZ DRZWI   "), 1);

				Write_LCD_String(PSTR("1         2        3"), 2);
				Write_LCD_String(PSTR("                    "), 3);
				Write_LCD_String(PSTR("                    "), 4);
			}

			else
			{
				Write_LCD_String(PSTR("    WPROWADZONO     "), 1);
				Write_LCD_String(PSTR("   "), 2);
				convert_m(((Money_In_Automat / 10)));
				LCD_WriteText(",");
				convert_m(((Money_In_Automat / 10) - (Money_In_Automat)));
				LCD_WriteText("zl");
				Write_LCD_String(PSTR("      BRAKUJE       "), 3);
				Write_LCD_String(PSTR("       "), 4);
				convert_m(((Money_In_Automat / 10)) - (Expense/10));
				LCD_WriteText(",");
				convert_m(((Money_In_Automat / 10) - (Money_In_Automat))-Expense );
				LCD_WriteText("zl");
				//Write_LCD_String("       ", 4);
			}
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
	LCD_Clear();
	Write_LCD_String(" TRWA URUCHAMIANIE", 1);
	Write_LCD_String("    PROSZE CZEKAC", 2);
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
	UCSRC = (1 << 7) | (3 << UCSZ0);
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
	Expense = 25;
}
////////////////////////LCD
void Write_LCD_String(const char * text, uint8_t pos) {
	LCD_GoTo(pos - 1);
	LCD_WriteText(text);
}

void convert_m(uint16_t m) {
	char str[10];

	utoa(m, str, 10);
	LCD_WriteText(str);
}

///EEPROM

