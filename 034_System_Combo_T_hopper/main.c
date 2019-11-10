#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "main.h"
#include "HD44780.h"

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

void uart_init(uint16_t ubrr);
void uart_putc(uint8_t data);
void uartPut(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,
		uint8_t *data);
uint8_t uart_getc(void);
uint8_t uart_ischar(void);
int main(void) {

	uart_init(RS_UBRR);

	uint8_t i, j, buffers[20];
	uint8_t Data1, Data2, Data3;
	for(i = 0; i < 20 ;i++)
	{
		buffers[i] = 0;
	}

	uartPut(6, 1, 1, 164, (uint8_t[] ) { 165 }); //Aktywny
	_delay_ms(100);

	uartPut(6, 0, 1, 242, (uint8_t[] ) { 0 }); //Aktywny

	for (j = 0; j < 8; j++) {
		buffers[j] = uart_getc();
	}
	_delay_ms(100);
	Data1 = buffers[10];
	Data2 = buffers[11];
	Data3 = buffers[12];
	uartPut(6, 0, 1, 236, (uint8_t[] ) {0 }); //wyplac monete
	_delay_ms(100);

	uartPut(6, 4, 1, 167, (uint8_t[] ) { 110, 53, 26, 50 }); //wyplac monete
	for (j = 0; j < 5; j++) {
		buffers[j] = uart_getc();
	}
	_delay_ms(100);

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

uint8_t uart_ischar(void) {
	// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc(void) {
	// Czy w buforze s¹ dane?'
	uint8_t timie_out = 1;
	while ((!uart_ischar()) && timie_out) {
		timie_out++;

		if (timie_out >= 10000)
			timie_out = 0;

	};

	return UDR;
}

void uartPut(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,
		uint8_t *data) {
	uart_putc(from);
	uart_putc(dataCount);
	uart_putc(to);
	uart_putc(command);
	uint8_t checkSum = from + to + command + dataCount;
	for (int i = 0; i < dataCount; i++) {
		uart_putc(data[i]);
		checkSum += data[i];
	}

	checkSum %= 256;
	checkSum = 256 - checkSum;

	uart_putc(checkSum);
}

void gpioInit() {

	DDR_BUTTON1_IN;
	DDR_BUTTON2_IN;
	DDR_SWITCH_IN;
	DDR_COIN1_IN;
	DDR_COIN2_IN;
	DDR_HOPPERON1_OUT;
	DDR_HOPPERON2_OUT;
	PORT_HOPPERON1_OUT_1;
	PORT_HOPPERON2_OUT_1;
	SWITCH_IN_VCC;
	BUTTON1_IN_VCC;
	BUTTON2_IN_VCC;

}

