#include "main.h"

// GLOBAL VARIABLES

void uart_init(uint16_t ubrr);

void uart_putc(uint8_t data);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);


volatile uint8_t A = 0,B = 0,C = 0,D = 0;
volatile uint8_t CheckSumA = 0,CheckSumB = 0;
volatile uint16_t CheckSum,CheckSumX,CheckSumZ;


int main(void) {

	ioInit();

	uart_init(RS_UBRR);


	while (1) {

		A = uart_getc();
		B = uart_getc();
		C = uart_getc();
		D = uart_getc();



		CheckSum = (((((A*C)%D)+B)%((((A+B)%B)+C) + ((B*C)% A)))*333);
		CheckSum = CheckSum ^ 35011;

		CheckSumA = CheckSum >> 8;
		CheckSumB = CheckSum;


		uart_putc(CheckSumA);
		uart_putc(CheckSumB);
	}

}






void ioInit(void) {
//========== INS ========================
	_delay_ms(500);
//IN
	DDR_IN1_PA3;
	DDR_IN2_PA2;
	DDR_IN3_PA1;
	DDR_IN4_PA0;
	DDR_IN5_PA4;
	DDR_IN6_PC3;
	DDR_IN7_PC2;
	DDR_IN8_PC1;
	DDR_IN9_PC0;
	DDR_IN10_PB4;
	//DDR_RX_PD0;
	DDR_MOSI_PB5;
	DDR_SCK_PB7;
	DDR_TEST_POINT_PB6;

	IN1_PA3_VCC;
	IN2_PA2_VCC;
	IN3_PA1_VCC;
	IN4_PA0_VCC;
	IN5_PA4_VCC;
	IN6_PC3_VCC;
	IN7_PC2_VCC;
	IN8_PC1_VCC;
	IN9_PC0_VCC;
	IN10_PB4_VCC;
	//RX_PD0_VCC;
	MOSI_PB5_VCC;
	SCK_PB7_VCC;
	TEST_POINT_PB6_VCC;
/////////////
	//TX_PD1_DDR;
	MISO_PB6_DDR;
	OUT1_PC6_DDR;
	OUT2_PC7_DDR;
	OUT3_PA7_DDR;
	OUT4_PA6_DDR;
	OUT5_PA5_DDR;
	OUT6_PC5_DDR;
	OUT7_PD7_DDR;
	OUT8_PD6_DDR;
	OUT9_PD5_DDR;
	VGA_SWITCH_PD4_DDR;
	RELAY_ONE_PB2_DDR;
	RELAY_TWO_PD2_DDR;
	MUTE_PC4_DDR;
	ALARM_12V_PD3_DDR;

	//TX_PD1_LOW;
	MISO_PB6_LOW;
	OUT1_PC6_LOW;
	OUT2_PC7_LOW;
	OUT3_PA7_LOW;
	OUT4_PA6_LOW;
	OUT5_PA5_LOW;
	OUT6_PC5_LOW;
	OUT7_PD7_LOW;
	OUT8_PD6_LOW;
	OUT9_PD5_LOW;

	VGA_SWITCH_PD4_LOW;
	RELAY_ONE_PB2_LOW;
	RELAY_TWO_PD2_LOW;
	MUTE_PC4_HIGH;
	ALARM_12V_PD3_LOW;

	_delay_ms(500);

}

void uart_init(uint16_t ubrr) {
// Ustawienie prêdkoœci transmisji
	UBRRH = (uint8_t) (ubrr >> 8);
	UBRRL = (uint8_t) ubrr;

// W³¹czenie nadajnika i odbiornika
	UCSRB = (1 << RXEN) | (1 << TXEN);

// Ustawienie formatu ramki:
// 8 bitów danych, 1 b it stopu, brak parzystoœci
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

void uart_putc(uint8_t data) {
	// Oczekiwanie na zakoñczenie nadawania
	while (!(UCSRA & (1 << UDRE)))
		;

	// Wys³anie danych
	UDR = data;
}
//
uint8_t uart_ischar(void) {
	// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc(void) {
	// Czy w buforze s¹ dane?
	while (!uart_ischar())
		;

	// Dane z bufora
	return UDR;
}
