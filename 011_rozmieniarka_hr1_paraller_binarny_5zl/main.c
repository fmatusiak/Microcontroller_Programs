#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>
#include <avr/interrupt.h>
#include "main.h"

volatile uint8_t sec = 0, m = 0, startj = 0, startd = 0, startp = 0, swieci = 0;
volatile uint8_t p = 1, j = 0, pintka = 0;
volatile uint16_t min = 0, pom = 0, przerwa = 0, czas = 0, punkty = 0, licznik =
		0, time = 1600, punktyw = 0;

volatile uint16_t jedynkalimit = 11, dwojkalimit = 11, piatkalimit = 11, i = 0,
		stop = 0;

int main(void) {

	DDR_pierwszy_we;
	DDR_drugi_we;
	DDR_trzeci_we;
	DDR_czwarty_we;
	DDR_piaty_we;

	DDR_hopper_we;

	pierwszy_we_VCC;
	drugi_we_VCC;
	trzeci_we_VCC;
	czwarty_we_VCC;
	piaty_we_VCC;

	hopper_we_GND;

	DDR_syrena_wy;
	PORT_syrena_wy_0;
	DDR_hopper_out;
	PORT_hopper_out_0;

	_delay_ms(1000);

	while (1) {

		// ================== alarm ==========================
		if (PIN_hopper_we) {
			PORT_syrena_wy_1;
		} else {
			PORT_syrena_wy_0;
		}

		// ====================================================
		// =================== pierwszy =======================
		if (!(PIN_pierwszy_we)) {
			i = 0;

			while (i < 50) {
				if ((PIN_pierwszy_we)) {
					stop = stop + 1;
				}
				if (!(PIN_drugi_we)) {
					stop = stop + 1;
				}
				if (!(PIN_trzeci_we)) {
					stop = stop + 1;
				}
				if (!(PIN_czwarty_we)) {
					stop = stop + 1;
				}

				_delay_us(500);
				if (stop == 40) {
					PORT_syrena_wy_1;
					while (1) {
					}
				}
				i = i + 1;
				_delay_us(500);
			}
			stop = 0;
			if (!(PIN_pierwszy_we)) {
				_delay_ms(5);

				if (!(PIN_pierwszy_we)) {

					{
						for (int i = 0; i < 2; i++) {
							PORT_hopper_out_1;
							_delay_ms(20);
							PORT_hopper_out_0;
							_delay_ms(20);
						}
					}
				}
			}
			while (!(PIN_pierwszy_we)) {
			}
		}

// ==========================================================================================
// =================================== drugi ================================================

		if (!(PIN_drugi_we)) {
			i = 0;
			while (i < 50) {
				if (!(PIN_pierwszy_we)) {
					stop = stop + 1;
				}
				if (!(PIN_trzeci_we)) {
					stop = stop + 1;
				}
				if (!(PIN_czwarty_we)) {
					stop = stop + 1;
				}
				if ((PIN_drugi_we)) {
					stop = stop + 1;
				}

				_delay_us(500);
				if (stop == 40) {
					PORT_syrena_wy_1;
					while (1) {
					}
				}
				i = i + 1;
				_delay_ms(1);
			}
			stop = 0;
			if (!(PIN_drugi_we)) {
				_delay_ms(5);
				if (!(PIN_drugi_we)) {
					{
						for (int i = 0; i < 4; i++) {
							PORT_hopper_out_1;
							_delay_ms(20);
							PORT_hopper_out_0;
							_delay_ms(20);
						}
					}
				}
			}
			while (!(PIN_drugi_we)) {
			}
		}
// ==========================================================================================
// ================================= trzeci =================================================
		if (!(PIN_trzeci_we)) {
			i = 0;
			while (i < 50) {
				if (!(PIN_drugi_we)) {
					stop = stop + 1;
				}
				if (!(PIN_pierwszy_we)) {
					stop = stop + 1;
				}
				if (!(PIN_czwarty_we)) {
					stop = stop + 1;
				}
				if (PIN_trzeci_we) {
					stop = stop + 1;
				}
				_delay_ms(1);
				if (stop == 40) {
					PORT_syrena_wy_1;
					while (1) {
					}
				}
				i = i + 1;
				_delay_us(500);
			}
			stop = 0;
			if (!(PIN_trzeci_we)) {
				_delay_ms(5);

				if (!(PIN_trzeci_we)) {
					{
						for (int i = 0; i < 10; i++) {
							PORT_hopper_out_1;
							_delay_ms(20);
							PORT_hopper_out_0;
							_delay_ms(20);
						}
					}
				}
			}

			while (!(PIN_trzeci_we)) {
			}
		}
// ==========================================================================================
// =================================== czwarty ==============================================

		if (!(PIN_czwarty_we)) {
			i = 0;
			while (i < 50) {
				if (!(PIN_drugi_we)) {
					stop = stop + 1;
				}
				if (!(PIN_trzeci_we)) {
					stop = stop + 1;
				}
				if (!(PIN_pierwszy_we)) {
					stop = stop + 1;
				}
				if ((PIN_czwarty_we)) {
					stop = stop + 1;
				}
				_delay_ms(1);
				if (stop == 40) {
					PORT_syrena_wy_1;
					while (1) {
					}
				}
				i = i + 1;
				_delay_us(500);
			}
			stop = 0;
			if (!(PIN_czwarty_we)) {
				_delay_ms(5);

				if (!(PIN_czwarty_we)) {
					{
						for (int i = 0; i < 20; i++) {
							PORT_hopper_out_1;
							_delay_ms(20);
							PORT_hopper_out_0;
							_delay_ms(20);
						}

					}
				}
			}
			while (!(PIN_czwarty_we)) {
			}
		}
// ==========================================================================================

	}

}
