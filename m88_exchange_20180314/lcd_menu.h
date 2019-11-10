/*
 * lcd_menu.h
 *
 *  Created on: 18 kwi 2017
 *      Author: Gaja
 */

#ifndef LCD_MENU_H_
#define LCD_MENU_H_

void lcd_update(uint8_t x,uint8_t y ,uint32_t val);
void lcd_display_menu(uint8_t screen, uint8_t data);
void lcd_error(void);
void lcd_service(uint8_t type);
void convert(uint32_t data);
void service_menu(void);
//void lcd_print_up(char string);
//void lcd_print_down(char *string);

#endif /* LCD_MENU_H_ */
