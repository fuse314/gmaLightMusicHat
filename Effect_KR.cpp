//mode 0: red kr effect
//mode 1: blue kr effect
//mode 2: green kr effect
//mode 3: rainbow kr effect 

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
    case 1:
      _currColor = CRGB(5,32,192); // blue-ish
    break;
    case 2:
      _currColor = CRGB(0,192,0); // green
    break;
  }
}

void EffectKR::step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
  dimLeds(DIMSPEED_KR , _leds, 1);
  if(_effectMode == 3) {
    _currColor = Wheel(_cnf->currFrame);
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

