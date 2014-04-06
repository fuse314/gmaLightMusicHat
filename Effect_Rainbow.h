#ifndef EFFECTRAINBOW_H
#define EFFECTRAINBOW_H
#include "zEffectClass.h"

class EffectRainbow : public EffectClass {
  public:
  EffectRainbow(uint8_t _mode, Config_t *_cnf);
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow);
};
#endif
