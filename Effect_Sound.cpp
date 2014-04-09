//mode 1: volume dependent width, eqColor bars
//mode 2: volume dependent width, rainbow bars
//mode 3: all leds solid eqColor
//mode 4: volume dependent width, eqColor bars with rainbow underlay
//mode 5: rotating eqColor sound graph
//mode 6: fixed eqColor sound graph with rotating (shift all leds)
//mode 7: volume dependent width, volume dependent color blue to red bars
//mode 8: volume dependent width, volume dependent color green to blue bars
//mode 9: volume dependent width, red bars with blue background
//mode 10: volume dependent brightness, red solid color per row
//mode 11: volume dependent brightness, volume dependent color green to blue per row

#include "zEffectClass.h"
#include "Effect_Sound.h"
#include "zGlobals.h"
#include "LEDColorMgt.h"
#include "MSGEQ7Mgt.h"


EffectSound::EffectSound(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
  _cnf->currDelay = DELAY_NORMAL;
  LEDS.setBrightness(NORMBRIGHT);
}

void EffectSound::step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
  if(_effectMode == 4) {
    fill_rainbow( &(_ledsrow[0]), NUM_LEDSPERROW, _cnf->currFrame % 256);
    paintAllRows(_ledsrow, _leds);
  }
  if(_effectMode == 9) {
    solidColor(CRGB(0,0,128),_ledsrow,NUM_LEDSPERROW); // blue base color
  }
  
  CRGB theColor;
  switch (_effectMode) {
    case 1:
    case 2:
    case 4:
    case 7:
    case 8:
    case 9:
      if(_effectMode != 9) {
        clearLeds(_ledsrow, NUM_LEDSPERROW);
      }
      if(_effectMode == 1 || _effectMode == 2 || _effectMode == 4) {
        theColor = GetEQColor(_cnf);
      }
      if(_effectMode == 9) {
        theColor = CRGB(255,0,0); // red bar
      }
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        if(_cnf->eq7Vol[i] > 0) {
          if(_effectMode == 7) {  // color depending on volume from blue(512) to red(767)
            theColor = Wheel(_cnf->eq7Vol[i] + 512);
          }
          if(_effectMode == 8) {  // color depending on volume from green(256) to blue(511)
            theColor = Wheel(_cnf->eq7Vol[i] + 256);
          }
          uint8_t soundlvl = map(_cnf->eq7Vol[i], 1, 255, 1, NUM_LEDSPERHALFROW);
          for(uint8_t j=0; j<soundlvl; j++) {
            if(_effectMode == 2) {
              _ledsrow[j] = Wheel(_cnf->currFrame);
            } else {
              _ledsrow[j] = theColor;  // idea: dim lights from the middle in higher volumes... something with .nscale8(0-255);
            }
          }
        }
        if(_effectMode == 4) {
          showMirrored(i, _ledsrow, _leds, 1);  // merge with current line content
        } else {
          showMirrored(i, _ledsrow, _leds, 0);  // overwrite with content
        }
      }
      break;
    case 3:
      solidColor(GetEQColor(_cnf), _leds, NUM_LEDS);
      break;
    case 5:
      theColor = GetEQColor(_cnf);
      dimLeds(DIMSPEED,_leds,1);
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        _leds[getLedIndex(i,_cnf->currFrame)] = theColor;
      }
      break;
    case 6:
      theColor = GetEQColor(_cnf);
      shiftLeds(1, _leds);
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        _leds[getLedIndex(i,NUM_LEDSPERROW-1)] = theColor;
      }
      break;
    case 10:
    case 11:
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        if(_cnf->eq7Vol[i] > 0) {
          if(_effectMode == 10) {
            theColor = CRGB(_cnf->eq7Vol[i],0,0);  // red, dependent on volume
          } else {
            if(_effectMode == 11) {            //      from green(256) to blue(511)  , dim from 0-255 depending on volume
              theColor = Wheel(_cnf->eq7Vol[i] + 256).nscale8(_cnf->eq7Vol[i]);
            }
          }
        } else {
          theColor = CRGB(0,0,0);
        }
        solidColorRow(theColor, i, _leds);
      }
      break;
  }
}
