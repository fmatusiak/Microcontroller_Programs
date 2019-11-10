/*
 * LCD.c
 *
 *  Created on: 17 lip 2017
 *      Author: dell
 */
#include "LCD.h"

void Write_LCD(uint8_t n) {
	switch (n) {
	case 1:
		Write_LCD_String_FLASH(PSTR("AUTOMATYCZNY SYSTEM "), 1);
		Write_LCD_String_FLASH(PSTR("   OBSLUGI KLIENTA  "), 2);
		Write_LCD_String_FLASH(PSTR("      WPROWADZ      "), 3);
		Write_LCD_String_FLASH(PSTR(" MONETY LUB BANKNOT "), 4);
		break;
	case 2:
		Write_LCD_String_FLASH(PSTR(" AUTOMAT PRZYJMUJE  "), 1);
		Write_LCD_String_FLASH(PSTR("   10zl 20zl 50zl   "), 2);
		Write_LCD_String_FLASH(PSTR("  50gr 1zl 2zl 5zl  "), 3);
		switch (Expense_Atmega) {
		case 5:
			Write_LCD_String_FLASH(PSTR("    KOSZT  50gr     "), 4);
			break;
		case 10:
			Write_LCD_String_FLASH(PSTR("     KOSZT  1zl     "), 4);
			break;
		case 15:
			Write_LCD_String_FLASH(PSTR("    KOSZT  1,50zl   "), 4);
			break;
		case 20:
			Write_LCD_String_FLASH(PSTR("     KOSZT  2zl     "), 4);
			break;
		case 25:
			Write_LCD_String_FLASH(PSTR("    KOSZT  2,50zl    "), 4);
			break;
		case 30:
			Write_LCD_String_FLASH(PSTR("     KOSZT  3zl     "), 4);
			break;
		case 35:
			Write_LCD_String_FLASH(PSTR("    KOSZT  3,50zl    "), 4);
			break;
		case 40:
			Write_LCD_String_FLASH(PSTR("     KOSZT  4zl     "), 4);
			break;
		case 45:
			Write_LCD_String_FLASH(PSTR("    KOSZT  4,50zl    "), 4);
			break;
		case 50:
			Write_LCD_String_FLASH(PSTR("     KOSZT  5zl     "), 4);
			break;
		case 55:
			Write_LCD_String_FLASH(PSTR("    KOSZT  5,50zl    "), 4);
			break;
		case 60:
			Write_LCD_String_FLASH(PSTR("     KOSZT  6zl     "), 4);
			break;
		case 65:
			Write_LCD_String_FLASH(PSTR("    KOSZT  6,50zl    "), 4);
			break;
		case 70:
			Write_LCD_String_FLASH(PSTR("     KOSZT  7zl     "), 4);
			break;
		case 75:
			Write_LCD_String_FLASH(PSTR("    KOSZT  7,50zl    "), 4);
			break;
		case 80:
			Write_LCD_String_FLASH(PSTR("     KOSZT  8zl     "), 4);
			break;
		case 85:
			Write_LCD_String_FLASH(PSTR("    KOSZT  8,50zl    "), 4);
			break;
		case 90:
			Write_LCD_String_FLASH(PSTR("     KOSZT  9zl     "), 4);
			break;
		case 95:
			Write_LCD_String_FLASH(PSTR("    KOSZT  9,50zl    "), 4);
			break;
		case 100:
			Write_LCD_String_FLASH(PSTR("     KOSZT  10zl    "), 4);
			break;
		}

		break;
	case 3:
		Time_Disp++;
		if (Time_Disp <= 5) {
			Write_LCD_String_FLASH(PSTR("                    "), 2);
			Write_LCD_String_FLASH(PSTR("  MONET 5zl  : "), 2);
			convert_m(Money_5zl_Atmega);
			Write_LCD_String_FLASH(PSTR("                    "), 3);
			Write_LCD_String_FLASH(PSTR("  MONET 1zl  : "), 3);
			convert_m(Money_1zl_Atmega);
			Write_LCD_String_FLASH(PSTR("                    "), 4);
			Write_LCD_String_FLASH(PSTR("  MONET 50gr : "), 4);
			convert_m(Money_50gr_Atmega);
		}
		if (Time_Disp > 5 && Time_Disp <= 10) {
			if (Hopper_One_Opto == 0) {
				Write_LCD_String_FLASH(PSTR("                    "), 2);
				Write_LCD_String_FLASH(PSTR("  MONET 5zl  : FULL "), 2);
			}

			if (Hopper_Two_Opto == 0) {
				Write_LCD_String_FLASH(PSTR("                    "), 3);
				Write_LCD_String_FLASH(PSTR("  MONET 1zl  : FULL "), 3);
			}

			if (Hopper_Three_Opto == 0) {
				Write_LCD_String_FLASH(PSTR("                    "), 4);
				Write_LCD_String_FLASH(PSTR("  MONET 50gr : FULL "), 4);
			}

		}

		if (Time_Disp > 10) {
			Time_Disp = 0;
		}

		break;
	case 4:

		tmp_money_In = Money_In_Automat;
		tmp_money_koszt = Expense_Atmega;
		tmp_money_Brak = Expense_Atmega - Money_In_Automat;

		LSWprowadzono = 0;
		PSWprowadzono = 0;
		LSBrakuje = 0;
		PSBrakuje = 0;


		Tmp_time_while = 0;

		while (true) {
			Tmp_time_while++;

			if (tmp_money_In >= 10) {
				tmp_money_In -= 10;
				LSWprowadzono++;
				Tmp_time_while = 0;
			}
			if ((tmp_money_In > 0) && tmp_money_In < 10) {
				tmp_money_In--;
				PSWprowadzono++;
				Tmp_time_while = 0;
			}
			if (tmp_money_Brak >= 10) {
				tmp_money_Brak -= 10;
				LSBrakuje++;
				Tmp_time_while = 0;
			}

			if ((tmp_money_Brak > 0) && tmp_money_Brak < 10) {
				tmp_money_Brak--;
				PSBrakuje++;
				Tmp_time_while = 0;
			}

			if ((tmp_money_Brak == 0) && (tmp_money_In == 0)) {
				Tmp_time_while = 0;
				break;
			}

			if (Tmp_time_while >= 64000) {

				LSWprowadzono = 0;
				PSWprowadzono = 0;
				LSBrakuje = 0;
				PSBrakuje = 0;
				Tmp_time_while = 0;
				break;
			}
		}

		Write_LCD_String_FLASH(PSTR("     WPROWADZONO    "), 1);
		Write_LCD_String_FLASH(PSTR("     "), 2);
		convert_m(LSWprowadzono);

		LCD_WriteText_FLASH(PSTR(" zl   "));
		convert_m(PSWprowadzono * 10);

		LCD_WriteText_FLASH(PSTR(" gr    "));
		Write_LCD_String_FLASH(PSTR("       BRAKUJE      "), 3);
		Write_LCD_String_FLASH(PSTR("     "), 4);

		if (LSBrakuje) {
			convert_m(LSBrakuje);
			LCD_WriteText_FLASH(PSTR(" zl   "));
			convert_m(PSBrakuje * 10);
			LCD_WriteText_FLASH(PSTR(" gr    "));
		} else {
			Write_LCD_String_FLASH(PSTR("        "), 4);
			convert_m(PSBrakuje * 10);
			LCD_WriteText_FLASH(PSTR(" gr        "));
		}

		break;

	case 5:
		Write_LCD_String_FLASH(PSTR("     CENA USLUGI    "), 1);
		Write_LCD_String_FLASH(PSTR("                    "), 2);
		Write_LCD_String_FLASH(PSTR("                    "), 3);
		Write_LCD_String_FLASH(PSTR("       "), 3);
		convert_m(Expense_Atmega * 10);
		LCD_WriteText_FLASH(PSTR(" gr "));
		Write_LCD_String_FLASH(PSTR("                    "), 4);
		break;

	case 6:
		Write_LCD_String_FLASH(PSTR(" AUTOMAT ZABLOKOWANY"), 1);
		Write_LCD_String_FLASH(PSTR("  POWIADOM OBSLUGE  "), 2);
		Write_LCD_String_FLASH(PSTR("                    "), 3);
		Write_LCD_String_FLASH(PSTR("     BRAK MONET     "), 4);
		break;

	case 7:
		Write_LCD_String_FLASH(PSTR("    WYBIERZ DRZWI   "), 1);
		Write_LCD_String_FLASH(PSTR("     DO OTWARCIA    "), 2);
		Write_LCD_String_FLASH(PSTR("                    "), 3);
		Write_LCD_String_FLASH(PSTR(" 1        2       3 "), 4);
		break;

	case 8:
		Write_LCD_String_FLASH(PSTR("       OTWARTO      "), 1);
		Write_LCD_String_FLASH(PSTR("        DRZWI       "), 2);
		Write_LCD_String_FLASH(PSTR("                    "), 3);
		Write_LCD_String_FLASH(PSTR("[1]       2       3 "), 4);
		break;

	case 9:
		Write_LCD_String_FLASH(PSTR("       OTWARTO      "), 1);
		Write_LCD_String_FLASH(PSTR("        DRZWI       "), 2);
		Write_LCD_String_FLASH(PSTR("                    "), 3);
		Write_LCD_String_FLASH(PSTR(" 1       [2]      3 "), 4);
		break;
	case 10:
		Write_LCD_String_FLASH(PSTR("       OTWARTO      "), 1);
		Write_LCD_String_FLASH(PSTR("        DRZWI       "), 2);
		Write_LCD_String_FLASH(PSTR("                    "), 3);
		Write_LCD_String_FLASH(PSTR(" 1        2      [3]"), 4);

		break;

	case 11:
		Write_LCD_String_FLASH(PSTR(" AUTOMAT ZABLOKOWANY"), 1);
		Write_LCD_String_FLASH(PSTR("  POWIADOM OBSLUGE  "), 2);
		Write_LCD_String_FLASH(PSTR("                    "), 3);
		Write_LCD_String_FLASH(PSTR("     BRAK MONET     "), 4);
		break;

	case 12:

		LSWprowadzono = 0;
		PSWprowadzono = 0;
		LSBrakuje = 0;
		PSBrakuje = 0;

		uint16_t tmp_Last_Money_In = Last_Money_In;
		uint16_t tmp_Last_Transaction_Atmega = Last_Transaction_Atmega;

		while (true) {
			Tmp_time_while++;
			if (tmp_Last_Money_In >= 10) {
				tmp_Last_Money_In -= 10;
				LSWprowadzono++;
				Tmp_time_while = 0;
			}
			if ((tmp_Last_Money_In > 0) && tmp_Last_Money_In < 10) {
				tmp_Last_Money_In--;
				PSWprowadzono++;
				Tmp_time_while = 0;
			}
			if (tmp_Last_Transaction_Atmega >= 10) {
				tmp_Last_Transaction_Atmega -= 10;
				LSBrakuje++;
				Tmp_time_while = 0;
			}

			if ((tmp_Last_Transaction_Atmega > 0)
					&& tmp_Last_Transaction_Atmega < 10) {
				tmp_Last_Transaction_Atmega--;
				PSBrakuje++;
				Tmp_time_while = 0;
			}

			if ((tmp_Last_Transaction_Atmega == 0)
					&& (tmp_Last_Money_In == 0)) {
				Tmp_time_while = 0;
				break;
			}

			if (Tmp_time_while >= 64000) {

				LSWprowadzono = 0;
				PSWprowadzono = 0;
				LSBrakuje = 0;
				PSBrakuje = 0;
				Tmp_time_while = 0;
				break;
			}
		}

		Write_LCD_String_FLASH(PSTR("      WPLACONO      "), 1);
		Write_LCD_String_FLASH(PSTR("     "), 2);
		convert_m(LSWprowadzono);
		LCD_WriteText_FLASH(PSTR(" zl   "));
		convert_m(PSWprowadzono * 10);

		LCD_WriteText_FLASH(PSTR(" gr    "));
		Write_LCD_String_FLASH(PSTR("     POZOSTALO      "), 3);
		Write_LCD_String_FLASH(PSTR("     "), 4);

		convert_m(LSBrakuje);
		LCD_WriteText_FLASH(PSTR(" zl   "));
		convert_m(PSBrakuje * 10);
		LCD_WriteText_FLASH(PSTR(" gr    "));
		break;

	case 13:
		Write_LCD_String_FLASH(PSTR(" AUTOMAT ZABLOKOWANY"), 1);
		Write_LCD_String_FLASH(PSTR("  POWIADOM OBSLUGE  "), 2);
		Write_LCD_String_FLASH(PSTR("                    "), 3);
		Write_LCD_String_FLASH(PSTR("  BLAD KOMUNIKACJI  "), 4);
		break;

	case 14:

		LSWprowadzono = 0;
		PSWprowadzono = 0;
		LSBrakuje = 0;
		PSBrakuje = 0;
		Tmp_time_while = 0;
		uint16_t tmp_Money_In_Automat = Money_In_Automat, tmp_Money_out =
				Money_In_Automat - Expense_Atmega;

		while (true) {
			Tmp_time_while++;
			if (tmp_Money_In_Automat >= 10) {
				tmp_Money_In_Automat -= 10;
				LSWprowadzono++;
				Tmp_time_while = 0;
			}
			if ((tmp_Money_In_Automat > 0) && tmp_Money_In_Automat < 10) {
				tmp_Money_In_Automat--;
				PSWprowadzono++;
				Tmp_time_while = 0;
			}
			if (tmp_Money_out >= 10) {
				tmp_Money_out -= 10;
				LSBrakuje++;
				Tmp_time_while = 0;
			}

			if ((tmp_Money_out > 0) && tmp_Money_out < 10) {
				tmp_Money_out--;
				PSBrakuje++;
				Tmp_time_while = 0;
			}

			if ((tmp_Money_out == 0) && (tmp_Money_In_Automat == 0)) {
				Tmp_time_while = 0;
				break;
			}
			if (Tmp_time_while >= 64000) {
				LSWprowadzono = 0;
				PSWprowadzono = 0;
				LSBrakuje = 0;
				PSBrakuje = 0;
				Tmp_time_while = 0;
				break;
			}

		}

		if(PSBrakuje % 5)
		{
			PSBrakuje = 0;
		}

		Write_LCD_String_FLASH(PSTR("      WPLACONO      "), 1);
		Write_LCD_String_FLASH(PSTR("     "), 2);
		convert_m(LSWprowadzono);
		LCD_WriteText_FLASH(PSTR(" zl   "));
		convert_m(PSWprowadzono * 10);
		LCD_WriteText_FLASH(PSTR(" gr    "));
		Write_LCD_String_FLASH(PSTR("       RESZTA       "), 3);
		Write_LCD_String_FLASH(PSTR("     "), 4);

		convert_m(LSBrakuje);
		LCD_WriteText_FLASH(PSTR(" zl   "));
		convert_m(PSBrakuje * 10);
		LCD_WriteText_FLASH(PSTR(" gr    "));
		break;

	case 15:
		Write_LCD_String_FLASH(PSTR("   AUTOMAT WYDAJE   "), 1);
		Write_LCD_String_FLASH(PSTR("       MONETY       "), 2);
		Write_LCD_String_FLASH(PSTR("    5zl      1zl    "), 3);
		Write_LCD_String_FLASH(PSTR("        50gr        "), 4);
		break;

	}
}

void Write_LCD_String_FLASH(const char * text, uint8_t pos) {
	LCD_GoTo(pos - 1);
	LCD_WriteText_FLASH(text);
}

void Write_LCD_String_RAM(char * text, uint8_t pos) {
	LCD_GoTo(pos - 1);
	LCD_WriteText_RAM(text);
}

void convert_m(uint16_t m) {
	char str[10];
	utoa(m, str, 10);
	LCD_WriteText_RAM(str);
}
