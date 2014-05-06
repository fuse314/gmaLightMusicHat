//mode 0: random pixels effect
//mode 1: random white "stars" effect
//mode 2: random color block sweep (iRandomWith wide block, one round per color)
//mode 3: random color solid sweep (fill leds with one color, next color)

#include "zEffectClass.h"
#include "Effect_Random.h"
#include "LEDColorMgt.h"
#include "zGlobals.h"

EffectRandom::EffectRandom(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
  _cnf->currDelay = DELAY_SLOW;
  RANDOM_WIDTH = 4;
  LEDS.setBrightness(NORMBRIGHT);
  _currColor = Wheel(random16(768));  // start with random color
}

void EffectRandom::step(Config_t *_cnf, CRGB* _leds, CRGB* _rowleds) {

  if(_effectMode == 2 || _effectMode == 3) {
    if(_cnf->currFrame % NUM_LEDSPERROW == 0) {  // new color on new round
      _currColor = Wheel(random16(768));
    }
  }

  switch(_effectMode) {
    case 0:
      dimLeds(DIMSPEED/2,_leds,1);
      if(random8() < 96) {  // the bigger the number (up to 255) the better the chances of placing a pixel
        _leds[random16(NUM_LEDS)] = Wheel(random16(768));
      }
    break;
    case 1:
      dimLeds(DIMSPEED,_leds,1);
      if(random8() < 160) {  // see comment above
        _leds[random16(NUM_LEDS)] = CRGB(255,255,255);  // white pixel
      }
    break;
    case 2:
      dimLeds(DIMSPEED_KR,_leds,1);
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        for(uint8_t j=0; j<RANDOM_WIDTH; j++) {
          _leds[getLedIndex(i,_cnf->currFrame+j)] = _currColor;
        }
      }
    break;
    case 3:
      dimLeds(DIMSPEED/4,_leds,1);
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        _leds[getLedIndex(i,_cnf->currFrame)] = _currColor;
      }
    break;
  }
}
