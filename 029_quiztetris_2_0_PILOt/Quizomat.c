/*
 * Tetris.c
 *
 *  Created on: 15-09-2016
 *      Author: pi
 */

#include "Quizomat.h"
#include "main.h"

void quizomat() {

	sendTime();


}

void sendTime() {

	if ((!(PIN_COUNTER_IN)) && FL_counter) {
		_delay_ms(2);
		if (!(PIN_COUNTER_IN)) {
			FL_counter = 0;
			counterTimeout = 1;
			counter_pulses++;
			if (counter_pulses > 10) {
				for (int i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = 10;
						counter_pulses -= 10;
						i = buffer_size;

					}
				}
			}
		}
	} else if (PIN_COUNTER_IN) {
		if (counterTimeout) {
			counterTimeout++;
		}
		if (counterTimeout == counter_off) {
			for (int i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					if (counter_pulses >= 5) {
						commandBuffer[i] = 5;
						counter_pulses -= 5;
						i++;
					}
				}
				if (commandBuffer[i] == 0) {
					if (counter_pulses >= 2) {
						commandBuffer[i] = 2;
						counter_pulses -= 2;
						i++;
					}
				}
				if (commandBuffer[i] == 0) {
					if (counter_pulses >= 1) {
						commandBuffer[i] = 1;
						counter_pulses -= 1;
						i++;
					}
				}
			}

			counterTimeout = 0;
		}
		FL_counter = 1;
	}

}


