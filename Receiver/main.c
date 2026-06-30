#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "lcd.h"

#define RX_PIN PB0
#define LED_PIN PB1          // LED connected to PB1
#define BIT_TIME_US 52      // 19200 baud

// --- Bit-bang UART RX ---
void uart_rx_init(void)
{
    DDRB &= ~(1<<RX_PIN);   // RX pin as input
    PORTB |= (1<<RX_PIN);   // pull-up
}

uint8_t uart_rx_byte(void)
{
    uint8_t data=0;
    while(PINB & (1<<RX_PIN));        // wait for start bit
    _delay_us(BIT_TIME_US/2);

    for(uint8_t i=0;i<8;i++){
        _delay_us(BIT_TIME_US);
        if(PINB & (1<<RX_PIN)) data|=(1<<i);
    }

    _delay_us(BIT_TIME_US);           // stop bit
    return data;
}

int main(void)
{
    uart_rx_init();
    lcd_init();
    lcd_clear();

    // --- LED setup ---
    DDRB |= (1<<LED_PIN);   // LED pin as output
    PORTB &= ~(1<<LED_PIN); // LED off initially

    uint8_t col=0, row=0;

    while(1){
        uint8_t c=uart_rx_byte();

        // --- Bonus Challenge handling ---
        if(c == 0x08){ // Backspace
            if(col>0){
                col--;
                lcd_set_cursor(col,row);
                lcd_data(' ');
                lcd_set_cursor(col,row);
            }
            continue;
        }
        if(c == 0x0C){ // Clear
            lcd_clear();
            col=0; row=0;
            lcd_set_cursor(0,0);
            continue;
        }
        if(c == 0x04){ // Transmission complete
            lcd_clear();
            lcd_data('D'); lcd_data('O'); lcd_data('N'); lcd_data('E');

            // --- LED ON for 1 second ---
            PORTB |= (1<<LED_PIN);
            _delay_ms(1000);
            PORTB &= ~(1<<LED_PIN);

            lcd_clear();
            col=0; row=0;
            lcd_set_cursor(0,0);
            continue;
        }

        // --- Normal character display ---
        lcd_data(c);

        // --- Line wrapping ---
        col++;
        if(col==16 && row==0){
            lcd_command(0xC0); // move cursor to line 2
            row=1; col=0;
        }
        else if(col==16 && row==1){
            lcd_clear();
            lcd_command(0x80); // reset to line 1
            row=0; col=0;
        }
    }
}