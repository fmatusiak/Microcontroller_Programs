#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "main.h"
#include "HD44780.h"

volatile uint16_t buffer[21], bufferOld[21], bank = 0, event = -1, firstRun = 1,
		wyplata_out1 = 0;
volatile uint16_t coins = 0, ban = 0, outs5 = 0, outs2 = 0, ins = 0, timie_out =
		0, time_out_coin = 0;
volatile uint8_t flaga_button = 0, ktory = 0, wyplata = 1, flaga_wyplata = 0,
		wyplata_out = 0, flaga_serwis = 1, flaga_lcd_hopper1,
		flaga_lcd_hopper2 = 0, flaga_bank = 1, flaga_menu = 0, zatwierdz = 1;

volatile uint16_t ine_cal = 0, out5e_cal = 0, out2e_cal = 0, ilosc5 = 0,
		ilosc2 = 0, change_disp = 0;
volatile uint8_t ine_prawy = 0, ine_lewy = 0, out5e_lewy = 0, out5e_prawy = 0,
		out2e_lewy = 0, out2e_prawy = 0, check_pay = 0;

uint8_t EEMEM in_prawy = 0;
uint8_t EEMEM out5_prawy = 0;
uint8_t EEMEM out2_prawy = 0;

uint8_t EEMEM in_lewy = 0;
uint8_t EEMEM out5_lewy = 0;
uint8_t EEMEM out2_lewy = 0;

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51
void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
void convert_m(uint16_t);
int bufferEq(void);
void napisz(uint8_t n);
void gpioInit();
void billInit();
void menu();
void payout(int);
void save_counters(uint16_t, uint16_t, uint16_t);

int main(void) {
	LCD_Initalize();
	napisz(1);
	gpioInit();
	uart_init(RS_UBRR);
	billInit();
	save_counters(0, 0, 0);

	if (!(PIN_SWITCH_IN))
		flaga_serwis = 0;

	while (1) {

		uartPut(40, 0, 1, 159, 0);
		for (int i = 0; i < 21; i++) { //21

			buffer[i] = uart_getc();
			if (firstRun == 1) {
				bufferOld[i] = buffer[i];
				firstRun = 0;
			}
		}
		if (buffer[10] == 1 || buffer[10] == 2 || buffer[10] == 3
				|| buffer[10] == 4 || buffer[10] == 5 || buffer[10] == 6
				|| buffer[10] == 7 || buffer[10] == 8 || buffer[10] == 9
				|| buffer[10] == 10) {

			if (event != buffer[9]) {
				event = buffer[9];

				// CREDIT
				if (buffer[11] == 0 && buffer[12] == buffer[10]
						&& buffer[13] == 1 && bufferEq() == 1) {
					if ((buffer[10] == 1) || (buffer[10] == 6)) {
						bank += 10;
						save_counters(10, 0, 0);

					} else if ((buffer[10] == 2) || (buffer[10] == 7)) {
						bank += 20;
						save_counters(20, 0, 0);

					} else if ((buffer[10] == 3) || (buffer[10] == 8)) {
						bank += 50;
						save_counters(50, 0, 0);

					} else if ((buffer[10] == 4) || (buffer[10] == 9)) {
						bank += 100;
						save_counters(100, 0, 0);

					}

					else if ((buffer[10] == 5) || (buffer[10] == 10)) {
						bank += 200;
						save_counters(200, 0, 0);

					}

					_delay_ms(50);
					uartPut(40, 1, 1, 228, (uint8_t[]) {0});
					for (int i = 0; i < 11; i++) { //21

						buffer[i] = uart_getc();
					}
				} else if (buffer[11] == 1 && bufferEq() == 1) {
					// PENDING CREDIT
				}
			}

		}
		int i = 0;
		for (i = 0; i < 21; i++) {
			bufferOld[i] = buffer[i];
		}
		for (int i = 0; i < 100; i++) {
			_delay_us(500);
			menu();
			payout(wyplata_out1);
		}

		uartPut(40, 1, 1, 154, (uint8_t[]) {1});
		for (int i = 0; i < 12; i++) { //21

			buffer[i] = uart_getc();
		}
		for (int i = 0; i < 100; i++) {
			_delay_us(500);
			menu();
			payout(wyplata_out1);
		}

	}

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

uint8_t uart_ischar() {
	// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc() {
	// Czy w buforze s¹ dane?'
	timie_out = 1;
	while ((!uart_ischar()) && timie_out) {
		timie_out++;

		if (timie_out >= 10000)
			timie_out = 0;

	};

	return UDR;
}

void uartPut(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,
		uint8_t *data) {
	uart_putc(from);
	uart_putc(dataCount);
	uart_putc(to);
	uart_putc(command);
	uint8_t checkSum = from + to + command + dataCount;
	for (int i = 0; i < dataCount; i++) {
		uart_putc(data[i]);
		checkSum += data[i];
	}
	checkSum %= 256;
	checkSum = 256 - checkSum;
	uart_putc(checkSum);
}

void convert_m(uint16_t m) {
	char str[16];
	utoa(m, str, 10);
	LCD_WriteText(str);
}

int bufferEq() {
	int bufferEq = -1;
	int i;
	if (firstRun == 1)
		return 1;
	for (i = 10; i < 18; i++) {
		if (buffer[i + 2] == bufferOld[i]) {
			bufferEq = 1;
		} else {
			bufferEq = -1;
			break;
		}
	}
	return bufferEq;
}

void billInit() {

	_delay_ms(2000);
	uartPut(40, 0, 1, 254, 0);
	_delay_ms(200);
	uartPut(40, 2, 1, 231, (uint8_t[]) {255, 255});
	_delay_ms(200);
	uartPut(40, 1, 1, 228, (uint8_t[]) {1});
	_delay_ms(200);

}

void gpioInit() {

	DDR_BUTTON1_IN;
	DDR_BUTTON2_IN;
	DDR_SWITCH_IN;
	DDR_COIN1_IN;
	DDR_COIN2_IN;
	DDR_HOPPERON1_OUT;
	DDR_HOPPERON2_OUT;
	PORT_HOPPERON1_OUT_1;
	PORT_HOPPERON2_OUT_1;
	SWITCH_IN_VCC;
	BUTTON1_IN_VCC;
	BUTTON2_IN_VCC;
}

void menu() {
	if (!(PIN_SWITCH_IN)) {

		change_disp++;
		flaga_menu = 1;
		flaga_serwis = 1;

		if (change_disp == 0)
			napisz(6);

		if (change_disp == 10000) {
			change_disp = 0;
			napisz(6);
		}

		if (change_disp == 5000)
			napisz(9);

		if (!(PIN_BUTTON1_IN)) {
			if (flaga_lcd_hopper1 == 0) {
				napisz(7);
				PORT_HOPPERON1_OUT_0;
				flaga_lcd_hopper1 = 1;
			}

		} else {
			if (flaga_lcd_hopper1 == 1) {
				flaga_lcd_hopper1 = 0;
				flaga_serwis = 0;
			}
			PORT_HOPPERON1_OUT_1;
		}

		if (!(PIN_BUTTON2_IN)) {
			if (flaga_lcd_hopper2 == 0) {
				napisz(8);
				PORT_HOPPERON2_OUT_0;
				flaga_lcd_hopper2 = 1;
			}
		} else {
			if (flaga_lcd_hopper2 == 1) {
				flaga_lcd_hopper2 = 0;
				flaga_serwis = 0;
			}

			PORT_HOPPERON2_OUT_1;
		}
	} else

	{
		if (flaga_serwis == 1) {
			flaga_serwis = 0;
			napisz(1);
		}

		if (bank == 0)
			napisz(10);

		else {

			if ((flaga_bank == 1) && (zatwierdz == 1)) {
				flaga_bank = 0;
				napisz(2);
				wyplata = 1;
			}

			if (!(PIN_BUTTON1_IN)) {
				flaga_button = 1;

			}

			if ((PIN_BUTTON1_IN) && (flaga_button == 1) && (zatwierdz == 1)) {
				flaga_button = 0;
				ktory++;
				if (ktory == 1) {
					napisz(2);
					wyplata = 1;
				}

				if (ktory == 2) {
					napisz(3);
					ktory = 0;
					wyplata = 2;
				}

			}
			if (!(PIN_BUTTON2_IN)) {
				flaga_wyplata = 1;

			}

			if ((PIN_BUTTON2_IN) && flaga_wyplata == 1) {
				zatwierdz = 0;
				flaga_wyplata = 0;
				wyplata_out = 1;
				flaga_bank = 1;
				wyplata_out1 = wyplata;
				payout(wyplata_out1);
				check_pay = 1;
				_delay_ms(20);
				uartPut(40, 1, 1, 228, (uint8_t[]) {0});
				for (int i = 0; i < 11; i++) { //21

					buffer[i] = uart_getc();
				}
			}

		}
	}

}

void napisz(uint8_t n) {
	switch (n) {
	case 1:
		LCD_Clear();
		LCD_WriteText("  ROZMIENIARKA  ");
		LCD_GoTo(0, 1);
		LCD_WriteText(" 5 zl      2 zl ");
		break;
	case 2:
		LCD_Clear();
		LCD_WriteText("    WYBIERZ     ");
		LCD_GoTo(0, 1);
		LCD_WriteText(" [5 zl]    2 zl ");
		break;
	case 3:
		LCD_Clear();
		LCD_WriteText("    WYBIERZ     ");
		LCD_GoTo(0, 1);
		LCD_WriteText(" 5 zl    [2 zl] ");
		break;
	case 4:
		LCD_Clear();
		LCD_WriteText("    WYPLATA     ");
		LCD_GoTo(0, 1);
		LCD_WriteText(" POZOSTALO: ");
		convert_m(bank);
		break;
	case 5:
		LCD_Clear();
		LCD_WriteText(" ZAWOLAJ OBSLUGE ");
		LCD_GoTo(0, 1);
		LCD_WriteText(" POZOSTALO: ");
		convert_m(bank);
		break;

	case 6:
		LCD_Clear();
		LCD_WriteText("IN:");
		convert_m(ine_cal);
		break;
	case 7:
		LCD_Clear();
		LCD_WriteText("      DUMP       ");
		LCD_GoTo(0, 1);
		LCD_WriteText("   HOPPER 5 zl   ");
		break;

	case 8:
		LCD_Clear();
		LCD_WriteText("      DUMP       ");
		LCD_GoTo(0, 1);
		LCD_WriteText("   HOPPER 2 zl   ");
		break;
	case 9:
		LCD_Clear();
		LCD_WriteText("OUT5:");
		convert_m(out5e_cal);
		LCD_GoTo(0, 1);
		LCD_WriteText("OUT2:");
		convert_m(out2e_cal);
		break;

	}
}

void payout(int hopper) {
	if ((hopper == 2) && (bank > 0)) {
		PORT_HOPPERON1_OUT_0;

		if (time_out_coin == 20000) {
			PORT_HOPPERON1_OUT_1;

			napisz(5);
			bank = 0;
			_delay_ms(50);
			uartPut(40, 2, 1, 231, (uint8_t[]) {0, 0});
			for (int i = 0; i < 12; i++) { //21

				buffer[i] = uart_getc();
			}
			save_counters(0, ilosc5, ilosc2);
			while (1) {
			}

		}

		time_out_coin++;
		if (!(PIN_COIN1_IN)) {
			time_out_coin = 0;
			bank -= 2;
			ilosc2++;
			napisz(4);
			while (!(PIN_COIN1_IN)) {
			}
			flaga_menu = 0;
			time_out_coin = 0;
		}
	}

	if ((hopper == 1) && (bank > 0)) {
		PORT_HOPPERON2_OUT_0;

		if (time_out_coin == 20000) {
			PORT_HOPPERON2_OUT_1;
			napisz(5);
			bank = 0;
			_delay_ms(50);
			uartPut(40, 2, 1, 231, (uint8_t[]) {0, 0});
			for (int i = 0; i < 12; i++) { //21

				buffer[i] = uart_getc();
			}
			save_counters(0, ilosc5, ilosc2);
			while (1) {
			}

		}

		time_out_coin++;

		if (!(PIN_COIN2_IN)) {
			bank -= 5;
			ilosc5++;
			napisz(4);
			while (!(PIN_COIN2_IN)) {
			}
			flaga_menu = 0;
			time_out_coin = 0;
		}
	}

	if (bank == 0 && check_pay == 1) {
		if (flaga_menu == 0) {
			napisz(1);
			flaga_menu = 1;
			flaga_bank = 1;
		}
		save_counters(0, ilosc5, ilosc2);
		time_out_coin = 0;
		PORT_HOPPERON1_OUT_1;
		PORT_HOPPERON2_OUT_1;
		wyplata_out1 = 0;
		zatwierdz = 1;
		ilosc2 = 0;
		ilosc5 = 0;
		check_pay = 0;
		_delay_ms(20);
		uartPut(40, 1, 1, 228, (uint8_t[]) {1});
		for (int i = 0; i < 11; i++) { //21

			buffer[i] = uart_getc();
		}

	}
}

void save_counters(uint16_t _in, uint16_t _out5, uint16_t _out2) {

	ine_lewy = eeprom_read_byte(&in_lewy);
	out5e_lewy = eeprom_read_byte(&out5_lewy);
	out2e_lewy = eeprom_read_byte(&out2_lewy);

	ine_prawy = eeprom_read_byte(&in_prawy);
	out5e_prawy = eeprom_read_byte(&out5_prawy);
	out2e_prawy = eeprom_read_byte(&out2_prawy);

	ine_cal = (ine_lewy << 8) + ine_prawy;
	ine_cal += _in;
	if (ine_cal >= 65535) {
		ine_cal += 1;
		eeprom_write_byte(&in_lewy, (ine_cal >> 8));
		eeprom_write_byte(&in_prawy, (ine_cal - ((ine_cal >> 8) << 8)));
	}

	out5e_cal = (out5e_lewy << 8) + out5e_prawy;
	out5e_cal += _out5;
	if (out5e_cal >= 65535) {
		out5e_cal += 1;
		eeprom_write_byte(&out5_lewy, (out5e_cal >> 8));
		eeprom_write_byte(&out5_prawy, (out5e_cal - ((out5e_cal >> 8) << 8)));
	}

	out2e_cal = (out2e_lewy << 8) + out2e_prawy;
	out2e_cal += _out2;
	if (out2e_cal >= 65535) {
		out2e_cal += 1;
		eeprom_write_byte(&out2_lewy, (out2e_cal >> 8));
		eeprom_write_byte(&out2_prawy, (out2e_cal - ((out2e_cal >> 8) << 8)));

	}

	if (_in != 0) {
		eeprom_write_byte(&in_lewy, (ine_cal >> 8));
		eeprom_write_byte(&in_prawy, (ine_cal - ((ine_cal >> 8) << 8)));
	}

	if (_out5 != 0) {
		eeprom_write_byte(&out5_lewy, (out5e_cal >> 8));
		eeprom_write_byte(&out5_prawy, (out5e_cal - ((out5e_cal >> 8) << 8)));
	}

	if (_out2 != 0) {
		eeprom_write_byte(&out2_lewy, (out2e_cal >> 8));
		eeprom_write_byte(&out2_prawy, (out2e_cal - ((out2e_cal >> 8) << 8)));
	}

}

