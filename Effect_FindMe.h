#ifndef EFFECTFINDME_H
#define EFFECTFINDME_H
#include "zEffectClass.h"

class EffectFindMe : public EffectClass {
  public:
  EffectFindMe( uint8_t _mode);
  void step(uint16_t *_currFrame);
  protected:
  uint8_t FINDME_WIDTH;
};
#endif
