/*
 * main.c
 *      Author: Arek Trojanowski
 */

#include "main.h"
volatile uint16_t serca = 0, zezwolenie = 0, impcash = 0, tmpimp = 0,
		flaga_impcash = 0, tmp_licznik = 0, flagapayout = 0, flagalight = 0;

int main(void) {

	ioInit();

//======================== end cctalk banknociarka=======================================
	while (1) {

		if (!hotSpotOn) {

			settings();
			switchOn();
			jackpotCredits();
			//settings();
			//switchOn();
		} else {

			jackpotCredits();
			jackpotSwitch();
			settings();
			check_quiz_payout();
			turnOnRasp();
			check_light();
		}

	}
}
// UART

// FUNCTIONS DEFINITION

void ioInit() {
//INS
	DDR_IN1;
	IN1_VCC;

	DDR_IN2;
	IN2_VCC;

	IN3_25_PC6_DDR;
	IN3_25_PC6_VCC;

	IN4_26_PC7_DDR;
	IN4_26_PC7_VCC;

	DDR_IN5;
	IN5_VCC;

	HS_ON_OFF_36_PA1_DDR;
	HS_ON_OFF_36_PA1_GND;

	BARMAN_35_PA2_DDR;
	BARMAN_35_PA2_VCC;

	DOOR_34_PA3_DDR;
	DOOR_34_PA3_VCC;

	WE1_32_PA5_DDR; //STAC IN
	WE1_32_PA5_VCC;

	RX_DO_RP_41_PB1_DDR; // pi in
	RX_DO_RP_41_PB1_VCC;

	WE2_33_PA4_DDR;
	WE2_33_PA4_VCC;

	RX2_11_PD2_DDR;
	RX2_11_PD2_VCC;

// OUTS
	DDR_OUT1;
	PORT_OUT1_0;

	DDR_OUT2;
	PORT_OUT2_0;

	DDR_OUT3_21_PC2;
	OUT3_21_PC2_LOW;

	DDR_OUT4;
	PORT_OUT4_0;

	DDR_OUT5;
	PORT_OUT5_0;

	RASP_CREDIT_DDR;
	RASP_CREDIT_HIGH;

	TX_DO_RP_42_PB2_DDR; // rasp_conf
	TX_DO_RP_42_PB2_HIGH;

	WBA_RES_14_PD5_DDR;
	WBA_RES_14_PD5_LOW;

	WBA12V_15_PD6_DDR;
	WBA12V_15_PD6_HIGH;

	WBA_PRZE_13_PD4_DDR;
	WBA_PRZE_13_PD4_LOW;

	PRZEL_VGA_44_PB4_DDR;
	PRZEL_VGA_44_PB4_LOW;

	JP_SCREEN_SWITCH_PB5_DDR;
	JP_SCREEN_SWITCH_PB5_LOW;

	V12_OUT_16_PD7_DDR;
	V12_OUT_16_PD7_LOW;

	TX2_12_PD3_DDR;
	TX2_12_PD3_LOW;

}

void credits() {
}

void check_light() {
	if ((WE2_33_PA4_LOW) && (flagalight == 0)) //
			{
		_delay_ms(10);
		if (WE2_33_PA4_LOW) {
			flagalight = 10000;
			RASP_CREDIT_LOW;
			_delay_ms(100);
		}
		RASP_CREDIT_HIGH;

	} else {
		if (flagalight) {
			flagalight -= 1;
		}
		_delay_ms(1);
		RASP_CREDIT_HIGH;
	}
	RASP_CREDIT_HIGH;

}

void turnOnRasp() {
	if ((BARMAN_35_PA2_LOW)) {
		_delay_ms(5);
		if (BARMAN_35_PA2_LOW) {

			WBA_PRZE_13_PD4_LOW;
			WBA_RES_14_PD5_LOW;
			WBA12V_15_PD6_HIGH;
			PRZEL_VGA_44_PB4_LOW;
			RASP_CREDIT_LOW;
			JP_SCREEN_SWITCH_PB5_LOW;
		}
	}
}

void check_quiz_payout() {
	if(FL_settings == 0)
	{
	if (RX_DO_RP_41_PB1_HIGH) {
		if (IN4_26_PC7_LOW) {
			_delay_ms(2);
			if (IN4_26_PC7_LOW) {
				PORT_OUT4_1;
			} else {
				PORT_OUT4_0;
			}
		}
	} else {
		PORT_OUT4_0;
	}
}}

void settings() {

	if (WE1_32_PA5_LOW) {
		FL_settings = 1;
		TX_DO_RP_42_PB2_LOW;
		if (IN4_26_PC7_LOW) {
					_delay_ms(2);
					if (IN4_26_PC7_LOW) {
						PORT_OUT4_1;
					} else {
						PORT_OUT4_0;
					}
				}

	} else {
		FL_settings = 0;
		TX_DO_RP_42_PB2_HIGH;
	}
	if ((RX_DO_RP_41_PB1_LOW && (hotSpotOn))) {
		V12_OUT_16_PD7_HIGH;
	} else {
		V12_OUT_16_PD7_LOW;
	}
}

void switchOn() {
	if (RX_DO_RP_41_PB1_LOW && !hotSpotOn) {
		_delay_ms(5);
		if (RX_DO_RP_41_PB1_LOW) {
			hotSpotOn = 1;

			WBA_PRZE_13_PD4_HIGH;
			WBA_RES_14_PD5_HIGH;
			WBA12V_15_PD6_LOW;
			PRZEL_VGA_44_PB4_HIGH;

			JP_SCREEN_SWITCH_PB5_HIGH;
			RASP_CREDIT_LOW;
			_delay_ms(1000);
			WBA12V_15_PD6_HIGH;

			_delay_ms(5000);


			JP_SCREEN_SWITCH_PB5_LOW;
			RASP_CREDIT_HIGH;
			zezwolenie = 0;
		}
	}
}

void jackpotCredits() {

	if (serca) {
		RASP_CREDIT_LOW;
		_delay_ms(CREDIT_DELAY);
		RASP_CREDIT_HIGH;
		_delay_ms(CREDIT_DELAY);

		serca = serca - 5;
	}

	if ((!(PIN_IN1)) && !hotSpotOn) {
		serca = serca + 5;
	}
	if ((!(PIN_IN1)) && hotSpotOn) {

		if (PIN_IN5) {
			while (!(PIN_IN1)) {
				PORT_OUT1_1;
				//RASP_CREDIT_LOW;
				JP_SCREEN_SWITCH_PB5_LOW;
				zezwolenie = 1;
			}

		} else {
			TX_DO_RP_42_PB2_LOW;
			_delay_ms(CREDIT_DELAY);
			TX_DO_RP_42_PB2_HIGH;
		}
		PORT_OUT1_0;
		RASP_CREDIT_HIGH;

	}

	if ((!(PIN_IN2)) && (!hotSpotOn)) {
		serca = serca + 10;
	}
	if ((!(PIN_IN2)) && hotSpotOn) {

		if (PIN_IN5) {
			while (!(PIN_IN2)) {
				PORT_OUT2_1;
				RASP_CREDIT_LOW;
				JP_SCREEN_SWITCH_PB5_LOW;
			}
		} else {
			TX_DO_RP_42_PB2_LOW;
			_delay_ms(CREDIT_DELAY);
			TX_DO_RP_42_PB2_HIGH;
		}
		PORT_OUT2_0;
		RASP_CREDIT_HIGH;

	}
}

void jackpotSwitch() {
	if (IN3_25_PC6_LOW) {
		_delay_ms(5);
		if (IN3_25_PC6_LOW) {
		}
		jackpot = 0;
	}

	if (!jackpot && (IN3_25_PC6_HIGH))
		JP_SCREEN_SWITCH_PB5_Z;
	jackpot = 1;
}

uint8_t uartIsChar() {
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc() {
// Czy w buforze s¹ dane?
	int i = 0;
	while (!uartIsChar()) {
		/*i++;
		 if (i == 5000) {
		 i = 0;
		 break;
		 //	UDR = 0;
		 }*/

	}
	i = 0;
// Dane z bufora
	return UDR;
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

void uart_init(uint16_t ubrr) {
// Ustawienie prêdkoœci transmisji
	UBRRH = (uint8_t) (ubrr >> 8);
	UBRRL = (uint8_t) ubrr;

// W³¹czenie nadajnika i odbiornika
	UCSRB = (1 << RXEN) | (1 << TXEN);

// Ustawienie formatu ramki:
// 8 bitów danych, 1 b it stopu, even bit
	UCSRC = (1 << URSEL) | (3 << UCSZ0) | (1 << UPM1);
}
