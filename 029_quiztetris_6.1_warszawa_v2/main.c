#include "main.h"

// GLOBAL VARIABLES

int main(void) {

	ioInit();
	//int ziet = 48;

	configurationInit();

	while (1) {

		if (sended) {
			for (int i = buffer_size; i >= 0; i--) {
				if (commandBuffer[i] != 0) {
					command = commandBuffer[i];
					commandBuffer[i] = 0;
					i = -1;
				}
			}

		}

		if (command != 0) {
			sended = sendCommand(command);
			if (sended == 1) {
				command = 0;
			}

		}

		if (receive == 0) {

			receive = receiveCommand();

		}


		if (FL_TETRIS_ON) {
			sendKeySwitch();

		}
		if (FL_QUIZ_ON) {
			quizomat();
			endTime();
		}
		switchOnCard();
		switchOn();
		switchOnPi();
		if ((receive != 3) && (receive != 7) && (receive != 9)
					&& (receive != 12) && (receive != 5) && (receive != 8)
					&& (receive != 10) && (receive != 13) && (receive != 11)) {
				receive = 0;
			}
	}
}
void ioInit() {
//========== INS ========================
	_delay_ms(500);
	DDR_BET_BUTTON_IN;
	DDR_HOLD_BUTTON_IN;
	DDR_DISPLAY_CHANGE_BUTTON_IN;
	DDR_PAYOUT_BUTTON_IN;
	DDR_PROTECTION_IN;
	DDR_PILOT_IN;
	DDR_KEY_SWITCH_IN;
	DDR_COUNTER_IN;
	DDR_ON_MACHINE_IN;
	DDR_READ_PI_IN;
	DDR_BUTTON_BUTTON_IN;

	BUTTON_BUTTON_IN_VCC;
	BET_BUTTON_IN_VCC;
	HOLD_BUTTON_IN_VCC;
	DISPLAY_CHANGE_BUTTON_IN_VCC;
	PAYOUT_BUTTON_IN_VCC;
	PROTECTION_IN_VCC;
	PILOT_IN_VCC;
	KEY_SWITCH_IN_VCC;
	COUNTER_IN_VCC;
	ON_MACHINE_IN_VCC;
	READ_PI_IN_VCC;

//========= OUTS ========================
	BET_BUTTON_OUT_DDR;
	HOLD_BUTTON_OUT_DDR;
	PAYOUT_OUT_DDR;
	START_OUT_DDR;
	MUTE_OUT_DDR;
	SCREEN_SWITCH_OUT_DDR;
	SWITCH_RELAY_DDR;
	SEND_PI_OUT_DDR;
	ALARM_DDR;
	CONTROL_DDR;
	BUTTON_BUTTON_OUT_DDR;
	BET_BUTTON_OUT_LOW;
	HOLD_BUTTON_OUT_LOW;
	PAYOUT_OUT_LOW;
	START_OUT_LOW;
	SCREEN_SWITCH_OUT_LOW;
	SWITCH_RELAY_LOW;
	SEND_PI_OUT_HIGH;
	ALARM_LOW;
	CONTROL_LOW;
	MUTE_OUT_HIGH;
	BUTTON_BUTTON_OUT_LOW;

	/*	while (!(PIN_READ_PI_IN)) {

	 }*/
	_delay_ms(500);

}
void configurationInit() {
	buffer_size = 20;
	for (uint8_t i = 0; i < buffer_size; i++) {
		commandBuffer[i] = 0;
	}
	// commands quiz sended
	sended = 1, com_switch_on_tetris = 4;
	com_quiz_on = 3;

	com_quiz_start_rules = 2, com_add_time_one = 1;
	klik_payout = 9, key_switch_clear = 5;

	//odbierane
	com_Relay_ON = 9, com_off = 9;
	com_unlock_BET = 5;
	com_unlock_HOLD = 8;
	com_unlock_Button = 10;
	// commands quiz received

	com_round = 11, com_unlock_pay = 13, com_disp_ON = 12;
	// commands tetris
	counter_off = 10000;
	TETRIS_ON = 0, QUIZ_ON = 0, FL_TETRIS_ON = 1, FL_pilot = 1, FL_QUIZ_ON = 0;
	FL_automatOn = 0, command = 0, receive = 0;
	FL_keySwitch = 1, FL_start = 0;

	startTimeout = 0, startImpulseTime = 4000;
	FL_CARD = 1, FL_counter_in = 0;
	counterTimeout_counter = 0;
	FL_pilotes = 0, FLAGA_Send = 0, FL_wyk = 0, FL_bet = 0, FL_button = 0;
	FL_hold = 0;

	initSettings();

	if (!(PIN_PILOT_IN)) {
		FL_pilotes = 1;
	}

}

void initSettings() {
	CONTROL_HIGH;

	while (receive != com_off) {
		receive = receiveCommand();

		if (receive == 5) {
			QUIZ_ON = 1;

		}
		if (receive == 4) {
			TETRIS_ON = 1;
			FL_TETRIS_ON = 1;
		}

	}
	settings();
	_delay_ms(100);

	if ((QUIZ_ON == 1) && (TETRIS_ON == 1)) {
		while (!sendCommand(com_switch_on_tetris)) {
			;
		}

	}

	FL_start = 1;
	receive = 0;

}
void switchOnPi() {
	if (((PIN_PILOT_IN) && FL_pilotes && FL_pilot)
			|| ((!(PIN_PILOT_IN)) && (FL_pilotes == 0) && FL_pilot)) {
		_delay_ms(2);
		if (((PIN_PILOT_IN) && FL_pilotes && FL_pilot)
				|| ((!(PIN_PILOT_IN)) && (FL_pilotes == 0) && FL_pilot)) {
			FL_pilot = 0;
			SCREEN_SWITCH_OUT_LOW;
			FL_automatOn = 0;
			if (TETRIS_ON == 0) {
				FL_TETRIS_ON = 0;
				FL_QUIZ_ON = 1;
			} else {
				FL_TETRIS_ON = 1;
				FL_QUIZ_ON = 0;
			}

			if ((TETRIS_ON)) {
				for (uint8_t i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = com_switch_on_tetris;
						i = buffer_size;
					}
				}
			}
			if ((TETRIS_ON == 0) && (QUIZ_ON == 1)) {
				for (uint8_t i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = com_quiz_on;
						i = buffer_size;
					}
				}
			}

		}
	}
}

void settings() {
	if ((!(PIN_KEY_SWITCH_IN)) && (!FL_automatOn)) {

		while (!sendCommand(7)) {
			;

		}
		while (!receive) {
			receive = receiveCommand();
		}

		while (1) {
			;
		}

	}
}
void switchOn() {
	if (receive == 3) {

		FL_automatOn = 1;
		SCREEN_SWITCH_OUT_HIGH;

		_delay_ms(1000);
		_delay_ms(2000);

		for (uint8_t i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = com_quiz_on;
				i = buffer_size;
			}
		}

		receive = 0;
		FL_TETRIS_ON = 0;
		FL_QUIZ_ON = 1;

	}
}
void endTime() {
	if (receive == 7) {
		receive = 0;
		for (uint8_t i = 0; i < buffer_size; i++) {
			commandBuffer[i] = 0;
		}

		FL_bet = 0;
		FL_hold = 0;
		FL_button = 0;
		FL_payout = 0;
		SWITCH_RELAY_LOW;

		PAYOUT_OUT_HIGH;
		_delay_ms(100);
		PAYOUT_OUT_LOW;
	}
}
void switchOnCard() {
	if (!(PIN_CARD_IN) && FL_CARD) {
		_delay_ms(5);
		if (!(PIN_CARD_IN)) {
			FL_CARD = 0;
			FL_automatOn = 1;
			SCREEN_SWITCH_OUT_HIGH;

			_delay_ms(1000);

			_delay_ms(2000);
			for (uint8_t i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] == 0) {
					commandBuffer[i] = com_quiz_on;
					i = buffer_size;
				}
			}
			receive = 0;
			FL_TETRIS_ON = 0;
			FL_QUIZ_ON = 1;
		}

	}
}

int sendCommand(uint8_t command) {
	uint8_t secondCommand, secondCommandtmp, commandtmp;
	uint8_t togetherCommand, togetherCommandtmp, delay_time = 104;
	int tab[8];
	secondCommand = command;
	togetherCommand = command + command;
	secondCommandtmp = command;
	togetherCommandtmp = command + command;
	commandtmp = command;
	command = commandtmp;
	int j = 0;
	CONTROL_LOW;
	for (int i = 128; i >= 1; i = i / 2) {
		if (command >= i) {
			tab[j] = 1;
			command -= i;
			j++;
		} else {
			tab[j] = 0;
			j++;
		}
	}
	if (!(PIN_READ_PI_IN)) {
		SEND_PI_OUT_LOW;
		FLAGA_Send = 1;
		_delay_us(delay_time);
		for (int i = 7; i >= 0; i--) {

			if (tab[i] == 1) {
				SEND_PI_OUT_HIGH;
			} else {
				SEND_PI_OUT_LOW;
			}
			_delay_us(delay_time);
		}
		SEND_PI_OUT_HIGH;
		_delay_ms(3);
		if ((PIN_READ_PI_IN)) {
			SEND_PI_OUT_HIGH;
			CONTROL_HIGH;
			return 1;
		} else {
			return 0;
		}
	} else {

		return 0;
	}

}

uint8_t receiveCommand() {
	uint16_t delayTime = 998;

	sendTimeCounter();
	uint8_t commandlocal = 0, secondcommand = 0;
	if (!(PIN_READ_PI_IN)) {
		_delay_us(delayTime);
		if (!(PIN_READ_PI_IN)) {
			CONTROL_LOW;

			for (uint8_t i = 0; i < 21; i++) {
				_delay_us(delayTime + 1);

			}
			for (int i = 8; i >= 1; i = i / 2) {
				if ((PIN_READ_PI_IN)) {
					commandlocal += i;
				}
				_delay_ms(5);
			}

			for (int i = 8; i >= 1; i = i / 2) {
				if ((PIN_READ_PI_IN)) {
					secondcommand += i;
				}
				_delay_ms(5);
			}

		}
	}
	sendTimeCounter();
	if ((commandlocal == secondcommand) && (commandlocal)) {

		CONTROL_HIGH;
		for (uint8_t i = 0; i < 20; i++) {
			_delay_us(delayTime);
		}

		return commandlocal;
	} else {

		return 0;
	}
}

