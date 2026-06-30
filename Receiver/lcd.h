#ifndef LCD_H
#define LCD_H
#include "i2c.h"
#include "utils.h"

#define LCD_ADDR 0x27

#define LCD_BACKLIGHT 0x08
#define LCD_EN        0x04//latch data
#define LCD_RW        0x02//read/write
#define LCD_RS        0x01//register select-command/data

// Send 4 bits to LCD
static void lcd_write4(unsigned char data)
{
    // Write data with backlight
    i2c_start();
    i2c_write(LCD_ADDR << 1);
    i2c_write(data | LCD_BACKLIGHT);
    i2c_stop();

    // Enable pulse HIGH
    i2c_start();
    i2c_write(LCD_ADDR << 1);
    i2c_write(data | LCD_EN | LCD_BACKLIGHT);//giving information that data comes
    i2c_stop();

    _delay_us(1);   // short pulse

    // Enable pulse LOW
    i2c_start();
    i2c_write(LCD_ADDR << 1);
    i2c_write((data & ~LCD_EN) | LCD_BACKLIGHT);//take the data and process it
    i2c_stop();

    _delay_us(50);  // allow command to settle
}

// Send full byte (high nibble + low nibble)
static void lcd_send(unsigned char value, unsigned char mode)
{
    unsigned char high = value & 0xF0;//extract upper nibble
    unsigned char low  = (value << 4) & 0xF0;//extract lower nibble

    lcd_write4(high | mode);//send upper nibble
    lcd_write4(low  | mode);//send lower nibble
}

void lcd_command(unsigned char cmd)
{
    lcd_send(cmd, 0);
    _delay_ms(2);
}

void lcd_data(unsigned char data)
{
    lcd_send(data, LCD_RS);
    _delay_us(50);
}

void lcd_clear()
{
    lcd_command(0x01);
    _delay_ms(2);
}

void lcd_init()
{
    i2c_init();

    _delay_ms(50);

    // Initialization sequence(wakeup command)
    lcd_write4(0x30);
    _delay_ms(5);

    lcd_write4(0x30);
    _delay_ms(5);

    lcd_write4(0x30);
    _delay_ms(5);

    lcd_write4(0x20); // 4-bit mode
    _delay_ms(5);

    lcd_command(0x28); // 4-bit, 2 line, 5x8 dots
    lcd_command(0x0C); // Display ON, cursor OFF
    lcd_command(0x06); // Entry mode: increment
    lcd_clear();
}

// Helper: set cursor position
void lcd_set_cursor(uint8_t col, uint8_t row)
{
    uint8_t row_offsets[] = {0x00, 0x40};
    lcd_command(0x80 | (col + row_offsets[row]));
}

#endif