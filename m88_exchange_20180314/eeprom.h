//DOUBLE

#ifndef EEPROM_H_
#define EEPROM_H_

uint32_t read(uint32_t adr);
void write(uint8_t target, uint32_t value);

uint32_t read_in(void);
uint32_t read_out1(void);
uint32_t read_out2(void);
//uint32_t read_hopper(void);

void set_in(uint8_t value);
void set_out1(uint8_t value);
void set_out2(uint8_t value);
//void set_hopper(uint32_t value);
//void refill_hopper(void);

#endif /* EEPROM_H_ */
