/*
 * IO_Button.h
 *
 *  Created on: 5 lip 2017
 *      Author: dell
 */

#ifndef IO_BUTTON_H_
#define IO_BUTTON_H_

#include "main.h"


uint8_t checkPin(uint16_t pinIn);
void Check_Button_Machine(void);
void Check_IO (uint16_t pinIn,char *text);


#endif /* IO_BUTTON_H_ */
