/*
 * main.c
 *
 *  Created on: 23 mar 2015
 *      Author: Arek Trojanowski

 */

#include "main.h"
#define F_CPU 16000000UL
volatile int starter = 0, c = 0, cctalkwrz = 0, cctalkban = 0;
volatile uint16_t ban = 0, dopelnienie = 12, wrz = 0, zmienna = 0, d = 0, stop =
		0, zmiennaw = 0, dw = 0, stopw = 0, dw2 = 256, i;
volatile uint16_t serca = 0, FL_CARD = 1, FL_CARD_Automat = 0, FL_RUN = 0;
int znak = 0, FL_ser = 0, FL_ser2 = 0;

volatile uint16_t buffer[21], bufferOld[21], bank = 0, event = -1, firstRun = 1;
volatile uint16_t min = 1, ebaban = 0;
volatile uint16_t bufferC[21], bufferOldC[21], bankC = 0, eventC = -1,
		firstRunC = 1;
int bufferEq(void);
int bufferEqC() {
	int bufferEqC = -1;
	int i;
	if (firstRunC == 1)
		return 1;
	for (i = 10; i < 18; i++) {
		if (bufferC[i + 2] == bufferOldC[i]) {
			bufferEqC = 1;
		} else {
			bufferEqC = -1;
			break;
		}
	}
	return bufferEqC;
}
int main(void) {

	RASP_CONF_DDR;
	RASP_CONF_HIGH;
	RASP_CREDIT_DDR;
	RASP_CREDIT_HIGH;
	DDR_PILOT_IN;
	PILOT_IN_VCC;
	ON_MACHINE_IN_VCC;

	DDR_CARD_IN;
	CARD_IN_VCC;
	DDR_ON_MACHINE_IN;

	DDR_IN1;
	IN1_VCC;

	DDR_RX;
	RX_VCC;

	DDR_IN2;
	IN2_VCC;

	DDR_IN3;
	IN3_VCC;

	DDR_IN4;
	IN4_VCC;

	DDR_IN5;
	IN5_VCC;

	STAC_IN_DDR;
	STAC_IN_VCC;

	PI_IN_DDR;
	PI_IN_VCC;

	DWA_DDR;
	DWA_VCC;

	DDR_OUT1;
	PORT_OUT1_0;

	DDR_OUT2;
	PORT_OUT2_0;

	DDR_OUT3;
	PORT_OUT3_0;

	DDR_OUT4;
	PORT_OUT4_0;

	DDR_OUT4;
	PORT_OUT4_0;

	DDR_OUT5;
	PORT_OUT5_0;

	V12_DDR;
	V12_LOW;
	WBA_V12_DDR;
	WBA_V12_HIGH;
	WBA_RESET_DDR;
	WBA_RESET_LOW;
	WBA_SWITCH_DDR;
	WBA_SWITCH_LOW; // low na high
	//BUTTONS_DDR;
	//BUTTONS_LOW;
	VGA_SWITCH_DDR;
	VGA_SWITCH_LOW;

	// TIMER0

	// UART

	UBRRH = (uint8_t) (RS_UBRR >> 8);
	UBRRL = (uint8_t) RS_UBRR;
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (3 << UCSZ0);

	//======================
	_delay_ms(3000);

	// koniec wrzutnik
	//========================= wrzutnik cctalk =============================

	// ==========================wrzutnik cctalk end ==========================

//======================== end cctalk banknociarka=======================================
	while (1) {

		if (!(PIN_IN1)) {
			if (!(PIN_IN5)) {
				PORT_OUT1_0;
			} else {
				PORT_OUT1_1;

				if (hotSpotOn == 0)
					FL_ser = 1;
			}

		}
		if (PIN_IN1) {
			PORT_OUT1_0;
			if (FL_ser == 1) {
				serca = serca + 5;
				FL_ser = 0;
			}
		}
		if (!(PIN_IN2)) {
			if (!(PIN_IN5)) {
				PORT_OUT2_0;
			} else {
				PORT_OUT2_1;
				if (hotSpotOn == 0)
					FL_ser2 = 1;
			}

		}
		if (PIN_IN2) {
			PORT_OUT2_0;
			if (FL_ser2 == 1) {
				serca = serca + 10;
				FL_ser2 = 0;
			}
		}

// =================================================

		if (STAC_IN_LOW) {
			znak = znak + 1;

		} else {
			znak = 0;

		}
		if (znak > 5) {
			znak = 5;
			RASP_CONF_LOW;
		} else {
			RASP_CONF_HIGH;
		}
// ============================wejscie wrzutnik i banknocarka  ===================================================
		if (serca) {
			RASP_CREDIT_LOW;
			_delay_ms(CREDIT_DELAY);
			RASP_CREDIT_HIGH;
			_delay_ms(CREDIT_DELAY);

			serca = serca - 5;
		}

// =========================== niski stan P1 hotspot ===============================

		if (((PI_IN_LOW) && !hotSpotOn) && (!FL_RUN)) {
			_delay_ms(5);
			if ((PI_IN_LOW)) {
				hotSpotOn = 1;
				FL_RUN = 1;
				VGA_SWITCH_HIGH;
				WBA_SWITCH_HIGH;
				WBA_RESET_HIGH;
				WBA_V12_LOW;
				_delay_ms(1000);
				WBA_V12_HIGH;
			}
		}
		if ((!(PIN_CARD_IN)) && (FL_CARD) && (!FL_RUN)) {
			_delay_ms(5);
			if (!(PIN_CARD_IN)) {
				FL_CARD_Automat = 1;
				FL_RUN = 1;
				hotSpotOn = 1;
				FL_CARD = 0;
				VGA_SWITCH_HIGH;
				WBA_SWITCH_HIGH;
				WBA_RESET_HIGH;
				WBA_V12_LOW;
				_delay_ms(1000);
				WBA_V12_HIGH;

			}
		}
		if ((FL_RUN) && (!(FL_CARD_Automat)) && (!(PIN_CARD_IN))) {
			_delay_ms(5);
			if (!(PIN_CARD_IN)) {
				FL_CARD_Automat = 1;
			}

		}

		if ((PIN_CARD_IN) && (FL_CARD_Automat)) {
			_delay_ms(5);
			if ((PIN_CARD_IN) && (FL_CARD_Automat)) {
				turnOnRasp();
			}
		}

// =========================== wysoki stan P1 tetris ===============================

		if (!(PIN_PILOT_IN)) {
			_delay_ms(5);
			if (!(PIN_PILOT_IN)) {
				turnOnRasp();
			}
		}

// =========================== otwarcie drzwi ==============================

		// UART
	}
}

// FUNCTIONS DEFINITION

void turnOnRasp() {
	_delay_ms(1000);

//V12_HIGH;
	VGA_SWITCH_LOW;
	BUTTONS_LOW;
	WBA_SWITCH_LOW;
	WBA_RESET_LOW;
	FL_CARD_Automat = 0;
	WBA_V12_LOW;
	_delay_ms(1000);
	WBA_V12_HIGH;

	hotSpotOn = 0;
}

void sendDataFrame() {
	uint8_t ones = 0;
	for (int i = 12; i >= 0; i--) {
		if (i == 1) {
			if (ones % 2 == 0) {
				dataFrame[1] = 0;
			} else {
				dataFrame[1] = 1;
			}
		}
		if (dataFrame[i] == 0) {
			RASP_CONF_LOW;
		} else {
			RASP_CONF_HIGH;
			if (i > 1)
				ones++;
		}
		_delay_ms(BIT_DELAY);
	}
	_delay_ms(FRAME_DELAY);
}

void addRaspCredits(uint8_t count) {
	for (uint8_t i = 0; i < count; i = i + 5) {
		RASP_CREDIT_LOW;
		_delay_ms(CREDIT_DELAY);
		RASP_CREDIT_HIGH;
		_delay_ms(CREDIT_DELAY);
	}
}

void addHsCredits(uint8_t count) {
	for (uint8_t i = 0; i < count; i = i + 5) {
		PORT_OUT1_1;
		_delay_ms(CREDITHS_DELAY);
		PORT_OUT1_0;
		_delay_ms(CREDITHS_DELAY);
	}
}

uint16_t adcConversion(uint8_t PIN) {
	if (PIN == 0) { // ADC6
		ADMUX = 0x06;
	} else if (PIN == 1) { // ADC7
		ADMUX = 0x07;

	}
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC))
		;
	return ADCW;
}

uint8_t potxConversion(uint16_t adcResult) {
	if ((adcResult < tempxResult - 10) || (adcResult > tempxResult + 10)) {
		tempxResult = adcResult;
	} else {
		adcResult = tempxResult;
	}
	uint8_t potxResult = (adcResult / 204) + 1; // 200 ZAMIAST 204

	return potxResult > 5 ? 5 : potxResult;
}

uint8_t potyConversion(uint16_t adcResult) {
	if ((adcResult < tempyResult - 10) || (adcResult > tempyResult + 10)) {
		tempyResult = adcResult;
	} else {
		adcResult = tempyResult;

	}
	uint8_t potyResult = (adcResult / 9) + 10; // 10 ZAMIAST 9
	return potyResult > 120 ? 120 : potyResult;
}

uint8_t uartIsChar() {
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc() {
// Czy w buforze s¹ dane?
	int i = 0;
	while (!uartIsChar()) {
		i++;
		if (i == 5000) {
			i = 0;
			break;
			//	UDR = 0;
		}

	}
	i = 0;
// Dane z bufora
	return UDR;
}

int bufferEq() {
	int bufferEq = -1;
	int i;
	if (firstRun == 1)
		return 1;
	for (i = 10; i < 18; i++) {
		if (buffer[i + 2] == bufferOld[i]) {
			bufferEq = 1;
		} else {
			bufferEq = -1;
			break;
		}
	}
	return bufferEq;
}

void uart_putc(uint8_t data) {
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = data;
}

void uartPutData(uint8_t dataCount, uint8_t *data) {
	for (int i = 0; i < dataCount; i++) {
		uart_putc(data[i]);
	}
}
