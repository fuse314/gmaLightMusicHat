#ifndef EFFECTRANDOM_H
#define EFFECTRANDOM_H

#include "Arduino.h"

class EffectRandom : public EffectClass {
  public:
  EffectRandom( uint8_t _mode);
  void step(uint16_t *_currFrame);
  
  protected:
  uint8_t RANDOM_WIDTH;  // width of random color bar (mode 1)
};
#endif
