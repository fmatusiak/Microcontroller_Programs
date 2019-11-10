/*
 * jackpot.c
 *
 *  Created on: 2 lis 2016
 *      Author: dell
 */

#include "jackpot.h"
#include "main.h"

void jackpot() {

	checkCounterJackpot();
	buzzer();
	if (value_jackpot) {
		sendCounterJackpot();
	}
}
void checkCounterJackpot() {
	if (FL_automatOn) {

		if ((PIN_JACKPOT_START_IN))
		{
			FL_KEY = 1;
		}

		if (((!(PIN_JACKPOT_START_IN)) &&(!(PIN_JACKPOT_STAWKA_LIGHT_IN))) && (FL_KEY == 1)) {
			FLAGA_START = 1;
			TMP_LIGHT = 0;

		}
		if (FLAGA_START == 1) {
			TMP_LIGHT++;
			if ((TMP_LIGHT > 500) && ((PIN_JACKPOT_STAWKA_LIGHT_IN))) {
				FLAGA_START = 0;
				TMP_LIGHT = 0;

				if (!(PIN_JACKPOT_START_LIGHT_IN)) {
					FL_KEY = 0;
					value_jackpot++;
					timeout_jackpot = 0;
				}
			}
		}
	}
}

void sendCounterJackpot() {
	if (FL_automatOn) {
		timeout_jackpot++;

		if (value_jackpot >= 5) {
			for (int i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = 12;
					value_jackpot -= 5;
					i = buffer_size;
				}
			}
		}

		if (timeout_jackpot >= 5000) {

			if (value_jackpot >= 2) {

				for (int i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = 9;
						value_jackpot -= 2;
						i = buffer_size;
					}
				}
			}
			if (value_jackpot >= 1) {

				for (int i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = 4;
						value_jackpot -= 1;
						i = buffer_size;
					}
				}
			}
			timeout_jackpot = 0;
		}
	}
}

void buzzer() {
	if (FL_automatOn) {
		if (receive == buzzer_on) {
			ALARM_HIGH;
		}
		if (receive == buzzer_off) {
			ALARM_LOW;
		}
	}
}

