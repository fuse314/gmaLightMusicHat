// Find Me Effect (spinning white light), all three rows show the same

#ifndef EFFECTFINDME_H
#define EFFECTFINDME_H
#include "zEffectClass.cpp"
#include "LEDColorMgt.h"

#define FINDME_WIDTH 3

class EffectFindMe : public EffectClass {

  public:
  EffectFindMe(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode, _cnf) {
    _cnf->currDelay = DELAY_SLOW;
    _cnf->currBright = MAXBRIGHT;
    _currColor = CRGB(255,255,255);
  }
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
    /*cmgt.*/clearLeds(_leds, NUM_LEDS);
    for(uint8_t i=0; i<NUM_ROWS; i++) {
      for(uint8_t j=0; j<FINDME_WIDTH; j++) {
        _leds[/*cmgt.*/getLedIndex(i,_cnf->currFrame+j)] = _currColor;  // for police blue-red pattern use CRGB(255,0,0)
        _leds[/*cmgt.*/getLedIndex(i,_cnf->currFrame+NUM_LEDSPERHALFROW+j)] = _currColor;  // and CRGB(0,0,255)
      }
    }
  }
};
#endif

