#ifndef SOFTUART_H
#define SOFTUART_H

#include <avr/io.h>
#include <stdint.h>

#define SOFTUART_TX_PORT PORTB
#define SOFTUART_TX_DDR  DDRB
#define SOFTUART_TX_PIN  0   // PB0 as TX

#define SOFTUART_BAUD_DELAY_US 52   // ~19200 baud at 16 MHz

void softuart_init(void);
void softuart_tx_byte(uint8_t data);
void softuart_tx_string(const char *s);

#endif
