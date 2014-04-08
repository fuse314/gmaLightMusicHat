#ifndef MSGEQ7MGT_H
#define MSGEQ7MGT_H
#include <Arduino.h>
#include <FastLED.h>
#include "zGlobals.h"

//MSGEQ7 stuff
#define EQ7STROBE_PIN 7
#define EQ7RESET_PIN 8
#define EQ7IN_PIN A1
#define NOISE_LVL 100     // noise cutoff value
#define MAX_LVL 1024      // maximum volume value

void InitEQ7();
void GetEQ7(Config_t *_cnf);
CRGB GetEQColor(Config_t *_cnf);
#endif
