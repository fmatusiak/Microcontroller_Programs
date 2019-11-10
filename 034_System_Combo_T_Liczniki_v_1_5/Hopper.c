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
				Write_LCD_String_FLASH(PSTR("       HOPPER       "), 3);
				Write_LCD_String_FLASH(PSTR("   HOPPER 1 FAIL   "), 4);
				_delay_ms(1500);
				Write_LCD_String_FLASH(PSTR("                   "), 3);
				Write_LCD_String_FLASH(PSTR("  "), 3);
				convert_m(*(datarecive + 4));
				LCD_WriteText_FLASH(PSTR(" : "));
				convert_m(*(datarecive + 5));
				LCD_WriteText_FLASH(PSTR(" : "));
				convert_m(*(datarecive + 6));
				LCD_WriteText_FLASH(PSTR(" : "));
				_delay_ms(1500);

			}
		}
	} else {
		Write_LCD_String_FLASH(PSTR("   HOPPER 1 ERROR   "), 4);
		while (1) {
		}
	}
	ccTalk_send(HOPPER_1ZL, 0, 242, 0);
	if (ccTalk_recive(datarecive, HOPPER_1ZL)) {

		if (((*(datarecive + 4)) == HOPPER1ID_NUMBER_1)
				&& ((*(datarecive + 5)) == HOPPER1ID_NUMBER_2)
				&& ((*(datarecive + 6)) == HOPPER1ID_NUMBER_3)) {
			Write_LCD_String_FLASH(PSTR("    HOPPER 2 OK     "), 4);
			_delay_ms(1000);
		} else {
			Write_LCD_String_FLASH(PSTR("   HOPPER 2 FAIL   "), 4);
			while (1) {
				Write_LCD_String_FLASH(PSTR("       HOPPER       "), 3);
				Write_LCD_String_FLASH(PSTR("   HOPPER 2 FAIL   "), 4);
				_delay_ms(1500);
				Write_LCD_String_FLASH(PSTR("                   "), 3);
				Write_LCD_String_FLASH(PSTR("  "), 3);
				convert_m(*(datarecive + 4));
				LCD_WriteText_FLASH(PSTR(" : "));
				convert_m(*(datarecive + 5));
				LCD_WriteText_FLASH(PSTR(" : "));
				convert_m(*(datarecive + 6));
				LCD_WriteText_FLASH(PSTR(" : "));
				_delay_ms(1500);

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
				Write_LCD_String_FLASH(PSTR("       HOPPER       "), 3);
				Write_LCD_String_FLASH(PSTR("   HOPPER 3 FAIL   "), 4);
				_delay_ms(1500);
				Write_LCD_String_FLASH(PSTR("                   "), 3);
				Write_LCD_String_FLASH(PSTR("  "), 3);
				convert_m(*(datarecive + 4));
				LCD_WriteText_FLASH(PSTR(" : "));
				convert_m(*(datarecive + 5));
				LCD_WriteText_FLASH(PSTR(" : "));
				convert_m(*(datarecive + 6));
				LCD_WriteText_FLASH(PSTR(" : "));
				_delay_ms(1500);

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

		_delay_ms(20);
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
		_delay_ms(40);
		Stan_Hopper = Hopper_LastPayOut(Hopper);
		while (Stan_Hopper) {
			_delay_ms(20);
			Stan_Hopper = Hopper_LastPayOut(Hopper);
			if (tmp_stan != Stan_Hopper) {
				tmp_stan = Stan_Hopper;
				Tmp_time = 0;
			}
			Tmp_time++;
			_delay_ms(40);
			Check_inhbit();
			if (Tmp_time >= 40) {
				_delay_ms(20);
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
		//	Inhibit_Coin -= 3;
	}

	else {

		if (FL_Cena_UP) {
			//	Inhibit_Coin += 3;
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
	uint16_t Count_5zl, Count_1zl, Count_50gr;
	uint16_t tmp_Count_5zl, tmp_Count_1zl, tmp_Count_50gr;

	if (Money_In_Automat >= Expense_Atmega) {

		Money = Money_In_Automat - Expense_Atmega;

		tmp_Count_5zl = 0;
		tmp_Count_1zl = 0;
		tmp_Count_50gr = 0;

		tmp_Count_5zl = (Money - (Money % 50)) / 50;

		tmp_Count_1zl = (Money - (Money % 10)) / 10;
		tmp_Count_1zl -= (tmp_Count_5zl * 5);

		tmp_Count_50gr = Money / 5;
		tmp_Count_50gr -= (tmp_Count_5zl * 10);
		tmp_Count_50gr -= (tmp_Count_1zl * 2);

		if (Hopper_One_Opto == 3) {

			if (Hopper_Two_Opto == 3) {
				tmp_Count_50gr += tmp_Count_5zl * 10;
				tmp_Count_5zl = 0;
			}
			if (Hopper_Three_Opto == 3) {
				tmp_Count_1zl += tmp_Count_5zl * 5;
				tmp_Count_5zl = 0;
			}
		}

		if (Hopper_Two_Opto == 3) {
			tmp_Count_50gr += tmp_Count_1zl * 2;
			tmp_Count_1zl = 0;

		}

		Count_5zl = tmp_Count_5zl;
		Count_1zl = tmp_Count_1zl;
		Count_50gr = tmp_Count_50gr;

		if ((Hopper_One_Opto != 3) && (Hopper_Two_Opto != 3)
				&& (Hopper_Three_Opto != 3)) {

			tmpFor = tmp_Count_5zl;
			for (uint8_t i = 0; i < tmpFor; i++) {
				rng = RNG();

				if (((rng >= 0) && (rng <= 30))
						|| ((rng > 175) && (rng <= 205))) {

					if (Count_5zl) {
						Count_50gr += 2;
						Count_1zl += 4;
						Count_5zl -= 1;
					}
				} // x % szans

			}
		}
		uint8_t tmp_mon_stan_5 = 0, tmp_mon_stan_1 = 0, tmp_mon_stan_50 = 0;

		tmp_mon_stan_5 = Hopper_PayOut(Count_5zl, HOPPER_5ZL);

		if (tmp_mon_stan_5) {
			Count_1zl += tmp_mon_stan_5 * 5;
			Money_OUT_Liczniki += (Count_5zl - tmp_mon_stan_5) * 10;
		} else {
			Money_OUT_Liczniki += Count_5zl * 10;
		}

		tmp_mon_stan_1 = Hopper_PayOut(Count_1zl, HOPPER_1ZL);

		if (tmp_mon_stan_1) {
			Count_50gr += tmp_mon_stan_1 * 2;

			Money_OUT_Liczniki += (Count_1zl - tmp_mon_stan_1) * 2;
		} else {
			Money_OUT_Liczniki += Count_1zl * 2;
		}

		tmp_mon_stan_50 = Hopper_PayOut(Count_50gr, HOPPER_50GR);

		if (tmp_mon_stan_50) {
			FL_ERROR = 1;
			Last_Money_In = Money_In_Automat;
			Last_Transaction_Atmega = tmp_mon_stan_50 * 5;
			Money_OUT_Liczniki += (Count_50gr - tmp_mon_stan_50);

		} else {
			Money_OUT_Liczniki += Count_50gr;
		}

		if (Count_5zl < Money_5zl_Atmega) {
			Money_5zl_Atmega -= Count_5zl;
		} else {
			Money_5zl_Atmega = 0;
		}

		if (Count_1zl < Money_1zl_Atmega) {
			Money_1zl_Atmega -= Count_1zl;
		} else {
			Money_1zl_Atmega = 0;
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
		if (Money_1zl_Atmega > 5) {
			Hopper_PayOut(5, HOPPER_1ZL);
			Money_1zl_Atmega -= 5;
		} else {
			Hopper_PayOut(25, HOPPER_1ZL);
			Money_1zl_Atmega = 0;
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

