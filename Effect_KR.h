#ifndef EFFECTKR_H
#define EFFECTKR_H
#include <Arduino.h>
#include "zEffectClass.h"

class EffectKR : public EffectClass {
  public:
  EffectKR(uint8_t _mode, Config_t *_cnf);
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow);
  
  protected:
  uint8_t KR_WIDTH;
};
#endif
