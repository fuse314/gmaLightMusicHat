#ifndef EFFECTCLASS_H
#define EFFECTCLASS_H
#include <Arduino.h>
#include <FastSPI_LED2.h>

// abstract class EffectClass to be inherited by different Effects
class EffectClass {
  public:
    // constructor
    EffectClass(uint8_t _mode = 0);
    // step function is called from loop
    virtual void step(uint16_t *_currFrame) = 0; 
    
  protected:
    uint8_t _effectMode;
    CRGB _currColor;
};

#endif
