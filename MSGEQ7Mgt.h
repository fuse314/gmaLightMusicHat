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

// this value overwrites the bright white color when loud noise is present with a rainbow color, dimmed according to loudness
// as soon as the average loudness level (0-255) of eq7Vol is greater than (EQ7RAINBOW_LVL), the sound color is replaced with the rainbow color.
#define EQ7RAINBOW_LVL 140   // set this to 256 to disable rainbow colors in GetEQColor(...)

void InitEQ7();
void GetEQ7(Config_t *_cnf);
CRGB GetEQColor(Config_t *_cnf);
#endif
