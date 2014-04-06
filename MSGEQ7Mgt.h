#ifndef MSGEQ7MGT_H
#define MSGEQ7MGT_H
#include <Arduino.h>
#include <FastLED.h>
#include "zEffectClass.h"

void InitEQ7();
void GetEQ7(Config_t *_cnf);
CRGB GetEQColor(Config_t *_cnf);
#endif
