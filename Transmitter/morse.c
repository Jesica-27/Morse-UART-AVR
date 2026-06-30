#include "morse.h"
#include <string.h>

char morse_decode(const char *code) {
    for (int i = 0; i < sizeof(morsetable)/sizeof(morsetable[0]); i++) {
        if (strcmp(code, morsetable[i].morse) == 0) {
            return morsetable[i].letter;
        }
    }
    return '?';  // unknown sequence
}
