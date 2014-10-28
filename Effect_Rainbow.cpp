//mode 0: rainbow all three rows the same
//mode 1: solid color rainbow all leds the same
//mode 2: rainbow through all leds, results in right-left-right run due to led configuration

#ifndef EFFECTRAINBOW_H
#define EFFECTRAINBOW_H
#include "zEffectClass.cpp"
#include "LEDColorMgt.h"

class EffectRainbow : public EffectClass {
  public:
  EffectRainbow(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
    _cnf->currDelay = DELAY_FAST;
    _cnf->currBright = NORMBRIGHT;
  }

  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
    switch(_effectMode) {
      case 0:
        fill_rainbow( &(_ledsrow[0]), NUM_LEDSPERROW, _cnf->currFrame % 256);
        paintAllRows(_ledsrow, _leds);
        break;
      case 1:
        solidColor(Wheel(_cnf->currFrame), _leds, NUM_LEDS);
        break;
      case 2:
        fill_rainbow( &(_leds[0]), NUM_LEDS, _cnf->currFrame % 256);
        break;
    }
  }
};
#endif



