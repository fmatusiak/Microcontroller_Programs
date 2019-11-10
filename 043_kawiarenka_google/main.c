#include "main.h"
// GLOBAL VARIABLES

int main(void) {

	ioInit();
	//int ziet = 48;

	while (1) {
		if (!(PIN_DOTYK)) {
			DOTYK_REL_LOW;
		} else {
			DOTYK_REL_HIGH;
		}

		if (!(PIN_ZASILANIE)) {
			SCREEN_SWITCH_OUT_LOW;
			POWER_REL_LOW;

		} else {
			SCREEN_SWITCH_OUT_HIGH;
			POWER_REL_HIGH;
			//DOTYK_REL_HIGH;
			//for (uint8_t i = 0; i < 5; i++) {
			//	_delay_ms(500);
		//	}
			DOTYK_REL_LOW;
			DOTYK_REL_HIGH;
			while (1)
			{

			}
		}
	}
}
void ioInit(void) {
//========== INS ========================
	_delay_ms(500);

	DDR_ZASILANIE;
	DDR_DOTYK;

	DOTYK_VCC;
	ZASILANIE_VCC;

//========= OUTS ========================
	DOTYK_REL_DDR;
	POWER_REL_DDR;
	SCREEN_SWITCH_OUT_DDR;

	POWER_REL_LOW;
	DOTYK_REL_LOW;
	SCREEN_SWITCH_OUT_LOW;

	_delay_ms(500);

}
