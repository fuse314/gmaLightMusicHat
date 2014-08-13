//mode 0: random pixels effect
//mode 1: random white "stars" effect
//mode 2: random color block sweep (iRandomWith wide block, one round per color)
//mode 3: random color solid sweep (fill leds with one color, next color)
//mode 4: random color lines (quick fade in, slow fade out)
//mode 5: random color lines (slow fade in, slow fade out)

#include "zEffectClass.h"
#include "Effect_Random.h"
#include "LEDColorMgt.h"
#include "zGlobals.h"

EffectRandom::EffectRandom(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
  _cnf->currDelay = DELAY_SLOW;
  LEDS.setBrightness(NORMBRIGHT);
  _currColor = Wheel(random16(768));  // start with random color
  if(_mode == 4 || _mode == 5) {
    // initialize random lines
    for(uint8_t i=0; i<RANDOM_NUM_LINES; i++) {
      initLine(&_rndLines[i]);      
    }
  }
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
    case 4:
    case 5:
      uint8_t _bright = 0;
      clearLeds(_leds, NUM_LEDS);
      for(uint8_t i=0; i<RANDOM_NUM_LINES; i++) {
        stepLine(&_rndLines[i]);
        if(_effectMode == 4) {
          _bright = 255-_rndLines[i].anim_idx;
        } else {
          _bright = quadwave8(_rndLines[i].anim_idx);
        }
        _currColor = CHSV(_rndLines[i].hue,255,_bright);
        for(uint16_t j=_rndLines[i].start; j<(_rndLines[i].start+_rndLines[i].length); j++) {
          _leds[j] += _currColor;
        }
      }
    break;
  }
}

void EffectRandom::initLine(rndline_t *_line) {  // initialize line object
  _line->start = random16(NUM_LEDS);
  _line->length = random8(NUM_LEDSPERROW);
  if(_line->start+_line->length >= NUM_LEDS) {
    _line->length = NUM_LEDS-1;
  }
  _line->hue = random8();
  _line->anim_idx = 0;
  _line->anim_speed = 1+random8(4);
}

void EffectRandom::stepLine(rndline_t *_line) {  // advance animation one step
  _line->anim_idx = qadd8(_line->anim_idx,_line->anim_speed);
  if(_line->anim_idx == 255) {
    initLine(_line);
  }
}
