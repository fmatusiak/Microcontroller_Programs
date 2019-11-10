#include "tetris.h"
#include "main.h"

void tetris() {
	sendHearts();
	sendKeySwitch();
}

void sendHearts() {
	if (heart) {

		for (int i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = com_send_hearts;
				i = buffer_size;
			}
		}
		heart = heart - 5;

		if (FL_heart == 0) {
			for (int i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_quiz_start_rules;
					i = buffer_size;
				}
			}
			FL_heart = 1;
		}
	}

	if (heart == 0) {
		FL_heart = 0;
	}

}




