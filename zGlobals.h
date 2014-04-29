#ifndef ZGLOBALS_H
#define ZGLOBALS_H
#include <Arduino.h>

#define NUM_LEDS 114
#define NUM_ROWS 3
#define NUM_LEDSPERROW 38
#define NUM_LEDSPERHALFROW 19 //NUM_LEDSPERROW / 2

#define DELAY_NORMAL 7
#define DELAY_FAST 4
#define DELAY_SLOW 18
#define DELAY_FIRE 50
#define DELAY_KR 25

#define NORMBRIGHT 40  // maximum brightness of leds (0-255)
#define MAXBRIGHT 120  // used for "find me" mode

#define DIMSPEED 16     // the higher the faster
#define DIMSPEED_KR 25

// configuration class to be passed to step() function
struct Config_t {
  uint16_t currFrame;
  uint8_t  currDelay;
  uint8_t  currMode;
  
  uint8_t eq7Band[7]; // 63Hz,160Hz,400Hz,1kHz,2.5kHz,6.25kHz,16kHz
  uint8_t eq7Vol[3];  // low(<=400), mid(1k-2.5k), high(>=6.25k)
  uint32_t debug;
};

extern uint8_t soundForEveryone;

// comment out to get RF24 module working
#define NOWIRELESS

#endif
