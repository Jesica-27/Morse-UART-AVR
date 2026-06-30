#ifndef MORSE_H
#define MORSE_H

typedef struct {
    const char *morse;
    char letter;
} morsemap;

static const morsemap morsetable[] = {
    {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'},
    {"-..", 'D'}, {".", 'E'}, {"..-.", 'F'},
    {"--.", 'G'}, {"....", 'H'}, {"..", 'I'},
    {".---", 'J'}, {"-.-", 'K'}, {".-..", 'L'},
    {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
    {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'},
    {"...", 'S'}, {"-", 'T'}, {"..-", 'U'},
    {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'},
    {"-.--", 'Y'}, {"--..", 'Z'},
    {"-----", '0'}, {".----", '1'}, {"..---", '2'},
    {"...--", '3'}, {"....-", '4'}, {".....", '5'},
    {"-....", '6'}, {"--...", '7'}, {"---..", '8'},
    {"----.", '9'},
    // Custom control sequences
    {"------", 0x08},   // Backspace
    {"-.-.-.-", 0x0C} ,    // Clear
    {".-.-.-",  0x04}     // Transmission complete (EOT)
};

char morse_decode(const char *code);

#endif
