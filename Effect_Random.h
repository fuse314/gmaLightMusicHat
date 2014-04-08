#ifndef EFFECTRANDOM_H
#define EFFECTRANDOM_H

#include <Arduino.h>
#include "zEffectClass.h"

class EffectRandom : public EffectClass {
  public:
  EffectRandom( uint8_t _mode, Config_t *_cnf);
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _rowleds);
  
  protected:
  uint8_t RANDOM_WIDTH;  // width of random color bar (mode 1)
};
#endif
