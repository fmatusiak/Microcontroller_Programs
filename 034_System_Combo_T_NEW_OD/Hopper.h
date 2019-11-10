/*
 * Hopper.h
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#ifndef HOPPER_H_
#define HOPPER_H_

#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>

void Check_Hopper(void);
uint8_t Hopper_PayOut(uint8_t Count,uint8_t Hopper);

#endif /* HOPPER_H_ */
