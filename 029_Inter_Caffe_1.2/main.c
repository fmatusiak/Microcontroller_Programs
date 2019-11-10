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

		receive = receiveCommand();
		if (FL_Caffe) {
			Caffe();

		}


		switchOn();


	}
}
void ioInit() {
//========== INS ========================
	_delay_ms(500);
	DDR_READ_PI_IN;
	DDR_CARD_IN;
	DDR_PAYOUT_IN;
	DDR_SETTINGS_IN;
	DDR_GIVEMONEY_IN;
	DDR_SETTINGS_AUTOMAT_IN;
	DDR_MOTOR_HOPPER_CONTROL_IN;
	DDR_PILOT_IN;
	DDR_KEY_SWITCH_IN;
	DDR_ON_MACHINE_IN;


	READ_PI_IN_VCC;
	CARD_IN_VCC;
	PAYOUT_IN_VCC;
	SETTINGS_IN_VCC;
	GIVEMONEY_IN_VCC;
	SETTINGS_AUTOMAT_IN_VCC;
	MOTOR_HOPPER_CONTROL_IN_VCC;
	PILOT_IN_VCC;
	KEY_SWITCH_IN_VCC;
	ON_MACHINE_IN_VCC;

//========= OUTS ========================
	SEND_PI_OUT_DDR;
	SETTINGS_AUTOMAT_OUT_DDR;
	HOPPER_PULS_OUT_DDR;
	PAYOUT_OUT_DDR;
	SCREEN_SWITCH_OUT_DDR;
	SWITCH_ON_MACHINE_DDR;
	ALARM_DDR;
	CONTROL_DDR;
	SETTINGS_AUTOMAT_REVERSE_OUT_DDR;

	SEND_PI_OUT_HIGH;
	SETTINGS_AUTOMAT_OUT_LOW;
	SETTINGS_AUTOMAT_REVERSE_OUT_HIGH;
	HOPPER_PULS_OUT_LOW;
	PAYOUT_OUT_LOW;
	SCREEN_SWITCH_OUT_LOW;
	SWITCH_ON_MACHINE_LOW;
	ALARM_LOW;
	CONTROL_LOW;


	_delay_ms(500);

}
void configurationInit() {
	buffer_size = 20;
	for (int i = 0; i < buffer_size; i++) {
		commandBuffer[i] = 0;
	}

	sended = 1, delayCounts = 1,CAFFE_ON = 0;
	FL_automatOn = 0, command = 0, pause = 20, receive = 0, FL_start = 0;
	FL_pilotes = 0, FLAGA_Send = 0,FL_Caffe = 0,FL_Nabij = 1,FL_Settings_automat = 1,FL_SA = 1,FL_Hopper_time = 0;

	com_caffe_on = 5, com_off_value = 10,com_start_automat = 3, com_disp = 7;
	com_caffe_is = 1,com_payout = 2,com_payout_button = 3,com_money_one = 4,com_money_two = 5,com_money_five = 6,com_money_ten = 7,com_key_switch = 8;
	com_nabijKredyt = 9, com_money_twenty = 10 , com_money_fifty = 11, com_money_hundred = 12;


	//////////Cafe


	FL_keySwitch = 0,FL_PAYOUT = 0,FL_START_PAYOUT = 0,FL_HOPPER = 0,money_pulses = 0 ,FL_Hopper_DOWN = 1,FL_Hopper_UP = 0;
	Tmp_time_payout = 0,Tmp_time_hopper_low = 1000,Tmp_time_hopper_high = 1000,time_hopper = 1000;



	initSettings();
	_delay_ms(100);

	if (!(PIN_PILOT_IN)) {
		FL_pilotes = 1;
	}

}

void initSettings() {
	CONTROL_HIGH;

	while (receive != com_off_value) {
		receive = receiveCommand();

		if (receive == com_caffe_on) {
			CAFFE_ON = 1;
		}

		if (CAFFE_ON) {
			command = com_caffe_is;
		}

	}

	FL_start = 1;
	receive = 0;
}


void switchOn() {
	if (receive == com_start_automat) {
		FL_automatOn = 1;
		FL_Caffe = 1;
		SWITCH_ON_MACHINE_HIGH;
		SCREEN_SWITCH_OUT_HIGH;
		while (delayCounts) {
			_delay_ms(1000);
			delayCounts -= 1;
			_delay_ms(2000);

			receive = 0;
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
	uint8_t commandlocal = 0, secondcommand = 0;
	if (!(PIN_READ_PI_IN)) {
		_delay_us(delayTime);
		if (!(PIN_READ_PI_IN)) {
			CONTROL_LOW;

			for (uint8_t i = 0; i < 21; i++) {
				_delay_us(delayTime);
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

