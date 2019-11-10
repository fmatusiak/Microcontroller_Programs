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
int znak = 0;

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
		if ((!(PIN_IN1)) && !hotSpotOn) {
			serca = serca + 5;
		}
		if ((!(PIN_IN1)) && hotSpotOn) {

			while ((!(PIN_IN1)) && (PIN_IN5)) {
				PORT_OUT1_1;
			}
			PORT_OUT1_0;
		}

		if ((!(PIN_IN2)) && !hotSpotOn) {
			serca = serca + 10;
		}
		if ((!(PIN_IN2)) && hotSpotOn) {

			while ((!(PIN_IN1)) && (PIN_IN5)) {
				PORT_OUT2_1;
			}
			PORT_OUT2_0;
		}

		if (hotSpotOn == 0) {

			uart_putc(2);
			uart_putc(0);
			uart_putc(1); // STALA
			uart_putc(229);
			uart_putc(24);
			for (i = 0; i < 21; i++) {
				//	bufferC[i] = uart_getc();
				if (firstRunC == 1) {
					bufferOldC[i] = bufferC[i];
					firstRunC = 0;
				}
			}

			if (bufferC[10] == 1 || bufferC[10] == 2 || bufferC[10] == 3
					|| bufferC[10] == 4 || bufferC[10] == 5 || bufferC[10] == 6
					|| bufferC[10] == 7 || bufferC[10] == 8 || bufferC[10] == 9
					|| bufferC[10] == 10) {

				if (eventC != bufferC[9]) {
					eventC = bufferC[9];

					if (bufferC[11] == 1 && bufferEqC() == 1) {
						// PENDING CREDIT
						if (bufferC[10] == 1) {
							if (hotSpotOn == 0) {
								serca = serca + 5;
							}
							PORT_OUT2_1;
							_delay_ms(100);
							PORT_OUT2_0;
						}
						if (bufferC[10] == 2) {
							if (hotSpotOn == 0) {
								serca = serca + 5;
							}
							PORT_OUT2_1;
							_delay_ms(100);
							PORT_OUT2_0;
						}
						if (bufferC[10] == 3) {
							if (hotSpotOn == 0) {
								serca = serca + 5;
							}
							PORT_OUT2_1;
							_delay_ms(100);
							PORT_OUT2_0;

						}
						if (bufferC[10] == 4) {
							if (hotSpotOn == 0) {
								serca = serca + 5;
							}
							PORT_OUT2_1;
							_delay_ms(100);
							PORT_OUT2_0;
						}
						if (bufferC[10] == 5) {
							if (hotSpotOn == 0) {
								serca = serca + 5;
							}
							PORT_OUT2_1;
							_delay_ms(100);
							PORT_OUT2_0;
						}
						if (bufferC[10] == 6) {
							if (hotSpotOn == 0) {
								serca = serca + 5;
							}
							PORT_OUT2_1;
							_delay_ms(100);
							PORT_OUT2_0;

						}
						if (bufferC[10] == 7) {
							if (hotSpotOn == 0) {
								serca = serca + 5;
							}
							PORT_OUT2_1;
							_delay_ms(100);
							PORT_OUT2_0;
						}
						if (bufferC[10] == 8) {
							if (hotSpotOn == 0) {
								serca = serca + 5;
							}
							PORT_OUT2_1;
							_delay_ms(100);
							PORT_OUT2_0;
						}
						if (bufferC[10] == 9) {
							if (hotSpotOn == 0) {
								serca = serca + 5;
							}
							PORT_OUT2_1;
							_delay_ms(100);
							PORT_OUT2_0;

						}

					}
				}

			}
			for (i = 0; i < 21; i++) {
				bufferOldC[i] = bufferC[i];
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

	uart_putc(2);
	uart_putc(0);
	uart_putc(1); //1.simple poll
	uart_putc(254);
	uart_putc(255);
	_delay_ms(100);

	uart_putc(2);
	uart_putc(0);
	uart_putc(1); //2.equipment category
	uart_putc(245);
	uart_putc(8);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(0);
	uart_putc(1); //3. product code
	uart_putc(244);
	uart_putc(9);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(0);
	uart_putc(1); //4. build code
	uart_putc(192);
	uart_putc(61);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(0);
	uart_putc(1); //5. manufacturer id
	uart_putc(246);
	uart_putc(7);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(0);
	uart_putc(1); //6. serial number
	uart_putc(242);
	uart_putc(11);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(0);
	uart_putc(1); //7. sofware revision
	uart_putc(241);
	uart_putc(12);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(0);
	uart_putc(1); //8. comms revision
	uart_putc(4);
	uart_putc(249);
// =========================================
	_delay_ms(100);

	uart_putc(2);
	uart_putc(1);
	uart_putc(1); // coin id 1
	uart_putc(184);
	uart_putc(1);
	uart_putc(67);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(1);
	uart_putc(1); // coin id 2
	uart_putc(184);
	uart_putc(2);
	uart_putc(66);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(1);
	uart_putc(1); // coin id 3
	uart_putc(184);
	uart_putc(3);
	uart_putc(65);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(1);
	uart_putc(1); // coin id 4
	uart_putc(184);
	uart_putc(4);
	uart_putc(64);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(1);
	uart_putc(1); // coin id 5
	uart_putc(184);
	uart_putc(5);
	uart_putc(63);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(1);
	uart_putc(1); // coin id 6
	uart_putc(184);
	uart_putc(6);
	uart_putc(62);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(1);
	uart_putc(1); // coin id 7
	uart_putc(184);
	uart_putc(7);
	uart_putc(61);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(1);
	uart_putc(1); // coin id 8
	uart_putc(184);
	uart_putc(8);
	uart_putc(60);

	_delay_ms(100);

	uart_putc(2);
	uart_putc(2);
	uart_putc(1); // inhibit on
	uart_putc(231);
	uart_putc(255);
	uart_putc(255);
	uart_putc(22);

	_delay_ms(100);

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
