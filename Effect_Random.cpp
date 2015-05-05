//mode 0: random pixels effect
//mode 1: random white "stars" effect
//mode 2: random color lines (quick fade in, slow fade out)
//mode 3: random color lines (slow fade in, slow fade out)

#ifndef EFFECTRANDOM_H
#define EFFECTRANDOM_H

#include "zEffectClass.h"
#include "LEDColorMgt.h"

#define RANDOM_NUM_LINES 9  // number of random lines (mode x)

class EffectRandom : public EffectClass {
  protected:
  struct rndline_t {
    uint16_t start;       // start index
    uint8_t  length;      // length
    uint8_t  hue;         // hue
    uint8_t  anim_idx;    // animation index (brightness)
    uint8_t  anim_speed;  // animation speed
  };
  rndline_t _rndLines[RANDOM_NUM_LINES];  // array of random line variables
  void initLine(rndline_t *_line) {  // initialize line object
    _line->start = random16(NUM_LEDS-1);
    _line->length = random8(M_WIDTH/3);
    if(_line->start+_line->length >= NUM_LEDS) {
      _line->length = NUM_LEDS-_line->start-1;
    }
    _line->hue = random8();
    _line->anim_idx = 0;
    _line->anim_speed = 1+random8(4);
  }
  void stepLine(rndline_t *_line) {  // advance animation one step
    _line->anim_idx = qadd8(_line->anim_idx,_line->anim_speed);
    if(_line->anim_idx == 255) {
      initLine(_line);
    }
  }
  uint8_t _dimspeed;

  public:
  EffectRandom(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
    if(_mode == 0) {
      _dimspeed = 8;
    } else {
      _dimspeed = 16;
    }
    _cnf->currDelay = DELAY_SLOW;
    _cnf->currBright = NORMBRIGHT;
    _currColor = Wheel(random16(768));  // start with random color
    if(_mode == 2 || _mode == 3) {

      // initialize random lines
      for(uint8_t i=0; i<RANDOM_NUM_LINES; i++) {
        initLine(&_rndLines[i]);      
      }
    }
  }
  
  void step(Config_t *_cnf, CRGB* _leds) {
  
    switch(_effectMode) {
      case 0:
        dimLeds(_dimspeed,_leds,1);
        if(random8() < 96) {  // the bigger the number (up to 255) the better the chances of placing a pixel
          _leds[random16(NUM_LEDS)] = Wheel(random16(768));
        }
      break;
      case 1:
        dimLeds(_dimspeed,_leds,1);
        if(random8() < 160) {  // see comment above
          _leds[random16(NUM_LEDS)] = CRGB::White;
        }
      break;
      case 2:
      case 3:
        clearLeds(_leds, NUM_LEDS);
        for(uint8_t i=0; i<RANDOM_NUM_LINES; i++) {
          stepLine(&_rndLines[i]);
          if(_effectMode == 2) {
            _currColor = CHSV(_rndLines[i].hue,255,255-_rndLines[i].anim_idx);
          } else {
            _currColor = CHSV(_rndLines[i].hue,255,quadwave8(_rndLines[i].anim_idx));
          }
          for(uint16_t j=_rndLines[i].start; j<(_rndLines[i].start+_rndLines[i].length); j++) {
            _leds[j] += _currColor;
          }
        }
      break;
    }
  }
};
#endif

