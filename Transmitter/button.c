#include "button.h"

void button_init(Port port, char pin) {
    pin_mode(port, IN, pin);
    pin_write(port, pin, IO_HIGH); 
}

ButtonState button_read(Port port, char pin) {
    if (pin_read(port, pin) == IO_LOW) {
        return BUTTON_PRESSED;
    } else {
        return BUTTON_RELEASED;
    }
}
