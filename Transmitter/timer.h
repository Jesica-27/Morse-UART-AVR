#ifndef TIMER_H
#define TIMER_H

#include <avr/interrupt.h>
#include <stdint.h>

#define TCCR0A (*(volatile uint8_t*)0x44)
#define TCCR0B (*(volatile uint8_t*)0x45)
#define TCNT0  (*(volatile uint8_t*)0x46)
#define OCR0A  (*(volatile uint8_t*)0x47)

#define TIFR0  (*(volatile uint8_t*)0x35)
#define TIMSK0 (*(volatile uint8_t*)0x6E)

#define WGM01 1

#define CS00 0
#define CS01 1
#define CS02 2

#define OCF0A 1
#define OCIE0A 1

extern volatile uint32_t timer_ms;

void timer0_init(void);
void delay_ms(uint32_t ms);

#endif