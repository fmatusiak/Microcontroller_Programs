///*
// * Hopper.c
// *
// *  Created on: 4 lip 2017
// *      Author: dell
// */
//
//#include "Hopper.h"
//
//void Check_Hopper(void) {
//	uint8_t datarecive[20] = { 0 };
//	Write_LCD_String_FLASH(PSTR("       HOPPER       "), 3);
//	Write_LCD_String_FLASH(PSTR("                    "), 4);
//	_delay_ms(1000);
//
//	ccTalk_send(HOPPER_5ZL, 0, 242, 0);
//	if (ccTalk_recive(datarecive, HOPPER_5ZL)) {
//
//		if (((*(datarecive + 4)) == HOPPER5ID_NUMBER_1)
//				&& ((*(datarecive + 5)) == HOPPER5ID_NUMBER_2)
//				&& ((*(datarecive + 6)) == HOPPER5ID_NUMBER_3)) {
//			Write_LCD_String_FLASH(PSTR("    HOPPER 1 OK     "), 4);
//			_delay_ms(1000);
//		} else {
//			Write_LCD_String_FLASH(PSTR("   HOPPER 1 FAIL   "), 4);
//			while (1) {
//				Write_LCD_String_FLASH(PSTR("       HOPPER       "), 3);
//				Write_LCD_String_FLASH(PSTR("   HOPPER 1 FAIL   "), 4);
//				_delay_ms(1500);
//				Write_LCD_String_FLASH(PSTR("                   "), 3);
//				Write_LCD_String_FLASH(PSTR("  "), 3);
//				convert_m(*(datarecive + 4));
//				LCD_WriteText_FLASH(PSTR(" : "));
//				convert_m(*(datarecive + 5));
//				LCD_WriteText_FLASH(PSTR(" : "));
//				convert_m(*(datarecive + 6));
//				LCD_WriteText_FLASH(PSTR(" : "));
//				_delay_ms(1500);
//
//			}
//		}
//	} else {
//		Write_LCD_String_FLASH(PSTR("   HOPPER 1 ERROR   "), 4);
//		while (1) {
//		}
//	}
//	ccTalk_send(HOPPER_1ZL, 0, 242, 0);
//	if (ccTalk_recive(datarecive, HOPPER_1ZL)) {
//
//		if (((*(datarecive + 4)) == HOPPER1ID_NUMBER_1)
//				&& ((*(datarecive + 5)) == HOPPER1ID_NUMBER_2)
//				&& ((*(datarecive + 6)) == HOPPER1ID_NUMBER_3)) {
//			Write_LCD_String_FLASH(PSTR("    HOPPER 2 OK     "), 4);
//			_delay_ms(1000);
//		} else {
//			Write_LCD_String_FLASH(PSTR("   HOPPER 2 FAIL   "), 4);
//			while (1) {
//				Write_LCD_String_FLASH(PSTR("       HOPPER       "), 3);
//				Write_LCD_String_FLASH(PSTR("   HOPPER 2 FAIL   "), 4);
//				_delay_ms(1500);
//				Write_LCD_String_FLASH(PSTR("                   "), 3);
//				Write_LCD_String_FLASH(PSTR("  "), 3);
//				convert_m(*(datarecive + 4));
//				LCD_WriteText_FLASH(PSTR(" : "));
//				convert_m(*(datarecive + 5));
//				LCD_WriteText_FLASH(PSTR(" : "));
//				convert_m(*(datarecive + 6));
//				LCD_WriteText_FLASH(PSTR(" : "));
//				_delay_ms(1500);
//
//			}
//		}
//	} else {
//		Write_LCD_String_FLASH(PSTR("   HOPPER 2 ERROR   "), 4);
//		while (1) {
//		}
//	}
//	ccTalk_send(HOPPER_50GR, 0, 242, 0);
//	if (ccTalk_recive(datarecive, HOPPER_50GR)) {
//
//		if (((*(datarecive + 4)) == HOPPER50ID_NUMBER_1)
//				&& ((*(datarecive + 5)) == HOPPER50ID_NUMBER_2)
//				&& ((*(datarecive + 6)) == HOPPER50ID_NUMBER_3)) {
//			Write_LCD_String_FLASH(PSTR("    HOPPER 3 OK     "), 4);
//			_delay_ms(1000);
//		} else {
//			Write_LCD_String_FLASH(PSTR("   HOPPER 3 FAIL   "), 4);
//			while (1) {
//				Write_LCD_String_FLASH(PSTR("       HOPPER       "), 3);
//				Write_LCD_String_FLASH(PSTR("   HOPPER 3 FAIL   "), 4);
//				_delay_ms(1500);
//				Write_LCD_String_FLASH(PSTR("                   "), 3);
//				Write_LCD_String_FLASH(PSTR("  "), 3);
//				convert_m(*(datarecive + 4));
//				LCD_WriteText_FLASH(PSTR(" : "));
//				convert_m(*(datarecive + 5));
//				LCD_WriteText_FLASH(PSTR(" : "));
//				convert_m(*(datarecive + 6));
//				LCD_WriteText_FLASH(PSTR(" : "));
//				_delay_ms(1500);
//
//			}
//		}
//	} else {
//		Write_LCD_String_FLASH(PSTR("   HOPPER 3 ERROR   "), 4);
//		while (1) {
//		}
//	}
//
//}
//
//uint8_t Hopper_STOPPayOut(uint8_t Hopper) {
//	_delay_ms(10);
//	uint8_t datarecive[20] = { 0 };
//	ccTalk_send(Hopper, 0, 172, (uint8_t[] ) { 0 });
//	if (ccTalk_recive_no_timeout(datarecive, Hopper)) {
//		return datarecive[4];
//	} else
//		return 0;
//
//}
//
//uint8_t Hopper_LastPayOut(uint8_t Hopper) {
//	_delay_ms(10);
//	uint8_t datarecive[20] = { 0 };
//	ccTalk_send(Hopper, 0, 166, (uint8_t[] ) { 0 });
//	if (ccTalk_recive_no_timeout(datarecive, Hopper)) {
//		return datarecive[5];
//	} else
//		return 0;
//
//}
//
//void Hopper_PayOut(uint8_t Count, uint8_t Hopper) {
//
//	if (Count) {
//		uint8_t Data1, Data2, Data3;
//		uint8_t datarecive[20] = { 0 };
//		_delay_ms(10);
//		ccTalk_send(Hopper, 1, 164, (uint8_t[] ) { 165 });
//		_delay_ms(50);
//		ccTalk_send(Hopper, 0, 242, (uint8_t[] ) { 0 });
//		if (ccTalk_recive(datarecive, Hopper)) {
//			Data1 = datarecive[4];
//			Data2 = datarecive[5];
//			Data3 = datarecive[6];
//
//			ccTalk_send(Hopper, 4, 167, (uint8_t[] ) { Data1, Data2, Data3,
//							Count });
//			_delay_ms(40);
//		}
//	}
//}
//
//uint8_t Check_Hopper_Opto(uint8_t Hopper) {
//	uint8_t datarecive[20] = { 0 };
//
//	ccTalk_send(Hopper, 0, 236, (uint8_t[] ) { 0 });
//	if (ccTalk_recive(datarecive, Hopper)) {
//		return datarecive[4];
//	} else {
//		return 3;
//	}
//
//}
//
//void Set_Hopper_Opto(void) {
//	Hopper_One_Opto = Check_Hopper_Opto(HOPPER_5ZL);
//	Hopper_Two_Opto = Check_Hopper_Opto(HOPPER_1ZL);
//	Hopper_Three_Opto = Check_Hopper_Opto(HOPPER_50GR);
//}
//
//void Set_Expense_Hopper(void) {
//	if (Hopper_Three_Opto == 3) {
//		if ((Expense_Atmega % 2) == 1) {
//			Expense_Atmega += 5;
//			FL_Cena_UP = 1;
//		}
//		Inhibit_Coin = 248;
//	}
//
//	else {
//		Inhibit_Coin = 252;
//
//		if (FL_Cena_UP) {
//			Expense_Atmega -= 5;
//			FL_Cena_UP = 0;
//		}
//	}
//
//	if ((Hopper_Two_Opto == 3) && (Hopper_Three_Opto == 3)) {
//		FL_Blocked = 1;
//	}
//
//}
//
//void PayOut(void) {
//	uint16_t Money, tmpMoney;
//	uint8_t rng;
//
//	uint8_t Count_5zl, Count_1zl, Count_50gr;
//	uint8_t tmp_Count_5zl, tmp_Count_1zl, tmp_Count_50gr, tmpFor;
//
//	Money = Money_In_Automat - Expense_Atmega;
//
//	tmp_Count_5zl = 0;
//	tmp_Count_1zl = 0;
//	tmp_Count_50gr = 0;
//
//	tmp_Count_5zl = (Money - (Money % 50)) / 50;
//
//	tmp_Count_1zl = (Money - (Money % 10)) / 10;
//	tmp_Count_1zl -= (tmp_Count_5zl * 5);
//
//	tmp_Count_50gr = Money / 5;
//	tmp_Count_50gr -= (tmp_Count_5zl * 10);
//	tmp_Count_50gr -= (tmp_Count_1zl * 2);
//
//	if (Hopper_One_Opto == 3) {
//
//		if (Hopper_Two_Opto == 3) {
//			tmp_Count_50gr += tmp_Count_5zl * 10;
//			tmp_Count_5zl = 0;
//		}
//		if (Hopper_Three_Opto == 3) {
//			tmp_Count_1zl += tmp_Count_5zl * 5;
//			tmp_Count_5zl = 0;
//		}
//	}
//
//	if (Hopper_Two_Opto == 3) {
//		tmp_Count_50gr += tmp_Count_1zl * 2;
//		tmp_Count_1zl = 0;
//
//	}
//
//	if (Hopper_Three_Opto == 3) {
//		if ((tmp_Count_50gr % 2) == 0) {
//			tmp_Count_1zl += tmp_Count_50gr * 2;
//			tmp_Count_50gr = 0;
//		} else {
//			tmp_Count_50gr -= 5;
//			tmp_Count_1zl += tmp_Count_50gr * 2;
//			tmp_Count_50gr = 0;
//		}
//
//	}
//	Count_5zl = tmp_Count_5zl;
//	Count_1zl = tmp_Count_1zl;
//	Count_50gr = tmp_Count_50gr;
//
//	if ((Hopper_One_Opto != 3) && (Hopper_Two_Opto != 3)
//			&& (Hopper_Three_Opto != 3)) {
//
//		tmpFor = tmp_Count_5zl;
//		for (uint8_t i = 0; i < tmpFor; i++) {
//			rng = RNG();
//
//			if (((rng >= 0) && (rng <= 25)) || ((rng > 175) && (rng <= 200))) {
//				Count_1zl += 5;
//				Count_5zl -= 1;
//			} // x % szans
//
//		}
//
//		tmpFor = Count_1zl;
//		for (uint8_t i = 0; i < tmpFor; i++) {
//			rng = RNG();
//
//			if (((rng >= 0) && (rng <= 20)) || ((rng > 180) && (rng <= 200))) {
//				Count_1zl--;
//				Count_50gr += 2;
//			} //35%szans
//
//		}
//
//		tmpMoney = (Count_50gr * 5) + (Count_1zl * 10) + (Count_5zl * 50);
//		if (tmpMoney == Money) {
//			Hopper_PayOut(Count_5zl, HOPPER_5ZL);
//			Hopper_PayOut(Count_1zl, HOPPER_1ZL);
//			Hopper_PayOut(Count_50gr, HOPPER_50GR);
//
//			Chcek_Hopper_Last_PayOut(Count_5zl, Count_1zl, Count_50gr);
//			IO_Combo_Clear_Escrow();
//		}
//
//		else {
//			Hopper_PayOut(tmp_Count_5zl, HOPPER_5ZL);
//			Hopper_PayOut(tmp_Count_1zl, HOPPER_1ZL);
//			Hopper_PayOut(tmp_Count_50gr, HOPPER_50GR);
//
//			Chcek_Hopper_Last_PayOut(tmp_Count_5zl, tmp_Count_1zl,
//					tmp_Count_50gr);
//			IO_Combo_Clear_Escrow();
//		}
//	}
//
//	else {
//		Hopper_PayOut(Count_5zl, HOPPER_5ZL);
//		Hopper_PayOut(Count_1zl, HOPPER_1ZL);
//		Hopper_PayOut(Count_50gr, HOPPER_50GR);
//
//		Chcek_Hopper_Last_PayOut(Count_5zl, Count_1zl, Count_50gr);
//		IO_Combo_Clear_Escrow();
//	}
//
//}
//
//void Chcek_Hopper_Last_PayOut(uint8_t Count_1, uint8_t Count_2, uint8_t Count_3) {
//	uint8_t Stan_Hopper_1 = 0, Stan_Hopper_2 = 0, Stan_Hopper_3 = 0;
//	uint16_t money_automat_payout = 0;
//	uint8_t Tmp_time = 0, tmp_stan = 0;
//	money_automat_payout = (Count_1 *50) + (Count_1 * 10) + (Count_1 * 5);
//	Check_inhbit();
//
//	if (Count_1) {
//
//		Stan_Hopper = Hopper_LastPayOut(HOPPER_5ZL);
//		while (Stan_Hopper) {
//			Stan_Hopper = Hopper_LastPayOut(HOPPER_5ZL);
//			if (tmp_stan != Stan_Hopper) {
//				tmp_stan = Stan_Hopper;
//				Tmp_time = 0;
//			}
//			Tmp_time++;
//			Check_inhbit();
//			if (Tmp_time >= 40) {
//				_delay_ms(50);
//				Stan_Hopper_1 = Hopper_STOPPayOut(HOPPER_5ZL);
//				Count_1 -= Stan_Hopper_1;
//				break;
//			}
//		}
//	}_delay_ms(50);
//
//	if (Count_2) {
//		tmp_stan = Tmp_time = 0;
//		Stan_Hopper = Hopper_LastPayOut(HOPPER_1ZL);
//		while (Stan_Hopper) {
//			Stan_Hopper = Hopper_LastPayOut(HOPPER_1ZL);
//			if (tmp_stan != Stan_Hopper) {
//				tmp_stan = Stan_Hopper;
//				Tmp_time = 0;
//			}
//			Tmp_time++;
//			Check_inhbit();
//			if (Tmp_time >= 15) {
//				_delay_ms(50);
//				Stan_Hopper_2 = Hopper_STOPPayOut(HOPPER_1ZL);
//				Count_2 -= Stan_Hopper_2;
//				break;
//			}
//		}
//	}
//	_delay_ms(50);
//	if (Count_3) {
//		tmp_stan = Tmp_time = 0;
//
//		Stan_Hopper = Hopper_LastPayOut(HOPPER_50GR);
//		while (Stan_Hopper) {
//			Stan_Hopper = Hopper_LastPayOut(HOPPER_50GR);
//			if (tmp_stan != Stan_Hopper) {
//				tmp_stan = Stan_Hopper;
//				Tmp_time = 0;
//			}
//			Tmp_time++;
//			Check_inhbit();
//			if (Tmp_time >= 15) {
//				_delay_ms(50);
//				Stan_Hopper_3 = Hopper_STOPPayOut(HOPPER_50GR);
//				Count_3 -= Stan_Hopper_3;
//				break;
//			}
//		}
//	}
//
//	if ((Stan_Hopper_1 == 0) && (Stan_Hopper_2 == 0) && (Stan_Hopper_3 == 0)) {
//
//	} else {
//
//		if ((Stan_Hopper_1) && (Stan_Hopper_2 == 0)) {
//			//if (Hopper_Two_Opto != 3) {
//
//				tmp_stan = Tmp_time = 0;
//				Count_2 += Stan_Hopper_1 * 5;
//				Hopper_PayOut(Stan_Hopper_1 * 5, HOPPER_1ZL);
//				Stan_Hopper_1 = 0;
//
//				Stan_Hopper = Hopper_LastPayOut(HOPPER_1ZL);
//				while (Stan_Hopper) {
//					Stan_Hopper = Hopper_LastPayOut(HOPPER_1ZL);
//
//					if (tmp_stan != Stan_Hopper) {
//						tmp_stan = Stan_Hopper;
//						Tmp_time = 0;
//					}
//
//					Tmp_time++;
//					Check_inhbit();
//					if (Tmp_time >= 50) {
//						_delay_ms(50);
//						Stan_Hopper_2 += Hopper_STOPPayOut(HOPPER_1ZL);
//						Count_2 -= Stan_Hopper_2;
//						break;
//					}
//				}
//			//}
//
//		}
//		_delay_ms(50);
//		if ((Stan_Hopper_1) && (Stan_Hopper_3 == 0)) {
//			//if (Hopper_Three_Opto != 3) {
//				tmp_stan = Tmp_time = 0;
//				Stan_Hopper_1 = 0;
//				Count_3 += Stan_Hopper_1 * 10;
//				Hopper_PayOut(Stan_Hopper_1 * 10, HOPPER_50GR);
//
//				Stan_Hopper = Hopper_LastPayOut(HOPPER_50GR);
//				while (Stan_Hopper) {
//					Stan_Hopper = Hopper_LastPayOut(HOPPER_50GR);
//
//					if (tmp_stan != Stan_Hopper) {
//						tmp_stan = Stan_Hopper;
//						Tmp_time = 0;
//					}
//
//					Tmp_time++;
//					Check_inhbit();
//					if (Tmp_time >= 50) {
//						_delay_ms(50);
//						Stan_Hopper_3 += Hopper_STOPPayOut(HOPPER_50GR);
//						Count_3 -= Stan_Hopper_3;
//						break;
//					}
//				}
//			//}
//
//		}
//		_delay_ms(50);
//		if ((Stan_Hopper_2) && (Stan_Hopper_3 == 0)) {
//			//if (Hopper_Three_Opto != 3) {
//				tmp_stan = Tmp_time = 0;
//
//				Stan_Hopper_2 = 0;
//				Count_3 += Stan_Hopper_2 * 2;
//				Hopper_PayOut(Stan_Hopper_2 * 2, HOPPER_50GR);
//
//				Stan_Hopper = Hopper_LastPayOut(HOPPER_50GR);
//				while (Stan_Hopper) {
//					Stan_Hopper = Hopper_LastPayOut(HOPPER_50GR);
//
//					if (tmp_stan != Stan_Hopper) {
//						tmp_stan = Stan_Hopper;
//						Tmp_time = 0;
//					}
//					Tmp_time++;
//					Check_inhbit();
//					if (Tmp_time >= 50) {
//						_delay_ms(50);
//						Stan_Hopper_3 += Hopper_STOPPayOut(HOPPER_50GR);
//						Count_3 -= Stan_Hopper_3;
//						break;
//					}
//				}
//			//}
//		}
//		_delay_ms(50);
//		Last_Transaction_Atmega = (Stan_Hopper_1 * 50) + (Stan_Hopper_2 * 10)
//				+ (Stan_Hopper_3 * 5);
//
//		if (Last_Transaction_Atmega) {
//			FL_ERROR = 1;
//			Last_Money_In = Money_In_Automat;
//		}
//
//	}
//
//	if (Count_1 < Money_5zl_Atmega) {
//		Money_5zl_Atmega -= Count_1;
//	} else {
//		Money_5zl_Atmega = 0;
//	}
//
//	if (Count_2 < Money_1zl_Atmega) {
//		Money_1zl_Atmega -= Count_2;
//	} else {
//		Money_1zl_Atmega = 0;
//	}
//
//	if (Count_3 < Money_50gr_Atmega) {
//		Money_50gr_Atmega -= Count_3;
//	} else {
//		Money_50gr_Atmega = 0;
//	}
//
//	Save_Money_Hopper();
//	Money_In_Automat = 0;
//	FL_WPBlock = false;
//}
//
//void Dumpowanie(void) {
//	if ((checkPin(PIN_BUTTON_1_IN)) && FL_Button_1) {
//		_delay_ms(50);
//		Hopper_Dump(1);
//	}
//
//	if ((FL_Button_1 == 0) && (!(checkPin(PIN_BUTTON_1_IN)))) {
//		FL_Button_1 = 1;
//	}
//
//	if ((checkPin(PIN_BUTTON_2_IN)) && FL_Button_2) {
//		_delay_ms(50);
//		Hopper_Dump(2);
//	}
//
//	if ((FL_Button_2 == 0) && (!(checkPin(PIN_BUTTON_2_IN)))) {
//		FL_Button_2 = 1;
//	}
//
//	if ((checkPin(PIN_BUTTON_3_IN)) && FL_Button_3) {
//		_delay_ms(50);
//		Hopper_Dump(3);
//	}
//
//	if ((FL_Button_3 == 0) && (!(checkPin(PIN_BUTTON_3_IN)))) {
//		FL_Button_3 = 1;
//	}
//}
//
//void Hopper_Dump(uint8_t Hopper) {
//	if (Hopper == 1) {
//		if (Money_5zl_Atmega > 5) {
//			Hopper_PayOut(5, HOPPER_5ZL);
//			Money_5zl_Atmega -= 5;
//		} else {
//			Hopper_PayOut(25, HOPPER_5ZL);
//			Money_5zl_Atmega = 0;
//		}
//	}
//
//	if (Hopper == 2) {
//		if (Money_1zl_Atmega > 5) {
//			Hopper_PayOut(5, HOPPER_1ZL);
//			Money_1zl_Atmega -= 5;
//		} else {
//			Hopper_PayOut(25, HOPPER_1ZL);
//			Money_1zl_Atmega = 0;
//		}
//	}
//
//	if (Hopper == 3) {
//		if (Money_50gr_Atmega > 5) {
//			Hopper_PayOut(5, HOPPER_50GR);
//			Money_50gr_Atmega -= 5;
//		} else {
//			Hopper_PayOut(25, HOPPER_50GR);
//			Money_50gr_Atmega = 0;
//		}
//	}
//
//}
//
/*
 * Hopper.c
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#include "Hopper.h"

void Check_Hopper(void) {
	uint8_t datarecive[20] = { 0 };
	Write_LCD_String_FLASH(PSTR("       HOPPER       "), 3);
	Write_LCD_String_FLASH(PSTR("                    "), 4);
	_delay_ms(1000);

	ccTalk_send(HOPPER_5ZL, 0, 242, 0);
	if (ccTalk_recive(datarecive, HOPPER_5ZL)) {

		if (((*(datarecive + 4)) == HOPPER5ID_NUMBER_1)
				&& ((*(datarecive + 5)) == HOPPER5ID_NUMBER_2)
				&& ((*(datarecive + 6)) == HOPPER5ID_NUMBER_3)) {
			Write_LCD_String_FLASH(PSTR("    HOPPER 1 OK     "), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String_FLASH(PSTR("   HOPPER 1 FAIL   "), 4);
			while (1) {
			}
		}
	} else {
		Write_LCD_String_FLASH(PSTR("   HOPPER 1 ERROR   "), 4);
		while (1) {
		}
	}
	ccTalk_send(HOPPER_1ZL, 0, 242, 0);
	if (ccTalk_recive(datarecive, HOPPER_1ZL)) {

		if (((*(datarecive + 4)) == HOPPER2ID_NUMBER_1)
				&& ((*(datarecive + 5)) == HOPPER2ID_NUMBER_2)
				&& ((*(datarecive + 6)) == HOPPER2ID_NUMBER_3)) {
			Write_LCD_String_FLASH(PSTR("    HOPPER 2 OK     "), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String_FLASH(PSTR("   HOPPER 2 FAIL   "), 4);
			while (1) {

			}
		}
	} else {
		Write_LCD_String_FLASH(PSTR("   HOPPER 2 ERROR   "), 4);
		while (1) {
		}
	}
	ccTalk_send(HOPPER_50GR, 0, 242, 0);
	if (ccTalk_recive(datarecive, HOPPER_50GR)) {

		if (((*(datarecive + 4)) == HOPPER50ID_NUMBER_1)
				&& ((*(datarecive + 5)) == HOPPER50ID_NUMBER_2)
				&& ((*(datarecive + 6)) == HOPPER50ID_NUMBER_3)) {
			Write_LCD_String_FLASH(PSTR("    HOPPER 3 OK     "), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String_FLASH(PSTR("   HOPPER 3 FAIL   "), 4);
			while (1) {

			}
		}
	} else {
		Write_LCD_String_FLASH(PSTR("   HOPPER 3 ERROR   "), 4);
		while (1) {
		}
	}

}

uint8_t Hopper_STOPPayOut(uint8_t Hopper) {
	uint8_t datarecive[20] = { 0 };
	ccTalk_send(Hopper, 0, 172, (uint8_t[] ) { 0 });
	if (ccTalk_recive_no_timeout(datarecive, Hopper)) {
		return datarecive[4];
	} else
		return 0;

}

uint8_t Hopper_LastPayOut(uint8_t Hopper) {
	uint8_t datarecive[20] = { 0 };
	ccTalk_send(Hopper, 0, 166, (uint8_t[] ) { 0 });
	if (ccTalk_recive_no_timeout(datarecive, Hopper)) {
		return datarecive[5];
	} else
		return 0;

}

uint8_t Hopper_PayOut(uint8_t Count, uint8_t Hopper) {
	uint8_t tmp_stan = 0, Tmp_time = 0;
	uint8_t Stan = 0;
	if (Count) {
		uint8_t Data1, Data2, Data3;
		uint8_t datarecive[20] = { 0 };

		ccTalk_send(Hopper, 1, 164, (uint8_t[] ) { 165 });
		_delay_ms(50);
		ccTalk_send(Hopper, 0, 242, (uint8_t[] ) { 0 });
		if (ccTalk_recive(datarecive, Hopper)) {
			Data1 = datarecive[4];
			Data2 = datarecive[5];
			Data3 = datarecive[6];

			ccTalk_send(Hopper, 4, 167, (uint8_t[] ) { Data1, Data2, Data3,
							Count });
			_delay_ms(40);
		}
	}

	if (Count) {

		Stan_Hopper = Hopper_LastPayOut(Hopper);
		while (Stan_Hopper) {
			Stan_Hopper = Hopper_LastPayOut(Hopper);
			if (tmp_stan != Stan_Hopper) {
				tmp_stan = Stan_Hopper;
				Tmp_time = 0;
			}
			Tmp_time++;
			Check_inhbit();
			if (Tmp_time >= 40) {
				Stan = Hopper_STOPPayOut(Hopper);
				break;
			}
		}

		return Stan;
	}
	return 0;

}

uint8_t Check_Hopper_Opto(uint8_t Hopper) {
	uint8_t datarecive[20] = { 0 };

	ccTalk_send(Hopper, 0, 236, (uint8_t[] ) { 0 });
	if (ccTalk_recive_no_timeout(datarecive, Hopper)) {
		return datarecive[4];
	} else {
		return 3;
	}

}

void Set_Hopper_Opto(void) {
	Hopper_One_Opto = Check_Hopper_Opto(HOPPER_5ZL);
	Hopper_Two_Opto = Check_Hopper_Opto(HOPPER_1ZL);
	Hopper_Three_Opto = Check_Hopper_Opto(HOPPER_50GR);
}

void Set_Expense_Hopper(void) {
	if (Hopper_Three_Opto == 3) {
		if ((Expense_Atmega % 2) == 1) {
			Expense_Atmega += 5;
			FL_Cena_UP = 1;
		}
		//Inhibit_Coin = 248;
	}

	else {
		//Inhibit_Coin = 252;

		if (FL_Cena_UP) {
			Expense_Atmega -= 5;
			FL_Cena_UP = 0;
		}
	}

	if ((Hopper_Two_Opto == 3) && (Hopper_Three_Opto == 3)) {
		FL_Blocked = 1;
	}

}

void PayOut(void) {
	uint16_t Money;
	uint8_t rng, tmpFor;
	uint8_t Count_5zl, Count_2zl, Count_50gr;
	uint8_t tmp_Count_5zl, tmp_Count_2zl, tmp_Count_50gr;

	Money = Money_In_Automat - Expense_Atmega;

	tmp_Count_5zl = 0;
	tmp_Count_2zl = 0;
	tmp_Count_50gr = 0;

	tmp_Count_5zl = (Money - (Money % 50)) / 50;

	if (tmp_Count_5zl > 1) {
		if (tmp_Count_5zl % 2 == 0) {
			tmp_Count_2zl = (Money - (Money % 20)) / 20;
			tmp_Count_2zl -= ((tmp_Count_5zl * 5) / 2);
		}

		else {

			tmp_Count_2zl = (Money - (Money % 20)) / 20;
			tmp_Count_2zl -= (((tmp_Count_5zl - 1) * 5) / 2) + 2;
		}

	} else {
		tmp_Count_2zl = (Money - (Money % 20)) / 20;
		tmp_Count_2zl -= (((tmp_Count_5zl - 1) * 5) / 2) + 2;
	}

	tmp_Count_50gr = Money / 5;
	tmp_Count_50gr -= (tmp_Count_5zl * 10);
	tmp_Count_50gr -= (tmp_Count_2zl * 4);

	if (Hopper_One_Opto == 3) {
		if (tmp_Count_5zl > 1) {
			if (tmp_Count_5zl % 2 == 0) {
				tmp_Count_2zl += 2;
				tmp_Count_2zl += ((tmp_Count_5zl * 5) / 2);
				tmp_Count_5zl = 0;
			}

			else {
				tmp_Count_5zl--;
				tmp_Count_50gr += 2;
				tmp_Count_2zl += 2;
				tmp_Count_2zl += ((tmp_Count_5zl * 5) / 2);
				tmp_Count_5zl = 0;
			}

		} else {
			tmp_Count_50gr += 2;
			tmp_Count_2zl += 2;
			tmp_Count_5zl = 0;
		}

	}

	if (Hopper_Two_Opto == 3) {
		tmp_Count_50gr += tmp_Count_2zl * 4;
		tmp_Count_2zl = 0;
	}

	if (Hopper_Three_Opto == 3) {
		if ((tmp_Count_50gr % 4) == 0) {
			tmp_Count_2zl += tmp_Count_50gr * 4;
			tmp_Count_50gr = 0;
		}

	}
	Count_5zl = tmp_Count_5zl;
	Count_2zl = tmp_Count_2zl;
	Count_50gr = tmp_Count_50gr;

	if ((Hopper_One_Opto != 3) && (Hopper_Two_Opto != 3)
			&& (Hopper_Three_Opto != 3)) {

		tmpFor = tmp_Count_5zl;
		for (uint8_t i = 0; i < tmpFor; i++) {
			rng = RNG();

			if (((rng >= 0) && (rng <= 30)) || ((rng > 175) && (rng <= 205))) {
				Count_50gr += 2;
				Count_2zl += 2;
				Count_5zl -= 1;
			} // x % szans

		}
	}
	uint8_t tmp_mon_stan_5 = 0, tmp_mon_stan_1 = 0, tmp_mon_stan_50 = 0;

	tmp_mon_stan_5 = Hopper_PayOut(Count_5zl, HOPPER_5ZL);

	if (tmp_mon_stan_5) {
		if (tmp_mon_stan_5 % 2 == 0) {
			Count_5zl -= tmp_mon_stan_5;
			Count_2zl += (tmp_mon_stan_5 * 5) / 2;
		} else {
			if (tmp_mon_stan_5 > 1) {

				Count_5zl -= tmp_mon_stan_5;
				tmp_mon_stan_5--;
				Count_2zl += 2;
				Count_50gr += 2;

				Count_2zl += (tmp_mon_stan_5 * 5) / 2;
			}

			else {
				Count_5zl -= tmp_mon_stan_5;

				Count_2zl += 2;
				Count_50gr += 2;
			}

		}

		tmp_mon_stan_1 = Hopper_PayOut(Count_2zl, HOPPER_1ZL);
	} else {
		tmp_mon_stan_1 = Hopper_PayOut(Count_2zl, HOPPER_1ZL);
	}

	if (tmp_mon_stan_1) {
		Count_2zl -= tmp_mon_stan_1;
		Count_50gr += tmp_mon_stan_1 * 4;
		tmp_mon_stan_50 = Hopper_PayOut(Count_50gr,
		HOPPER_50GR);
	} else {
		tmp_mon_stan_50 = Hopper_PayOut(Count_50gr, HOPPER_50GR);
	}

	if (tmp_mon_stan_50) {
		FL_ERROR = 1;
		Last_Money_In = Money_In_Automat;
		Last_Transaction_Atmega = tmp_mon_stan_50 * 5;
	}

	if (Count_5zl < Money_5zl_Atmega) {
		Money_5zl_Atmega -= Count_5zl;
	} else {
		Money_5zl_Atmega = 0;
	}

	if (Count_2zl < Money_2zl_Atmega) {
		Money_2zl_Atmega -= Count_2zl;
	} else {
		Money_2zl_Atmega = 0;
	}

	if (Count_50gr < Money_50gr_Atmega) {
		Money_50gr_Atmega -= Count_50gr;
	} else {
		Money_50gr_Atmega = 0;
	}

	Save_Money_Hopper();
	Money_In_Automat = 0;
	FL_WPBlock = false;

	IO_Combo_Clear_Escrow();

}

void Dumpowanie(void) {
	if ((checkPin(PIN_BUTTON_1_IN)) && FL_Button_1) {
		_delay_ms(50);
		Hopper_Dump(1);
	}

	if ((FL_Button_1 == 0) && (!(checkPin(PIN_BUTTON_1_IN)))) {
		FL_Button_1 = 1;
	}

	if ((checkPin(PIN_BUTTON_2_IN)) && FL_Button_2) {
		_delay_ms(50);
		Hopper_Dump(2);
	}

	if ((FL_Button_2 == 0) && (!(checkPin(PIN_BUTTON_2_IN)))) {
		FL_Button_2 = 1;
	}

	if ((checkPin(PIN_BUTTON_3_IN)) && FL_Button_3) {
		_delay_ms(50);
		Hopper_Dump(3);
	}

	if ((FL_Button_3 == 0) && (!(checkPin(PIN_BUTTON_3_IN)))) {
		FL_Button_3 = 1;
	}
}

void Hopper_Dump(uint8_t Hopper) {
	if (Hopper == 1) {
		if (Money_5zl_Atmega > 5) {
			Hopper_PayOut(5, HOPPER_5ZL);
			Money_5zl_Atmega -= 5;
		} else {
			Hopper_PayOut(25, HOPPER_5ZL);
			Money_5zl_Atmega = 0;
		}
	}

	if (Hopper == 2) {
		if (Money_2zl_Atmega > 5) {
			Hopper_PayOut(5, HOPPER_1ZL);
			Money_2zl_Atmega -= 5;
		} else {
			Hopper_PayOut(25, HOPPER_1ZL);
			Money_2zl_Atmega = 0;
		}
	}

	if (Hopper == 3) {
		if (Money_50gr_Atmega > 5) {
			Hopper_PayOut(5, HOPPER_50GR);
			Money_50gr_Atmega -= 5;
		} else {
			Hopper_PayOut(25, HOPPER_50GR);
			Money_50gr_Atmega = 0;
		}
	}

}

