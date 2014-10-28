//mode 0: random pixels effect
//mode 1: random white "stars" effect
//mode 2: random color block sweep (iRandomWith wide block, one round per color)
//mode 3: random color solid sweep (fill leds with one color, next color)
//mode 4: random color lines (quick fade in, slow fade out)
//mode 5: random color lines (slow fade in, slow fade out)

#ifndef EFFECTRANDOM_H
#define EFFECTRANDOM_H

#include <Arduino.h>
#include "zEffectClass.cpp"
#include "LEDColorMgt.h"

#define RANDOM_WIDTH 5      // width of random colored band (mode 1)
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
    _line->length = random8(NUM_LEDSPERROW/3);
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
    } else if (_mode == 2) {
      _dimspeed = 35;
    } else if (_mode == 3) {
      _dimspeed = 4;
    } else {
      _dimspeed = 16;
    }
    _cnf->currDelay = DELAY_SLOW;
    _cnf->currBright = NORMBRIGHT;
    _currColor = Wheel(random16(768));  // start with random color
    if(_mode == 4 || _mode == 5) {

      // initialize random lines
      for(uint8_t i=0; i<RANDOM_NUM_LINES; i++) {
        initLine(&_rndLines[i]);      
      }
    }
  }
  
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _rowleds) {
  
    if(_effectMode == 2 || _effectMode == 3) {
      if(_cnf->currFrame % NUM_LEDSPERROW == 0) {  // new color on new round
        _currColor = Wheel(random16(768));
      }
    }
  
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
          _leds[random16(NUM_LEDS)] = CRGB(255,255,255);  // white pixel
        }
      break;
      case 2:
        dimLeds(_dimspeed,_leds,1);
        for(uint8_t i=0; i<NUM_ROWS; i++) {
          for(uint8_t j=0; j<RANDOM_WIDTH; j++) {
            _leds[getLedIndex(i,_cnf->currFrame+j)] = _currColor;
          }
        }
      break;
      case 3:
        dimLeds(_dimspeed,_leds,1);
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
};
#endif

