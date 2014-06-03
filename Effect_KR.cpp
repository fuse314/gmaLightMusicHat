//mode 0: red kr effect
//mode 1: rainbow kr effect
//mode 2: sound reactive kr effect (hue shift)

#include "Effect_KR.h"
#include "LEDColorMgt.h"
#include "zGlobals.h"

EffectKR::EffectKR(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode, _cnf) {
  _cnf->currDelay = DELAY_KR;
  LEDS.setBrightness(NORMBRIGHT);
  KR_WIDTH = 7;
  switch(_effectMode) {
    case 0:
      _currColor = CRGB(192,6,0); // red
    break;
  }
}

void EffectKR::step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
  dimLeds(DIMSPEED_KR , _leds, 1);
  switch(_effectMode) {
    case 1:
      _currColor = Wheel(_cnf->currFrame);
    break;
    case 2:
      _currColor = Wheel(520 + _cnf->eq7Vol[1]);
      _currColor.fadeToBlackBy(128-(_cnf->eq7Vol[1]/2));
    break;
  }
  
  for(uint8_t i=0; i<NUM_ROWS; i++) {
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

