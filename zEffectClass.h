#ifndef EFFECTCLASS_H
#define EFFECTCLASS_H

#include "zGlobals.h"
#include <FastLED.h>

// abstract class EffectClass to be inherited by different Effects
class EffectClass {
  public:
    // constructor
    EffectClass(uint8_t _mode = 0, Config_t *_cnf = 0) {
      _effectMode = _mode;
    }
    // step function is called from loop
    virtual void step(Config_t *_cnf, CRGB* _leds) = 0; 
    
  protected:
    uint8_t _effectMode;
    CRGB _currColor;
};

#endif


