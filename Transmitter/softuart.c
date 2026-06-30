#include "softuart.h"

static void delay_us(uint16_t us) {
    for (uint16_t i = 0; i < us; i++) {
        __asm__ __volatile__("nop");
    }
}

void softuart_init(void) {
    SOFTUART_TX_DDR |= (1 << SOFTUART_TX_PIN);
    SOFTUART_TX_PORT |= (1 << SOFTUART_TX_PIN);  
}

void softuart_tx_byte(uint8_t data) {
    SOFTUART_TX_PORT &= ~(1 << SOFTUART_TX_PIN);
    delay_us(SOFTUART_BAUD_DELAY_US);

    for (uint8_t i = 0; i < 8; i++) {
        if (data & (1 << i)) {
            SOFTUART_TX_PORT |= (1 << SOFTUART_TX_PIN);
        } else {
            SOFTUART_TX_PORT &= ~(1 << SOFTUART_TX_PIN);
        }
        delay_us(SOFTUART_BAUD_DELAY_US);
    }

    SOFTUART_TX_PORT |= (1 << SOFTUART_TX_PIN);
    delay_us(SOFTUART_BAUD_DELAY_US);
}

void softuart_tx_string(const char *s) {
    while (*s) {
        softuart_tx_byte(*s++);
    }
}
