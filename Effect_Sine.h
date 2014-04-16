#ifndef EFFECTSINE_H
#define EFFECTSINE_H
#include <Arduino.h>
#include "zEffectClass.h"

class EffectSine : public EffectClass {
  public:
  EffectSine(uint8_t _mode, Config_t *_cnf);
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow);
  
  protected:
  uint8_t sinval[3];
};
#endif
