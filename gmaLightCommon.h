#ifndef GMALIGHTCOMMON_H
#define GMALIGHTCOMMON_H

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

#define DIMSPEED 15    // the higher the slower...

//MSGEQ7 stuff
#define EQ7STROBE_PIN 7
#define EQ7RESET_PIN 8
#define EQ7IN_PIN A1
#define NOISE_LVL 100     // noise cutoff value
#define MAX_LVL 1023      // maximum volume value

#endif
