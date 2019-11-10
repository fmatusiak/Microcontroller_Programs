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

		switchOn();

		if ((receive != 3) && (receive != 7) && (receive != 9)
				&& (receive != 12) && (receive != 5) && (receive != 8)
				&& (receive != 10) && (receive != 13) && (receive != 11)) {
			receive = 0;
		}
	}
}
void ioInit(void) {
//========== INS ========================
	_delay_ms(500);

	DDR_READ_PI_IN;
	DDR_COIN_ACCEPTOR_IN;
	DDR_BILL_ACCEPTOR_IN;
	DDR_PROTECTION_IN;
	DDR_KEY_SWITCH_IN;

	READ_PI_IN_VCC;
	COIN_ACCEPTOR_IN_VCC;
	BILL_ACCEPTOR_IN_VCC;
	BILL_PROTECTION_IN_VCC;
	KEY_SWITCH_IN_VCC;

//========= OUTS ========================

	COIN_ACCEPTOR_OUT_DDR;
	BILL_ACCEPTOR_OUT_DDR;
	SEND_PI_OUT_DDR;
	PAYOUT_OUT_DDR;
	START_OUT_DDR;
	SCREEN_SWITCH_OUT_DDR;
	CONTROL_DDR;
	START_OUT_3_DDR;
	PAYOUT_OUT_4_DDR;

	COIN_ACCEPTOR_OUT_LOW;
	BILL_ACCEPTOR_OUT_LOW;
	SEND_PI_OUT_HIGH;
	PAYOUT_OUT_LOW;
	START_OUT_LOW;
	SCREEN_SWITCH_OUT_LOW;
	CONTROL_LOW;
	START_OUT_3_LOW;
	PAYOUT_OUT_4_LOW;
	_delay_ms(500);

}
void configurationInit(void) {
	buffer_size = 20;
	for (uint8_t i = 0; i < buffer_size; i++) {
		commandBuffer[i] = 0;
	}
	// commands quiz sended
	sended = 1, com_switch_on_tetris = 4;
	com_quiz_on = 3;

	Counter_IN_1 = 10;
	Counter_IN_2 = 11;
	Counter_IN_5 = 12;
	Counter_IN_10 = 13;
	Counter_IN_25 = 14;

	com_quiz_start_rules = 2;

	//send
	com_attack = 9;

	// commands quiz received

	com_round = 11;
	// commands tetris
	TETRIS_ON = 0, QUIZ_ON = 0, FL_TETRIS_ON = 1, FL_pilot = 1, FL_QUIZ_ON = 0;
	FL_automatOn = 0, command = 0, receive = 0;
	FL_keySwitch = 1;

	FLAGA_Send = 0;

	FL_protection = 0;
	FL_counter_pulses = 1;
	counter_pulses = 0;
	FL_start_rules_counter = 1;
	counterTimeout = 0;
	FL_start_rules_counter = 1;

	initSettings();

}

void switchOnCard(void) {

	FL_automatOn = 1;
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




void initSettings(void) {
	CONTROL_HIGH;

	while (receive != 11) {
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

	receive = 0;

}

void settings(void) {
	if (!(PIN_KEY_SWITCH_IN)) {
		_delay_ms(5);
		if (!(PIN_KEY_SWITCH_IN)) {

			while (!sendCommand(14)) {
				_delay_ms(20);

			}
			while (!receive) {
				receive = receiveCommand();
			}

			while(1)
			{

			}
		}
	}

}
void switchOn(void) {
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
void endTime(void) {
	if (receive == 7) {
		receive = 0;
		PAYOUT_OUT_HIGH;
		PAYOUT_OUT_4_HIGH;

		for (uint8_t obr = 0; obr < 250; obr++) {
			creditsCoinAcceptorQuizomat();
			creditsBillAcceptorQuizomat();
			_delay_ms(1);
		}

		PAYOUT_OUT_LOW;
		PAYOUT_OUT_4_LOW;
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

uint8_t receiveCommand(void) {
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
