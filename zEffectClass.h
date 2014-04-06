#ifndef EFFECTCLASS_H
#define EFFECTCLASS_H
#include <Arduino.h>
#include <FastLED.h>

// configuration class to be passed to step() function
struct Config_t {
  
  uint16_t currFrame;
  uint8_t  currDelay;

  uint16_t eq7Values[7];
  // [0], [1], [2],  [3],  [4],  [5],   [6]
  //  63, 160, 400, 1000, 2500, 6250, 16000 Hz
  uint16_t eq7Volumes[3];
  // 0 = low tones, 1 = mid tones, 3 = high tones

};

// abstract class EffectClass to be inherited by different Effects
class EffectClass {
  public:
    // constructor
    EffectClass(uint8_t _mode = 0, Config_t *_cnf = 0);
    // step function is called from loop
    virtual void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) = 0; 
    
  protected:
    uint8_t _effectMode;
    CRGB _currColor;
};

#endif
