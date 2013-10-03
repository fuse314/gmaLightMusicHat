#ifndef EFFECTRAINBOW_H
#define EFFECTRAINBOW_H
#include "zEffectClass.h"

class EffectRainbow : public EffectClass {
  public:
  EffectRainbow( uint8_t _mode);
  void step(uint16_t *_currFrame);
};
#endif
