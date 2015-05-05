#ifndef ZGLOBALS_H
#define ZGLOBALS_H
#include <stdint.h>

//#define NUM_LEDS 114
#define M_HEIGHT 3
#define M_WIDTH 38
#define M_HALFWIDTH (M_WIDTH/2)
#define NUM_LEDS (M_HEIGHT * M_WIDTH)
//#define NUM_LEDSPERHALFROW 19 //NUM_LEDSPERROW / 2

#define DELAY_NORMAL 7
#define DELAY_FAST 4
#define DELAY_SLOW 18
#define DELAY_FIRE 50
#define DELAY_KR 25

#define NORMBRIGHT 40  // maximum brightness of leds (0-255)
#define MAXBRIGHT 120  // used for "find me" mode

#define DIMSPEED 16     // the higher the faster
//#define DIMSPEED_KR 35

uint16_t XY( uint8_t x, uint8_t y);

// configuration class to be passed to step() function
struct Config_t {
  uint16_t currFrame;
  uint8_t  currHue;
  uint8_t  currDelay;
  uint8_t  currMode;
  uint8_t  currBright;
  
  uint8_t eq7Band[7]; // 63Hz,160Hz,400Hz,1kHz,2.5kHz,6.25kHz,16kHz
  uint8_t eq7Vol[3];  // low(<=400), mid(1k-2.5k), high(>=6.25k)
};

extern uint8_t soundForEveryone;

// comment out to get RF24 module working
//#define NOWIRELESS

#endif
