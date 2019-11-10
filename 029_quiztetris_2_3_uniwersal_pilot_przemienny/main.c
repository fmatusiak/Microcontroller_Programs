#include "main.h"

// GLOBAL VARIABLES

int main(void) {
	ioInit();

	configurationInit();

	while (1) {
		if (sended) {
			for (int i = 0; i < buffer_size; i++) {
				if (commandBuffer[i] != 0) {
					command = commandBuffer[i];
					commandBuffer[i] = 0;
					i = buffer_size;
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
		if (FL_TETRIS_ON) {
			tetris();
		}
		if (FL_QUIZ_ON) {
			quizomat();
			displaySwitch();
			endTime();
		} else if (QUIZ_ON) {
			quizomat();

		}
		switchOnCard();
		switchOn();
		switchOnPi();

	}
}
void ioInit() {
//========== INS ========================
	_delay_ms(1000);
	DDR_COIN_ACCEPTOR_IN;
	DDR_COIN_ACCEPTOR_IN;
	DDR_DISPLAY_CHANGE_BUTTON_IN;
	DDR_PAYOUT_BUTTON_IN;
	DDR_PROTECTION_IN;
	DDR_PILOT_IN;
	DDR_KEY_SWITCH_IN;
	DDR_COUNTER_IN;
	DDR_ON_MACHINE_IN;
	DDR_READ_PI_IN;

	COIN_ACCEPTOR_IN_VCC;
	COIN_ACCEPTOR_IN_VCC;
	DISPLAY_CHANGE_BUTTON_IN_VCC;
	PAYOUT_BUTTON_IN_VCC;
	PROTECTION_IN_VCC;
	PILOT_IN_VCC;
	KEY_SWITCH_IN_VCC;
	COUNTER_IN_VCC;
	ON_MACHINE_IN_VCC;
	READ_PI_IN_VCC;

//========= OUTS ========================
	COIN_ACCEPTOR_OUT_DDR;
	BILL_ACCEPTOR_OUT_DDR;
	PAYOUT_OUT_DDR;
	START_OUT_DDR;
	SCREEN_SWITCH_OUT_DDR;
	SWITCH_ON_MACHINE_DDR;
	SEND_PI_OUT_DDR;
	ALARM_DDR;

	COIN_ACCEPTOR_OUT_LOW;
	BILL_ACCEPTOR_OUT_LOW;
	PAYOUT_OUT_LOW;
	START_OUT_LOW;
	SCREEN_SWITCH_OUT_LOW;
	SWITCH_ON_MACHINE_LOW;
	SEND_PI_OUT_HIGH;
	ALARM_LOW;


	_delay_ms(1000);

}
void configurationInit() {
	buffer_size = 10;
	for (int i = 0; i < buffer_size; i++) {
		commandBuffer[i] = 0;
	}
	// commands quiz sended
	sended = 1, com_counter_start = 11, com_counter_stop = 12, com_attack = 13, com_clear_time_switch =
			14, com_switch_on_tetris = 7, com_on_automat = 3, com_switch_on = 8, com_quiz_start_rules =
			3, com_quiz_on = 6;
	// commands quiz received
	com_round = 11, com_lock_pay = 12, com_unlock_pay = 13, com_quiz_on = 6;
	// commands tetris
	com_send_hearts = 11, counter_pulses = 0, counter_off = 10000;
	toLong = 10000, switchTimeout = 0;
	TETRIS_ON = 0, QUIZ_ON = 0, JACKPOT_ON = 0, PROT_ON = 0, FL_TETRIS_ON = 1, FL_pilot =
			1, FL_QUIZ_ON = 0;
	delayCounts = 1, counterTimeout = 0;
	FL_counter = 1, FL_automatOn = 0, FL_display_switch = 0, FL_settingsQuiz =
			1, FL_settingsTetris = 1, command = 0, pause = 20, receive = 0;
	FL_keySwitch = 1, FL_display = 0, FL_start = 0;
	;
	tmp_tetris = 1, tmp_quiz = 1, startTimeout = 0, startImpulseTime = 4000;
	FL_protection = 0, displayTimeout = 1000, FL_CARD = 1, FL_start_rules = 1, FL_counter_in =
			0, counterTimeout_counter = 0,FL_pilotes= 0;

	initSettings();
	settings();
	_delay_ms(100);
	if (!(PIN_PILOT_IN)) {
FL_pilotes =1;
	}
}

void initSettings() {
	while (receive != 10) {

		if (receive == 5) {
			QUIZ_ON = 1;

		}
		if (receive == 4) {
			TETRIS_ON = 1;
			FL_TETRIS_ON = 1;
		}

		if (receive == 6) {
			JACKPOT_ON = 1;
		}
		if (receive == 7) {
			PROT_ON = 1;
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

		receive = receiveCommand();
	}
	FL_start = 1;
	receive = 0;
}
void switchOnPi() {
	if (((PIN_PILOT_IN) && FL_pilotes && FL_pilot)|| ((!(PIN_PILOT_IN)) && (FL_pilotes == 0) && FL_pilot)) {
		_delay_ms(2);
		if (((PIN_PILOT_IN) && FL_pilotes && FL_pilot)|| ((!(PIN_PILOT_IN)) && (FL_pilotes == 0) && FL_pilot)) {
			FL_pilot = 0;
			SCREEN_SWITCH_OUT_LOW;
			SWITCH_ON_MACHINE_LOW;
			if (TETRIS_ON == 0) {
				FL_TETRIS_ON = 0;
				FL_QUIZ_ON = 1;
			} else {
				FL_TETRIS_ON = 1;
				FL_QUIZ_ON = 0;
			}

			if ((TETRIS_ON)) {
				for (int i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = com_switch_on_tetris;
						i = buffer_size;
					}
				}
			}
			if ((TETRIS_ON == 0) && (QUIZ_ON == 1)) {
				for (int i = 0; i < buffer_size; i++) {
					if (commandBuffer[i] == 0) {
						commandBuffer[i] = 6;
						i = buffer_size;
					}
				}
			}

		}
	}
}

void settings() {
	if ((!(PIN_KEY_SWITCH_IN)) && (!FL_automatOn)) {

		while (!sendCommand(com_clear_time_switch)) {
			_delay_ms(pause);

		}
		while (!receive) {
			receive = receiveCommand();
		}
		initSettings();
	}
}
void switchOn() {
	if (receive == 3) {
		FL_automatOn = 1;
		SWITCH_ON_MACHINE_HIGH;
		SCREEN_SWITCH_OUT_HIGH;
		while (delayCounts) {
			_delay_ms(1000);
			delayCounts -= 1;

			_delay_ms(2000);
			while (!sendCommand(6)) {
				_delay_ms(40);
			}

			receive = 0;
			FL_TETRIS_ON = 0;
			FL_QUIZ_ON = 1;
		}
	}
}
void endTime() {
	if (receive == 7) {
		receive = 0;
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
			SWITCH_ON_MACHINE_HIGH;
			SCREEN_SWITCH_OUT_HIGH;
			while (delayCounts) {
				_delay_ms(1000);
				delayCounts -= 1;
			}
			_delay_ms(2000);
			while (!sendCommand(6)) {
				_delay_ms(40);
			}

			receive = 0;
			FL_TETRIS_ON = 0;
			FL_QUIZ_ON = 1;
		}

	}
}

void displaySwitch() {

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
		SCREEN_SWITCH_OUT_HIGH;
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

int sendCommand(uint8_t command) {
	if (PIN_READ_PI_IN) {
		uint8_t secondCommand;
		secondCommand = command;

		SEND_PI_OUT_LOW;
		for (int i = 0; i < 20; i++) {
			_delay_us(990);

			if (((command != com_switch_on_tetris) || (command != com_quiz_on))) {
				sendTimeCounter();
				sendTimeBill();
			}
		}
		for (int i = 8; i >= 1; i = i / 2) {
			if (command >= i) {
				SEND_PI_OUT_HIGH;
				command -= i;

			} else {
				SEND_PI_OUT_LOW;
			}
			for (int i = 0; i < 5; i++) {
				_delay_us(990);

			}
		}
		if (((command != com_switch_on_tetris) || (command != com_quiz_on))) {
			sendTimeCounter();
			sendTimeBill();
		}
		for (int i = 8; i >= 1; i = i / 2) {
			if (secondCommand >= i) {
				SEND_PI_OUT_HIGH;
				secondCommand -= i;

			} else {
				SEND_PI_OUT_LOW;
			}
			for (int i = 0; i < 5; i++) {
				_delay_us(990);

				if (((command != com_switch_on_tetris)
						|| (command != com_quiz_on))) {
					sendTimeCounter();
					sendTimeBill();
				}
			}
		}

		SEND_PI_OUT_HIGH;
		for (int i = 0; i < 15; i++) {
			_delay_us(990);

			if (((command != com_switch_on_tetris) || (command != com_quiz_on))) {
				sendTimeCounter();
				sendTimeBill();
			}
		}
		if (!(PIN_READ_PI_IN)) {
			while (!(PIN_READ_PI_IN)) {
			}
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

uint8_t receiveCommand() {

	uint8_t commandlocal = 0, secondcommand = 0;
	if (!(PIN_READ_PI_IN)) {
		_delay_ms(2);

		if (!(PIN_READ_PI_IN)) {
			for (int i = 0; i < 20; i++) {
				_delay_ms(1);
				if (FL_start) {
					sendTimeCounter();
					sendTimeBill();
				}
			}
			for (int i = 8; i >= 1; i = i / 2) {
				if ((PIN_READ_PI_IN)) {
					commandlocal += i;
				}
				for (int i = 0; i < 5; i++) {
					_delay_ms(1);
					if (FL_start) {
						sendTimeCounter();
						sendTimeBill();
					}

				}
			}

			for (int i = 8; i >= 1; i = i / 2) {
				if ((PIN_READ_PI_IN)) {
					secondcommand += i;
				}
				for (int i = 0; i < 5; i++) {
					_delay_ms(1);

					if (FL_start) {
						sendTimeCounter();
						sendTimeBill();
					}
				}
			}

		}
	}
	if ((commandlocal == secondcommand) && (commandlocal)) {
		SEND_PI_OUT_LOW;
		for (int i = 0; i < 20; i++) {
			_delay_ms(1);

			if (FL_start) {
				sendTimeCounter();
				sendTimeBill();
			}
		}
		SEND_PI_OUT_HIGH;

		return commandlocal;
	} else {

		return 0;
	}
}

/* wejscia
 licznik
 przycisk zmiana ekranu
 stacyjka
 kanal wrzutnik
 kanal do zabezpieczenia
 pilot
 banknociarka_we
 wejscie na zalaczenie automatu
 */
/* wyjscia
 wyjscie wyplata
 wyjscie start
 wyjscie pulse wrzutnik
 wyjscie puls banknociarka
 wyjscie ekran switch
 */
/*
 *
 * ========== wysylanie ========
 * quiz
 * 11. licznik start
 * 12. licznik stop
 * 1-10	liczbik wartosc
 * 13. atak
 * 14 kasuj czas (stacyjka)
 * 17 przelacz na tetris
 *
 * tetris wysylanie
 * 11. serca start
 *
 *
 * start atmega
 * 14. ustawienia(stacyjka)
 *================================
 *
 * Komendy odbierane:
 * 12. zablokuj wyplata
 * 13. odblokuj wyplata
 * 11. zakrec
 *
 * tetris
 * 1.wlacz
 *
 * start atmega
 * 1. wlacz tetris
 * 2. wlacz quiz
 * 3. wlacz jackpot
 * 4. wlacz zab
 * 5. czas
 * 1 - 14  && != 10 przedzial
 *
 *10. Puste
 */
