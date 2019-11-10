/*
 * LCD.h
 *
 *  Created on: 17 lip 2017
 *      Author: dell
 */

#ifndef LCD_H_
#define LCD_H_
#include "main.h"




void Write_LCD(uint8_t n);
void Write_LCD_String_FLASH(const char * text, uint8_t pos);
void Write_LCD_String_RAM(char * text, uint8_t pos);
void convert_m(uint16_t m);


uint8_t LSWprowadzono, PSWprowadzono;
uint8_t LSBrakuje, PSBrakuje;
uint8_t tmp_money_In, tmp_money_Brak, tmp_money_koszt;
uint16_t Tmp_time_while;


#endif /* LCD_H_ */
