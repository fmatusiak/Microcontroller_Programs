/*
 * IO_Board.h
 *
 *  Created on: 4 lip 2017
 *      Author: dell
 */

#ifndef IO_Combo_H_
#define IO_Combo_H_

#include "main.h"




void Check_IO_Combo(void);
uint8_t IO_Combo_Send(uint8_t dataCount,uint8_t command,uint8_t *data,uint8_t *datarecive);
void IO_Combo_Clear_Escrow(void);








#endif /* IO_BOARD_H_ */
