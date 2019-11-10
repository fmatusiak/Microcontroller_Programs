#define DDR_rxs_we DDRD &= ~(_BV(rxs_we))
#define PIN_rxs_we PIND & _BV(rxs_we)
#define rxs_we_VCC PORTD |= _BV(rxs_we)
#define rxs_we_GND PORTD &= ~_BV(rxs_we)
#define rxs_we PD3

#define DDR_txs DDRD |= _BV(txs)
#define PORT_txs_0 PORTD &= ~_BV(txs)
#define PORT_txs_1 PORTD |= _BV(txs)
#define PORT_txs_z PORTD ^= _BV(txs)
#define txs PD2

#define DDR_puls DDRC |= _BV(puls)
#define PORT_puls_1 PORTC &= ~_BV(puls)
#define PORT_puls_0 PORTC |= _BV(puls)
#define PORT_puls_z PORTC ^= _BV(puls)
#define puls PC5



#define DDR_IN6_IN DDRB &= ~(_BV(IN6_IN)) // IN 6
#define PIN_IN6_IN PINB & _BV(IN6_IN)
#define IN6_IN_VCC PORTB |= _BV(IN6_IN)
#define IN6_IN_GND PORTB &= ~_BV(IN6_IN)
#define IN6_IN PB2


typedef enum {
	false, true
} bool;


void uart_init(uint16_t);
void uart_putc(uint8_t);
uint8_t uart_ischar(void);
uint8_t uart_getc(void);
void uartPut(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t*);
int czytaj_bajt(void);
void nabij_impuls(void);
void init_device(void);
void request_status(void);
void Inhibit(void);
void Escrow_Limit(void);
void Security(void);
void Enable_disbale(void);
void Comunicaion_mode(void);
void Escrow_Limit_Reqest(void);
void Reset(void);
void EXT_version_request(void);
void version_request(void);
void put_crc(uint16_t cc);
uint8_t crc_1(uint16_t cc);
uint8_t crc_2(uint16_t cc);
bool check_acept(void);
void is_bill(void);
void KEEP(void);
void ESCROW_UNIT_STATUS (void);
void ACK(void);
void uart_clear(void);
void Stack(void);
bool check_Esc(void);
void oddaj_kase(void);
void stack_kas(void);
