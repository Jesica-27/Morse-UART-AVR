#include "timer.h"

volatile uint32_t timer_ms = 0;

void timer0_init(void)
{
    TCCR0A = (1 << WGM01);     // CTC mode

    OCR0A = 249;              // 1 ms @ 16 MHz, prescaler 64

    TCCR0B = (1 << CS01) | (1 << CS00);

    TCNT0 = 0;

    TIFR0 |= (1 << OCF0A); //Prevents a “false” interrupt firing immediately.

    TIMSK0 |= (1 << OCIE0A);

    sei();
}

void delay_ms(uint32_t ms)
{
    uint32_t start;

    cli();
    start = timer_ms;
    sei();

    while ((timer_ms - start) < ms);
}

ISR(TIMER0_COMPA_vect)
{
    timer_ms++;
}