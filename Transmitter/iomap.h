#ifndef IOMAP_H
#define IOMAP_H
typedef enum {
  A,B,C,D,E,F,G,H,J,K,L
} Port;
typedef enum {
  PIN,
  DIR,
  PORT
} Reg;
typedef enum {
  IO_LOW,
  IO_HIGH
} Status;
typedef enum {
   IN,
   OUT
} Mode;
#endif