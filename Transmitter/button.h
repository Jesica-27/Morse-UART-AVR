#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include "gpio.h"

typedef enum {
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED  = 1
} ButtonState;

void button_init(Port port, char pin);
ButtonState button_read(Port port, char pin);

#endif

