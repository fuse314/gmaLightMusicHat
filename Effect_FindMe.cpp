// Find Me Effect (spinning white light), all three rows show the same

#include "Effect_FindMe.h"
#include "LEDColorMgt.h"
#include "zGlobals.h"

EffectFindMe::EffectFindMe(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode, _cnf) {
  _cnf->currDelay = DELAY_SLOW;
  clearAllLeds();
  LEDS.setBrightness(MAXBRIGHT);
  _currColor = CRGB(255,255,255);
  FINDME_WIDTH = 2;
}

void EffectFindMe::step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
  clearAllLeds();
  for(uint8_t i=0; i<NUM_ROWS; i++) {
    for(uint8_t j=0; j<FINDME_WIDTH; j++) {
      _leds[getLedIndex(i,_cnf->currFrame+j)] = _currColor;  // for police blue-red pattern use CRGB(255,0,0)
      _leds[getLedIndex(i,_cnf->currFrame+NUM_LEDSPERHALFROW+j)] = _currColor;  // and CRGB(0,0,255)
    }
  }
}
