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
#include "gmaLightMusicHat.h"
#include "LEDColorMgt.h"
#include "MSGEQ7Mgt.h"


EffectSound::EffectSound(uint8_t _mode) : EffectClass(_mode) {
  currDelay = DELAY_NORMAL;
  LEDS.setBrightness(NORMBRIGHT);
  if(_effectMode == 3 || _effectMode == 5) {
    clearAllLeds();
  }
}

void EffectSound::step(uint16_t *_currFrame) {
  GetEQ7();
  if(_effectMode == 4) {
    fill_rainbow( &(ledsrow[0]), NUM_LEDSPERROW, *_currFrame % 256);
    paintAllRows(ledsrow);
  }
  if(_effectMode == 9) {
    solidColorLedsRow(CRGB(0,0,128)); // blue base color
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
        clearRowLeds();
      }
      if(_effectMode == 1 || _effectMode == 2 || _effectMode == 4) {
        theColor = GetEQColor();
      }
      if(_effectMode == 9) {
        theColor = CRGB(255,0,0); // red bar
      }
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        if(eq7Volumes[i] >= NOISE_LVL) {
          if(_effectMode == 7) {  // color depending on volume from blue(512) to red(767)
            theColor = Wheel(map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 512, 767));
          }
          if(_effectMode == 8) {  // color depending on volume from green(256) to blue(511)
            theColor = Wheel(map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 256, 511));
          }
          uint8_t soundlvl = map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 1, NUM_LEDSPERHALFROW);
          for(uint8_t j=0; j<soundlvl; j++) {
            if(_effectMode == 2) {
              ledsrow[j] = Wheel(*_currFrame);
            } else {
              ledsrow[j] = theColor;  // idea: dim lights from the middle in higher volumes... something with .nscale8(0-255);
            }
          }
        }
        if(_effectMode == 4) {
          showMirrored(i, ledsrow, 1);  // merge with current line content
        } else {
          showMirrored(i, ledsrow, 0);  // overwrite with content
        }
      }
      break;
    case 3:
      solidColor(GetEQColor());
      break;
    case 5:
      theColor = GetEQColor();
      dimLeds();
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        leds[getLedIndex(i,currFrame)] = theColor;
      }
      break;
    case 6:
      theColor = GetEQColor();
      shiftLEDs(1);
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        leds[getLedIndex(i,NUM_LEDSPERROW-1)] = theColor;
      }
      break;
    case 10:
    case 11:
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        if(eq7Volumes[i] >= NOISE_LVL) {
          if(_effectMode == 10) {
            theColor = CRGB(map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 0, 255),0,0);  // red, dependent on volume
          } else {
            if(_effectMode == 11) {            //      from green(256) to blue(511)  , dim from 0-255 depending on volume
              theColor = Wheel(map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 256, 511)).nscale8(map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 0, 255));
            }
          }
        } else {
          theColor = CRGB(0,0,0);
        }
        solidColorRow(theColor, i);
      }
      break;
  }
}
