#include "gpio.h"

const uintptr_t base_addr[] = {
    0x20, 0x23, 0x26, 0x29, 0x2C,
    0x2F, 0x32, 0x100, 0x103, 0x106, 0x109
};

void pin_mode(Port port, Mode mode, char pin) {
    volatile uint8_t *ddr = (volatile uint8_t *)(base_addr[port] + 1);
    if (mode == OUT)
        *ddr |= (1 << pin);
    else
        *ddr &= ~(1 << pin);
}

void pin_write(Port port, char pin, Status status) {
    volatile uint8_t *port_reg = (volatile uint8_t *)(base_addr[port] + 2);
    if (status == IO_HIGH)
        *port_reg |= (1 << pin);
    else
        *port_reg &= ~(1 << pin);
}

Status pin_read(Port port, char pin) {
    volatile uint8_t *pin_reg = (volatile uint8_t *)(base_addr[port]);
    return ((*pin_reg & (1 << pin)) ? IO_HIGH : IO_LOW);
}
