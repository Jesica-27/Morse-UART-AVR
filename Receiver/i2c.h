#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

#define TWBR (*(volatile unsigned char*)0xB8)//bit rate register
#define TWSR (*(volatile unsigned char*)0xB9)//status register
#define TWDR (*(volatile unsigned char*)0xBB)//data register
#define TWCR (*(volatile unsigned char*)0xBC)//control register

#define TWINT 7 //interrupt flag
#define TWSTA 5 //start condition
#define TWSTO 4//stop condition
#define TWEN  2//enable 

// Initialize I2C at 100 kHz (assuming F_CPU = 16 MHz)(standard mode - supports all devices)
void i2c_init(void)
{
    TWBR = 72;        // Bit rate register for ~100 kHz
    TWSR = 0x00;      // Prescaler = 1
    TWCR = (1<<TWEN); // Enable TWI
}

void i2c_start(void)
{
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT))); // Wait for start condition
}

void i2c_write(unsigned char data)
{
    TWDR = data; //load data to register
    TWCR = (1<<TWINT) | (1<<TWEN);//start transmission
    while(!(TWCR & (1<<TWINT))); // Wait for data to be transmitted
}

void i2c_stop(void)
{
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    // No wait here — stop condition is executed automatically
}

#endif