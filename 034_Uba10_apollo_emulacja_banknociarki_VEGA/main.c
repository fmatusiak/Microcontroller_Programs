#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"
#include <inttypes.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL // zegar w Hz
#define RS_BAUD 9600//
#define RS_UBRR 51

int main(void) {
	uint16_t i;
	DDR_rxs_we;
	rxs_we_VCC;
	DDR_IN6_IN;
	IN6_IN_VCC;
	DDR_txs;
	PORT_txs_1;
	DDR_puls;
	PORT_puls_0;

	uart_init(RS_UBRR);
	_delay_ms(4000);
	// coin acceptor
	init_device();
	while (1) {
		//===========================

		is_bill();


		//oddaj_kase();
		//stack_kas();
		//ESCROW_UNIT_STATUS();
	}
}

void is_bill(void) {
	if (check_acept()) {
		if (check_acept()) {
			request_status();
			request_status();
			while(check_Esc())
			{

			}
			request_status();
			KEEP();
			request_status();
			request_status();
			request_status();
			ACK();
			ESCROW_UNIT_STATUS();
			request_status();
			ACK();

		}
	}

}

bool check_Esc(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x11); // request sttusa
	put_crc(0x5627);
	uart_getc();
	uart_getc();
	if (uart_getc() == 0x13) {
		_delay_ms(100);
		uart_clear();
		return false;
	}

	_delay_ms(100);
	uart_clear();
	return true;
}


bool check_acept(void) {
	uint8_t tmp = 0 ;
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x11); // request sttusa
	put_crc(0x5627);
	uart_getc();
	uart_getc();
	tmp = uart_getc();
	if (tmp == 0x12) {
		_delay_ms(100);
		uart_clear();
		return true;
	}

	if (tmp == 0x74)
	{
		_delay_ms(100);
		ACK();
	}

	if 	(tmp == 0x15)
	{
		_delay_ms(100);
		ACK();
	}



	_delay_ms(100);
	uart_clear();
	return false;
}
void uart_clear(void)
{
	uint8_t flu;
	while ( UCSRA & (1<<RXC) )
	{
	flu = UDR;
	}
}


void check_is_bill(void) {
	request_status();
	request_status();
	uart_getc();
}

// FUNCTIONS

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

void uart_putc(uint8_t data) {
// Oczekiwanie na zakoñczenie nadawania
	while (!(UCSRA & (1 << UDRE)))
		;
// Wys³anie danych
	UDR = data;
}

uint8_t uart_ischar() {
// Czy w buforze s¹ dane?
	return (UCSRA & (1 << RXC));
}

uint8_t uart_getc() {
// Czy w buforze s¹ dane?
	int i = 0;
	while (!uart_ischar()) {
/*			if (i == 1000) {
		 _delay_us(1);
		 break;
		 }
		 i++;*/
	}

	return UDR;
}

void init_device(void) {
	request_status();
	request_status();
	request_status();
	version_request();
	EXT_version_request();
	Escrow_Limit_Reqest();
	Reset();
	request_status();
	Comunicaion_mode();
	Enable_disbale();
	Security();
	Escrow_Limit();
	Inhibit();
	request_status();
	request_status();

}

void stack_kas(void)
{
	request_status();

	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x41); // request sttusa
	put_crc(0x4A2 );
	_delay_ms(100);
	request_status();
	uart_getc();
	uart_getc();
	if 	(uart_getc() == 0x15)
	{
		ACK();
	}




	uart_clear();

}

void oddaj_kase(void)
{

	request_status();

	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x43); // request sttusa
	put_crc(0x27B0);
	_delay_ms(100);
	request_status();
	uart_getc();
	uart_getc();
	if 	(uart_getc() == 0x50)
	{
		ACK();
	}
	uart_clear();


	_delay_ms(100);
	request_status();

	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x47); // request sttusa
	put_crc(0x6194);
	_delay_ms(100);
	request_status();
	uart_getc();
	uart_getc();
	if 	(uart_getc() == 0x76)
	{
		ACK();
	}
	uart_clear();



}

void ESCROW_UNIT_STATUS(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x70); // request sttusa
	put_crc(0x24A8);
	_delay_ms(100);
}

void ACK(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x50); // request sttusa
	put_crc(0x05AA);
	_delay_ms(100);
}

void KEEP(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x46); // request sttusa
	put_crc(0x701D);
	_delay_ms(100);
}

void Stack(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x41); // request sttusa
	put_crc(0x4A2);
	_delay_ms(100);
}

void Inhibit(void) {
	uart_putc(0xFC);
	uart_putc(0x06);
	uart_putc(0xC3);
	uart_putc(0x00);
	put_crc(0xD604);
	_delay_ms(100);
}

void Escrow_Limit(void) {
	uart_putc(0xFC);
	uart_putc(0x06);
	uart_putc(0xCD);
	uart_putc(0x0A);
	put_crc(0xC2A);
	_delay_ms(100);
}

void Security(void) {
	uart_putc(0xFC);
	uart_putc(0x07);
	uart_putc(0xC1); // request sttusa
	uart_putc(0x00);
	uart_putc(0x00);
	put_crc(0xEFF1);
	_delay_ms(100);
}

void Enable_disbale(void) {
	uart_putc(0xFC);
	uart_putc(0x07);
	uart_putc(0xC0);
	uart_putc(0x0);
	uart_putc(0x0);

	put_crc(0xB52D);
	_delay_ms(100);
}

void Comunicaion_mode(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x82); // request sttusa
	put_crc(0xF035);
	_delay_ms(100);
}

void Escrow_Limit_Reqest(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x8D); // request sttusa
	put_crc(0x8C2);
	_delay_ms(100);
}

void Reset(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x40); // request sttusa
	put_crc(0x152B);
	_delay_ms(100);
}

void EXT_version_request(void) {
	uart_putc(0xFC);
	uart_putc(0x07);
	uart_putc(0x93); // request sttusa
	put_crc(0xC28D);

	_delay_ms(100);
}

void version_request(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x88); // request sttusa
	put_crc(0x5F6F);

	_delay_ms(100);
}

void request_status(void) {
	uart_putc(0xFC);
	uart_putc(0x05);
	uart_putc(0x11); // request sttusa
	put_crc(0x5627);
	_delay_ms(100);
}

void put_crc(uint16_t cc) {
	uart_putc(crc_1(cc));
	uart_putc(crc_2(cc));

}

uint8_t crc_1(uint16_t cc) {
	return cc - ((cc >> 8) << 8);
}

uint8_t crc_2(uint16_t cc) {
	return cc >> 8;
}

// === cctalk

