#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include "timer.h"
#include "morse.h"

#define TX_PIN PB0
#define BTN_PIN PD2
#define DOT_THRESHOLD 300   // ms
#define CHAR_GAP 1000       // ms gap to end character
#define BIT_TIME_US 52    // 19200 baud

// --- UART TX init ---
void uart_tx_init(void)
{
    DDRB |= (1 << TX_PIN);
    PORTB |= (1 << TX_PIN);   // idle HIGH
}

// --- UART TX byte ---
void uart_tx_byte(uint8_t data)
{
    PORTB &= ~(1 << TX_PIN); _delay_us(BIT_TIME_US); // start bit
    for(uint8_t i=0;i<8;i++){
        if(data & (1<<i)) PORTB |= (1<<TX_PIN);
        else PORTB &= ~(1<<TX_PIN);
        _delay_us(BIT_TIME_US);
    }
    PORTB |= (1 << TX_PIN); _delay_us(BIT_TIME_US);  // stop bit
}

// --- Main ---
int main(void)
{
    timer0_init();
    uart_tx_init();

    DDRD &= ~(1<<BTN_PIN);   // button input
    PORTD |= (1<<BTN_PIN);   // pull-up

    char buffer[10]; uint8_t idx=0;
    uint32_t lastPress=0;

    while(1){
        if(!(PIND & (1<<BTN_PIN))){   // button pressed
            uint32_t start=timer_ms;
            while(!(PIND & (1<<BTN_PIN))); // wait release
            uint32_t dur=timer_ms-start;

            if(dur<DOT_THRESHOLD && idx<9) buffer[idx++]='.';
            else if(idx<9) buffer[idx++]='-';

            lastPress=timer_ms;
        }

        // End of character detection
        if(idx>0 && (timer_ms-lastPress>CHAR_GAP)){
            buffer[idx]='\0';
            char c=morse_decode(buffer);   // lookup table handles letters + control codes

            uart_tx_byte(c);               // send character/control
            idx=0;
        }
    }
}
