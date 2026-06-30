#ifndef GPIO_H
#define GPIO_H

#include "iomap.h"
#include <stdint.h>

extern const uintptr_t base_addr[];

void pin_mode(Port port, Mode mode, char pin);
void pin_write(Port port, char pin, Status status);
Status pin_read(Port port, char pin);

#endif
