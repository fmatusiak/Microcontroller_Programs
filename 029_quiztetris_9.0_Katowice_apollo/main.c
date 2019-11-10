#include "main.h"

// GLOBAL VARIABLES

int main(void) {

	ioInit();
	//int ziet = 48;

	configurationInit();
	switchOnCard();
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

		receive = receiveCommand();

		if (FL_QUIZ_ON) {
			quizomat();
			displaySwitch();
			endTime();
		} else if (QUIZ_ON) {
			quizomat();

		}
		switchOn();

	}
}
void ioInit() {
//========== INS ========================
	_delay_ms(500);
	DDR_COIN_ACCEPTOR_IN;
	DDR_BILL_ACCEPTOR_IN;
	DDR_DISPLAY_CHANGE_BUTTON_IN;
	DDR_PAYOUT_BUTTON_IN;

	DDR_KEY_SWITCH_IN;
	DDR_COUNTER_IN;
	DDR_KEY_8_IN;
	DDR_KEY_9_IN;
	DDR_KEY_AG_IN;
	DDR_PROTECTION_IN;
	DDR_READ_PI_IN;
	DDR_CARD_IN;

	DDR_COUNTER_OUT_IN;
	CARD_IN_VCC;
	COIN_ACCEPTOR_IN_VCC;
	BILL_ACCEPTOR_IN_VCC;
	DISPLAY_CHANGE_BUTTON_IN_VCC;
	PAYOUT_BUTTON_IN_VCC;

	KEY_SWITCH_IN_VCC;
	COUNTER_IN_VCC;
	KEY_8_IN_VCC;
	KEY_9_IN_VCC;
	KEY_AG_IN_VCC;
	READ_PI_IN_VCC;
	PROTECTION_IN_VCC;
	COUNTER_OUT_IN_VCC;
	OUT_5_DDR;

//========= OUTS ========================
	COIN_ACCEPTOR_OUT_DDR;
	BILL_ACCEPTOR_OUT_DDR;
	PAYOUT_OUT_DDR;
	START_OUT_DDR;
	SCREEN_SWITCH_OUT_DDR;
	SWITCH_ON_MACHINE_DDR;
	SEND_PI_OUT_DDR;
	ALARM_DDR;
	CONTROL_DDR;
	COIN_ACCEPTOR_OUT_LOW;
	BILL_ACCEPTOR_OUT_LOW;
	PAYOUT_OUT_LOW;
	START_OUT_LOW;
	SCREEN_SWITCH_OUT_LOW;
	SWITCH_ON_MACHINE_LOW;
	SEND_PI_OUT_HIGH;
	ALARM_LOW;
	CONTROL_LOW;
	OUT_5_LOW;

	_delay_ms(500);

}
void configurationInit() {
	buffer_size = 40;
	for (int i = 0; i < buffer_size; i++) {
		commandBuffer[i] = 0;
	}
	// commands quiz sended
	sended = 1, com_attack = 13, com_clear_time_switch = 14, com_switch_on_tetris =
			7, com_quiz_start_rules = 3, com_quiz_on = 6;
	// commands quiz received
	com_round = 11, com_lock_pay = 12, com_unlock_pay = 13, com_quiz_on = 6;
	// commands tetris
	counter_pulses = 0, counter_off = 10000;
	switchTimeout = 0;
	TETRIS_ON = 0, QUIZ_ON = 0, FL_QUIZ_ON = 0;
	counterTimeout = 0;
	FL_counter = 1, FL_automatOn = 0, command = 0, pause = 20, receive = 0;
	FL_keySwitch = 1, FL_display = 0, FL_start = 0;

	FL_protection = 0, displayTimeout = 1000, FL_start_rules = 1, FL_counter_in =
			0, FLAGA_Send = 0, FL_wyk = 0;
	FL_KREDYT = 0;
	FL_SEND_KREDYT = 1;
	FL_start_rules_counter = 1;

	FL_counter_pulses = 1;

	Counter_IN_1_send = 1;
	Counter_IN_5_send = 2;
	Counter_IN_2_send = 4;
	Counter_IN_10_send = 5;

	initSettings();
	settings();
	_delay_ms(100);

}

void initSettings() {
	CONTROL_HIGH;

	while (receive != 15) {
		receive = receiveCommand();

		if (receive == 5) {
			QUIZ_ON = 1;

		}
		if (receive == 4) {
			TETRIS_ON = 0;

		}

		if ((QUIZ_ON == 1) && (TETRIS_ON == 1)) {
			command = com_switch_on_tetris;

		}

		if ((QUIZ_ON == 1) && (TETRIS_ON == 0)) {
			command = com_quiz_on;
		}

		if ((QUIZ_ON == 0) && (TETRIS_ON == 1)) {
			command = com_switch_on_tetris;
		}

	}

	FL_start = 1;
	receive = 0;

}

void switchOnCard(void) {

	FL_automatOn = 1;
	SWITCH_ON_MACHINE_LOW;
	SCREEN_SWITCH_OUT_LOW;

	_delay_ms(1000);

	_delay_ms(2000);
	for (int i = 0; i < buffer_size; i++) {
		if (commandBuffer[i] == 0) {
			commandBuffer[i] = 6;
			i = buffer_size;
		}
	}
	receive = 0;

	FL_QUIZ_ON = 1;

}

void settings() {
	if (!(PIN_KEY_SWITCH_IN)) {
		_delay_ms(5);
		if (!(PIN_KEY_SWITCH_IN)) {

			while (!sendCommand(com_clear_time_switch)) {
				_delay_ms(pause);

			}
			while (!receive) {
				receive = receiveCommand();
			}
			initSettings();
			while(1)
			{

			}
		}
	}

}
void switchOn() {
	if (receive == 3) {
		FL_automatOn = 1;
		SWITCH_ON_MACHINE_LOW;
		SCREEN_SWITCH_OUT_LOW;

		_delay_ms(1000);

		_delay_ms(2000);
		for (int i = 0; i < buffer_size; i++) {
			if (commandBuffer[i] == 0) {
				commandBuffer[i] = 6;
				i = buffer_size;
			}
		}

		receive = 0;

		FL_QUIZ_ON = 1;

	}
}
void endTime() {
	if (receive == 7) {
		receive = 0;
		PAYOUT_OUT_HIGH;

		_delay_ms(125);

		PAYOUT_OUT_LOW;
	}
}

void displaySwitch() {
	if (FL_automatOn) {
		if ((displayTimeout % 4) == 0) {
			switchTimeout++;
		}
		displayTimeout++;

		if ((switchTimeout >= 40000) && (FL_counter_in == 1)) {
			SCREEN_SWITCH_OUT_LOW;
			switchTimeout = 0;
			FL_display = 1;
		}

		if ((!(PIN_DISPLAY_CHANGE_BUTTON_IN)) && (switchTimeout > 1000)
				&& (FL_display == 1)) {
			SCREEN_SWITCH_OUT_LOW;
			switchTimeout = 0;
		}

		if ((!(PIN_DISPLAY_CHANGE_BUTTON_IN)) && (FL_counter_in == 0)) {
			_delay_ms(3);
			if ((!(PIN_DISPLAY_CHANGE_BUTTON_IN)) && (FL_counter_in == 0)) {
				SCREEN_SWITCH_OUT_LOW;
				switchTimeout = 0;
				FL_counter_in = 1;
			}
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
	creditsCoinAcceptorQuizomat();
	creditsBillAcceptorQuizomat();
	uint8_t commandlocal = 0, secondcommand = 0;
	if (!(PIN_READ_PI_IN)) {
		_delay_us(delayTime);
		if (!(PIN_READ_PI_IN)) {
			CONTROL_LOW;

			for (uint8_t i = 0; i < 21; i++) {
				_delay_us(delayTime);
				creditsCoinAcceptorQuizomat();
				creditsBillAcceptorQuizomat();

			}
			for (int i = 8; i >= 1; i = i / 2) {
				if ((PIN_READ_PI_IN)) {
					commandlocal += i;
				}
				_delay_ms(5);
			}
			creditsCoinAcceptorQuizomat();
			creditsBillAcceptorQuizomat();
			for (int i = 8; i >= 1; i = i / 2) {
				if ((PIN_READ_PI_IN)) {
					secondcommand += i;
				}
				_delay_ms(5);
			}
			creditsCoinAcceptorQuizomat();
			creditsBillAcceptorQuizomat();
		}
	}
	sendTimeCounter();
	if ((commandlocal == secondcommand) && (commandlocal)) {

		CONTROL_HIGH;
		for (uint8_t i = 0; i < 20; i++) {
			_delay_us(delayTime);
			creditsCoinAcceptorQuizomat();
			creditsBillAcceptorQuizomat();
		}

		return commandlocal;
	} else {

		return 0;
	}
}

