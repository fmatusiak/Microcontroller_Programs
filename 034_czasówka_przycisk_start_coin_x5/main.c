#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "main.h"
#include "HD44780.h"

volatile uint16_t m = 0, min = 0, sec = 0, scores = 0, start = 0;
volatile uint8_t FL_counter = 0, FL_switch = 0, FL_light = 0, FL_start = 0;
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

	DDR_START_IN;
	START_IN_VCC;

	DDR_SWITCH_IN;
	SWITCH_IN_VCC;

	DDR_START_OUT;
	PORT_START_OUT_0;

	DDR_LIGHT_OUT;
	PORT_LIGHT_OUT_1;

	LCD_Initalize();
	LCD_write(1);

	while (1) {
		start++;
		_delay_ms(1);
		if(start > 1000)
		{
			start = 0;
		}

		// ===================== zarówka ============================
		if ((start == 490) && (min || sec)) {
			PORT_LIGHT_OUT_1;
		}

		if (start == 980) {
			start = 0;
			if (min || sec) {
				PORT_LIGHT_OUT_0;
			}

			if (min >= 0) {
				if (sec == 0) {
					if (min == 0) {
						LCD_write(1);
						start = 0;
						scores = 0;
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

		if((!(PIN_COUNTER_IN)) &&(FL_counter == 0))
		{
			FL_counter = 1;
			min += 5;


		}

		if((PIN_COUNTER_IN) &&(FL_counter))
		{
			FL_counter = 0;
		}


		// ================start nabijanie ========================
		if (!(PIN_START_IN)) {

			if (!(PIN_START_IN) && (min || sec) && (start < 490)
					&& (!(FL_start))) {
				scores += 1;
				PORT_START_OUT_1;
				FL_start = 1;
			}
			if (start == 600) {
				PORT_START_OUT_0;
			}
			FL_start = 1;
		}

		else {
			if (start > 600) {
				PORT_START_OUT_0;
				FL_start = 0;
			}



		}

		// ========================== stacyjka =====================
		if ((!(PIN_SWITCH_IN)) && (!FL_switch)) {
			FL_switch = 1;
			min = 0;
			sec = 0;
			scores = 0;
			PORT_LIGHT_OUT_1;
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
		LCD_WriteText("  WRZUC MONETE");
		LCD_GoTo(0, 1);
		LCD_WriteText("  1 zl = 1 min");
		break;
	case 2:
		LCD_Clear();
		LCD_WriteText("Czas ");
		convert_m(min);
		LCD_WriteText(":");
		if (sec < 10)
			LCD_WriteText("0");
		convert_s(sec);

		LCD_GoTo(0, 1);
		LCD_WriteText("Punkty: ");
		convert_m(scores);
		break;
	case 4:
		LCD_Clear();
		LCD_WriteText("  GAME OVER ");
		LCD_GoTo(0, 1);
		LCD_WriteText(" ");
		break;

	}
}

