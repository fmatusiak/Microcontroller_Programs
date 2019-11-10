//DOUBLE

#ifndef CCTALK_H_
#define CCTALK_H_

void cc_put(uint8_t from, uint8_t dataCount, uint8_t to, uint8_t command,uint8_t *data);
void bill_init();
void bill_alive();
int analyze_data(uint8_t buffer[]);
void bill_enable(void);
void bill_distable(void);
void bill_take(void);
void bill_reject(void);
uint8_t checksum(uint8_t buffer[], uint8_t byte_count);

#endif /* CCTALK_H_ */
