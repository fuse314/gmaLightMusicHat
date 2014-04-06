#ifndef EFFECTFINDME_H
#define EFFECTFINDME_H
#include "zEffectClass.h"

class EffectFindMe : public EffectClass {
  public:
  EffectFindMe(uint8_t _mode, Config_t *_cnf);
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow);
  protected:
  uint8_t FINDME_WIDTH;
};
#endif
