#ifndef EFFECTKR_H
#define EFFECTKR_H
#include <Arduino.h>
#include "zEffectClass.h"

class EffectKR : public EffectClass {
  public:
  EffectKR( uint8_t _mode);
  void step(uint16_t *_currFrame);
  
  protected:
  uint8_t KR_WIDTH;
};
#endif
