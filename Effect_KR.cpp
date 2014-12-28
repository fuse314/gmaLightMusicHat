//mode 0: red kr effect
//mode 1: rainbow kr effect
//mode 2: sound reactive kr effect (hue shift)

#include "zEffectClass.cpp"
#include "LEDColorMgt.h"

#define KR_WIDTH 7     // width of KR-band
#define KR_DIMSPEED 35

class EffectKR : public EffectClass {

  public:
  EffectKR(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode, _cnf) {
    _cnf->currDelay = DELAY_KR;
    _cnf->currBright = NORMBRIGHT;
    switch(_effectMode) {
      case 0:
        _currColor = CRGB(192,6,0); // red
      break;
    }
  }
  
  void step(Config_t *_cnf, CRGB* _leds) {
    dimLeds(KR_DIMSPEED , _leds, 1);
    switch(_effectMode) {
      case 1:
        _currColor = CHSV(_cnf->currHue,255,255);
      break;
      case 2:
        _currColor = Wheel(520 + _cnf->eq7Vol[1]);
        _currColor.fadeToBlackBy(128-(_cnf->eq7Vol[1]/2));
      break;
    }
    
    for(uint8_t i=0; i<M_HEIGHT; i++) {
      uint16_t startIndex = getKRLedIndex(i, _cnf->currFrame, KR_WIDTH);
      uint16_t endIndex;
      if(i%2==0) {
        endIndex = startIndex + KR_WIDTH;
        for(uint16_t j=startIndex; j<endIndex; j++) {
          if(j==startIndex || j==endIndex-1) { // fade edges for better effect
            _leds[j] += _currColor - CRGB(128,128,128);
          } else {
            _leds[j] += _currColor;
          }
        }
      } else {
        startIndex += 1;
        endIndex = startIndex - KR_WIDTH;
        for(uint16_t j=endIndex; j<startIndex; j++) {
          _leds[j] += _currColor;
        }
      }
    }
  }
};

