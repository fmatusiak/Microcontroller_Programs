/*
 * LCD.c
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#include "main.h"


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
		Write_LCD_String("   OBSLUGI KLIENTA  ",2);
		Write_LCD_String("       WPROWADZ     ",3);
		Write_LCD_String(" MONETY LUB BANKNOT ",4);

		break;
	case 3:

		Write_LCD_String(" AUTOMAT PRZYJMUJE  ",1);
		Write_LCD_String("   10zl 20zl 50zl   ",2);
		Write_LCD_String("  50gr 1zl 2zl 5zl  ",3);
		Write_LCD_String("   KOSZT  ",4);
		convert_m(Expense);
		break;
	case 4:
		LCD_Clear();
		Write_LCD_String(" WPROWADZONO ",1);
		convert_m(Money_In_Automat);
		LCD_WriteText(",");
		LCD_WriteText("zl");
		LCD_WriteText(" BRAKUJE ");
		//convert_m(out5e_cal);
		LCD_WriteText(",");
	//	convert_m(out5e_cal);
		LCD_WriteText("zl");
		Write_LCD_String("    WYBIERZ DRZWI   ",3);

		Write_LCD_String("1         2        3",4);

		break;
	case 81:
//		LCD_Clear();
//		LCD_WriteText(" WPROWADZONO ");
//	//	convert_m(out5e_cal);
//		LCD_WriteText(",");
//	//	convert_m(out5e_cal);
//		LCD_WriteText("zl");
//		LCD_GoTo(0, 1);
//
//		LCD_WriteText(" BRAKUJE ");
//	//	convert_m(out5e_cal);
//		LCD_WriteText(",");
//	//	convert_m(out5e_cal);
//		LCD_WriteText("zl");
//		LCD_GoTo(0, 2);
//		LCD_WriteText("    WYBIERZ DRZWI   ");
//		LCD_GoTo(0, 3);
//		LCD_WriteText("[1]        2       3");
		break;
	case 5:
//		LCD_Clear();
//		LCD_WriteText(" WPROWADZONO ");
//	//	convert_m(out5e_cal);
//		LCD_WriteText(",");
//		//convert_m(out5e_cal);
//		LCD_WriteText("zl");
//		LCD_GoTo(0, 1);
//
//		LCD_WriteText(" BRAKUJE ");
//		//convert_m(out5e_cal);
//		LCD_WriteText(",");
//	//	convert_m(out5e_cal);
//		LCD_WriteText("zl");
//		LCD_GoTo(0, 2);
//		LCD_WriteText("    WYBIERZ DRZWI   ");
//		LCD_GoTo(0, 3);
//		LCD_WriteText("1        [2]       3");
		break;

	case 6:
//		LCD_Clear();
//		LCD_WriteText(" WPROWADZONO ");
//	//	convert_m(out5e_cal);
//		LCD_WriteText(",");
//		//convert_m(out5e_cal);
//		LCD_WriteText("zl");
//		LCD_GoTo(0, 1);
//
//		LCD_WriteText(" BRAKUJE ");
//		//convert_m(out5e_cal);
//		LCD_WriteText(",");
//		//convert_m(out5e_cal);
//		LCD_WriteText("zl");
//		LCD_GoTo(0, 2);
//		LCD_WriteText("    WYBIERZ DRZWI   ");
//		LCD_GoTo(0, 3);
//		LCD_WriteText("1        2       [3]");
		break;
	case 7:
//		LCD_Clear();
//		LCD_WriteText("        DUMP        ");
//		LCD_GoTo(1);
//		LCD_WriteText("   WYBIERZ HOPPER   ");
//		LCD_GoTo(3);
//		LCD_WriteText("[1]        2       3");
		break;

	case 8:
//		LCD_Clear();
//		LCD_WriteText("      DUMP       ");
//		LCD_GoTo(1);
//		LCD_WriteText("   HOPPER 1 zl   ");
		break;


	}
}

void Write_LCD_String(char * text, uint8_t pos) {
	LCD_GoTo(pos - 1);
	LCD_WriteText(text);
}

void  convert_m(uint16_t m) {
	char str[10];

	utoa(m, str, 10);
	LCD_WriteText(str);
}
