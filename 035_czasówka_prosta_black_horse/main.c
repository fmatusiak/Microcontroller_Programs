#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "main.h"
#include "HD44780.h"

volatile uint16_t min = 0, sec = 0, start = 0;
volatile uint8_t FL_counter = 0, FL_switch = 0, Fl_end = 0, fl_game = 0;
void LCD_write(uint8_t n);

void convert_m(uint64_t m) {
	char str[16];
	itoa(m, str, 10);
	LCD_WriteText(str);
}

void convert_s(uint8_t s) {
	char str[16];
	itoa(s, str, 10);
	LCD_WriteText(str);
}

int main(void) {

	DDR_COUNTER_IN;
	COUNTER_IN_VCC;

	DDR_keySwitch_IN;
	keySwitch_IN_VCC;

	DDR_PayOut_OUT;
	PORT_PayOut_OUT_0;

	LCD_Initalize();
	LCD_write(5);

	_delay_ms(500);
	_delay_ms(500);
	LCD_write(1);
	while (1) {
		start++;
		_delay_ms(1);

		// ===================== zarówka ============================

		if (Fl_end == 1) {
			Fl_end = 0;
			PORT_PayOut_OUT_1;
			_delay_ms(100);
			PORT_PayOut_OUT_0;
			_delay_ms(100);
			PORT_PayOut_OUT_1;
			_delay_ms(100);
			PORT_PayOut_OUT_0;
		}

		if (start >= 990) {
			start = 0;

			if (min >= 0) {
				if (sec == 0) {
					if (min == 0) {

						start = 0;
						if (fl_game) {
							LCD_write(1);
							Fl_end = 1;
							fl_game = 0;
						}
					} else {

						LCD_write(2);
						sec = 59;
						--min;
					}
				} else {
					LCD_write(2);
					--sec;
				}
			}
		}
		// ======================= licznik =======================

		if ((!(PIN_COUNTER_IN)) && (FL_counter == 0)) {
			FL_counter = 1;
			min += 1;
			fl_game = 1;
		}

		if ((PIN_COUNTER_IN) && (FL_counter)) {
			FL_counter = 0;

		}

		// ========================== stacyjka =====================
		if ((!(PIN_keySwitch_IN)) && (!FL_switch)) {
			FL_switch = 1;
			min = 0;
			sec = 0;
			Fl_end = 0;
			fl_game = 0;
			LCD_write(1);
		} else {
			if (FL_switch) {

				FL_switch = 0;
			}
		}
	}
}
void LCD_write(uint8_t n) {
	switch (n) {
	case 1:
		LCD_Clear();
		LCD_WriteText("  WRZUC MONETE  ");
		LCD_GoTo(0, 1);
		LCD_WriteText("  1 zl = 1 min  ");
		break;
	case 2:
		LCD_Clear();
		LCD_WriteText("    Czas Gry    ");
		LCD_GoTo(0, 1);
		LCD_WriteText("      ");
		convert_m(min);
		LCD_WriteText(":");
		if (sec < 10)
			LCD_WriteText("0");
		convert_s(sec);

		break;
	case 4:
		LCD_Clear();
		LCD_WriteText("  GAME OVER ");
		LCD_GoTo(0, 1);
		LCD_WriteText(" ");
		break;
	case 5:
		LCD_Clear();
		LCD_WriteText("      TRWA      ");
		LCD_GoTo(0, 1);
		LCD_WriteText("  URUCHAMIANIE  ");
		break;

	}
}

