// sine interference effect

//mode 0: sine 1
//mode 1: sine 2

#include "Effect_Sine.h"
#include "LEDColorMgt.h"
#include "zGlobals.h"

EffectSine::EffectSine(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
  _cnf->currDelay = DELAY_NORMAL;
  LEDS.setBrightness(NORMBRIGHT);

  switch(_effectMode) {
    case 0:
      _xoffset = 1;
      _yoffset = 6;
      _freq = 490;
      _speed = 900;
      _color = 1;
      break;
    case 1:
      _xoffset = 0;
      _yoffset = 3;
      _freq = 730;
      _speed = 1000;
      _color = 2;
      break;
  }
  uint8_t mlt256 = 256 / (NUM_ROWS + NUM_LEDSPERHALFROW);
  for(uint8_t y=0; y<NUM_ROWS; y++) {
    for(uint8_t x=0; x<NUM_LEDSPERHALFROW; x++) {
      _dist[y][x] = sqrt((x+_xoffset)*(x+_xoffset) + (y+_yoffset)*(y+_yoffset)) * mlt256;
    }
  }
}

void EffectSine::step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
  for(uint8_t y=0; y<NUM_ROWS; y++) {
    for(uint8_t x=0; x<NUM_LEDSPERHALFROW; x++) {
      _leds[getLedIndex(y,NUM_LEDSPERHALFROW+x)] = _leds[getLedIndex(y,NUM_LEDSPERHALFROW-x-1)] = 
        HeatColor(128.0 + (sin16(((_dist[y][x] * _freq) - (_cnf->currFrame * _speed))%65536)/256),_color);
    }
  }
}

