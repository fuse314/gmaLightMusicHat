//mode 1: volume dependent width, eqColor bars
//mode 2: volume dependent width, rainbow bars
//mode 3: all leds solid eqColor
//mode 4: volume dependent width, white bars with rainbow underlay
//mode 5: rotating eqColor sound graph
//mode 6: volume dependent width, volume dependent color blue to red bars
//mode 7: volume dependent width, volume dependent color green to blue bars
//mode 8: volume dependent width, red bars with blue background
//mode 9: volume dependent brightness, red solid color per row
//mode 10: volume dependent brightness, volume dependent color green to blue per row

#include "zEffectClass.cpp"
#include "LEDColorMgt.h"
#include "MSGEQ7Mgt.cpp"

class EffectSound : public EffectClass {
  private:
  MSGEQ7Mgt eq7;
  CRGBPalette16 _palette;  // use palette for color dependent sound effects
  
  public:
  EffectSound(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
    _cnf->currDelay = DELAY_NORMAL;
    _cnf->currBright = NORMBRIGHT;
    switch(_effectMode) {
      case 6:
        _palette = CRGBPalette16(CRGB::Blue, CRGB::Red);
      break;
      case 7:
        _palette = CRGBPalette16(CRGB::Green, CRGB::Blue);
      break;
      case 10:
        _palette = CRGBPalette16(CRGB::Blue, CRGB::Green);
      break;
    }
  }
  
  void step(Config_t *_cnf, CRGB* _leds) {
    if(_effectMode == 4) {
      fill_rainbow( &(_leds[0]), M_WIDTH, _cnf->currFrame % 256);
      copyRowToAll(_leds);
    }
    if(_effectMode == 8) {
      setColor(CRGB(0,0,100),_leds,NUM_LEDS); // blue base color
    }
    
    CRGB theColor;
    switch (_effectMode) {
      case 1:
      case 2:
      case 4:
      case 6:
      case 7:
      case 8:
        if(_effectMode != 8 && _effectMode != 4) {
          clearLeds(_leds, NUM_LEDS);
        }
        switch(_effectMode) {
          case 1:
            theColor = eq7.GetEQColor(_cnf);
          break;
          case 2:
            theColor = CHSV(_cnf->currHue,255,255);
          break;
          case 8:
            theColor = CRGB(255,0,0); // red bar
          break;
        }
        for(uint8_t i=0; i<M_HEIGHT; i++) {
          if(_cnf->eq7Vol[i] > 0) {
            if(_effectMode == 4) {
              theColor = CHSV(0,0,_cnf->eq7Vol[i]);
            } else
            if(_effectMode == 6 || _effectMode == 7) {
              theColor = ColorFromPalette(_palette, _cnf->eq7Vol[i]);
            }
            uint8_t soundlvl = map(_cnf->eq7Vol[i], 1, 255, 1, M_HALFWIDTH);
            for(uint8_t j=0; j<soundlvl; j++) {
              if (_effectMode==4) {
                _leds[XY(M_HALFWIDTH-j-1,i)] += theColor;
                _leds[XY(M_HALFWIDTH+j,i)] += theColor;
              } else {
                _leds[XY(M_HALFWIDTH-j-1,i)] = theColor;
                _leds[XY(M_HALFWIDTH+j,i)] = theColor;
              }
            }
          }
        }
        break;
      case 3:
        setColor(eq7.GetEQColor(_cnf),_leds,NUM_LEDS);
        break;
      case 5:
        theColor = eq7.GetEQColor(_cnf);
        dimLeds(DIMSPEED,_leds,1);
        for(uint8_t i=0; i<M_HEIGHT; i++) {
          _leds[XY(_cnf->currFrame,i)] = theColor;
        }
        break;
      case 9:
      case 10:
        for(uint8_t i=0; i<M_HEIGHT; i++) {
          if(_cnf->eq7Vol[i] > 0) {
            if(_effectMode == 9) {
              theColor = CRGB(_cnf->eq7Vol[i],0,0);  // red, dependent on volume
            } else {
              if(_effectMode == 10) {            //      from green(256) to blue(511)  , dim from 0-255 depending on volume
                theColor = ColorFromPalette(_palette,_cnf->eq7Vol[i]).nscale8(_cnf->eq7Vol[i]);
              }
            }
          } else {
            theColor = CRGB(0,0,0);
          }
          setColor(theColor,&_leds[M_WIDTH*i],M_WIDTH);
        }
        break;
    }
  }
};

