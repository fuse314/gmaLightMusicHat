// fire effect by Mark Kriegsman
// copied from http://pastebin.com/wmy3gt1P


//mode 0: fire 1
//mode 1: fire 2
//mode 2: sound fire

#ifndef EFFECTFIRE_H
#define EFFECTFIRE_H
#include <Arduino.h>
#include "zEffectClass.cpp"
#include "LEDColorMgt.h"

class EffectFire : public EffectClass {
  protected:
  // _heat holds the 8bit heat map for half of the leds (displayed mirrored)
  uint8_t _heat[NUM_ROWS][NUM_LEDSPERHALFROW];
  // _cooling defines how fast the fire "cools" off (higher value=shorter flames)
  uint8_t _cooling;
  // _sparking defines how often a spark is created at the bottom of the flame
  uint8_t _sparking;
  // _palette defines the color palette for the effect
  CRGBPalette16 _palette;
  
  //LEDColorMgt cmgt;
  
  public:
  EffectFire(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
    _cnf->currDelay = DELAY_FIRE;
    _cnf->currBright = NORMBRIGHT;
  
    switch(_effectMode) {
      case 0:
        _cooling = 45;
        _sparking = 120;
        break;
      case 1:
        _cooling = 70;
        _sparking = 170;
        break;
    }
    _palette = HeatColors_p;
  }
  
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
    if(_effectMode == 1) {
      uint8_t _hue = _cnf->currFrame % 256;
      CRGB _darkcolor  = CHSV(_hue,255,192); // pure hue, three-quarters brightness
      CRGB _lightcolor = CHSV(_hue,128,255); // half 'whitened', full brightness
      _palette = CRGBPalette16( CRGB::Black, _darkcolor, _lightcolor, CRGB::White);
    }
    if(_effectMode == 2) {
      _cooling = map(_cnf->eq7Vol[1],0,255, 40,90);
      _sparking = map(_cnf->eq7Vol[1],0,255, 32,100);
    }
  
    for (uint8_t row = 0; row < NUM_ROWS; row++) {
    // Step 1.  Cool down every cell a little
      for(uint8_t i = 0; i < NUM_LEDSPERHALFROW; i++) {
        _heat[row][i] = qsub8( _heat[row][i],  random8(0, ((_cooling * 10) / NUM_LEDSPERHALFROW) + 2));
      }
     
      // Step 2.  Heat from each cell drifts 'up' and diffuses a little
      for(uint8_t k= NUM_LEDSPERHALFROW - 1; k > 0; k--) {
        _heat[row][k] = (_heat[row][k - 1] + _heat[row][k - 2] + _heat[row][k - 2] ) / 3;
      }
      // step 2.5 Heat from each cell drifts 'left' and diffuses a little
      if(row < (NUM_ROWS-1)) {
        for(uint8_t m=NUM_LEDSPERHALFROW - 1; m > 0; m--) {
          _heat[row+1][m] = (_heat[row+1][m] + _heat[row+1][m] + _heat[row+1][m] + _heat[row][m] ) / 4;
        }
      }
     
      // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
      if(random8() < _sparking ) {
        uint8_t y = random8(7);
        _heat[row][y] = qadd8( _heat[row][y], random8(150,255) );
      }
     
      // Step 4.  Map from heat cells to LED colors
      uint8_t palIndex;
      for(uint8_t j = 0; j < NUM_LEDSPERHALFROW; j++) {
        palIndex = scale8(_heat[row][j], 240); // scale for better results with palette colors
        _leds[/*cmgt.*/getLedIndex(row,NUM_LEDSPERHALFROW+j)] = _leds[/*cmgt.*/getLedIndex(row,NUM_LEDSPERHALFROW-j-1)] = ColorFromPalette(_palette, palIndex);
      }
    }
  }
};
#endif

