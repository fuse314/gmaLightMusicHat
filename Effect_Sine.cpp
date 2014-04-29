// sine interference effect

//mode 0: sine 1 (red)
//mode 1: sine 2 (multi color)
//mode 2: sine 3 (variable color)

#include "Effect_Sine.h"
#include "LEDColorMgt.h"
#include "zGlobals.h"

EffectSine::EffectSine(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
  _cnf->currDelay = DELAY_NORMAL;
  LEDS.setBrightness(NORMBRIGHT);

  switch(_effectMode) {
    case 0:
      _xoffset = 1;
      _yoffset = -4;
      _freq = 5;
      _speed = 2;
      _color = 1;
      _var = 0;
      break;
    case 1:
      _xoffset = 0;
      _yoffset = -4;
      _freq = 6;
      _speed = 2;
      _color = 4;
      _var = 550; // color variation
      break;
    case 2:
      _xoffset = -8;
      _yoffset = 6;
      _freq = 7;
      _speed = 2;
      _color = 4;
      _var = 0;
  }
  uint8_t mlt256 = 256 / (NUM_ROWS + NUM_LEDSPERHALFROW);
  for(uint8_t y=0; y<NUM_ROWS; y++) {
    for(uint8_t x=0; x<NUM_LEDSPERHALFROW; x++) {
      _dist[y][x] = sqrt((x+_xoffset)*(x+_xoffset) + (y+_yoffset)*(y+_yoffset)) * mlt256;
    }
  }
}

void EffectSine::step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
  if(_effectMode == 2) {
    _var = _cnf->currFrame;
  }
  if(_cnf->debug != 0 && _cnf->currFrame % 200 == 0) {
    _cnf->debug = millis();
  }
  for(uint8_t y=0; y<NUM_ROWS; y++) {
    for(uint8_t x=0; x<NUM_LEDSPERHALFROW; x++) {
      _leds[getLedIndex(y,NUM_LEDSPERHALFROW+x)] = _leds[getLedIndex(y,NUM_LEDSPERHALFROW-x-1)] = 
        //HeatColor(sin8(((_dist[y][x] * _freq) - (_cnf->currFrame * _speed)%256)),_color,_var);
        HeatColor(quadwave8(((_dist[y][x] * _freq) - (_cnf->currFrame * _speed)%256)),_color,_var);
        /* float */
        //HeatColor(128.0 + (sin16(((_dist[y][x] * _freq) - (_cnf->currFrame * _speed))%65536)/256),_color,_var);
        /**/
    }
  }
  if(_cnf->debug != 0 && _cnf->currFrame % 200 == 0) {
    _cnf->debug = millis() - _cnf->debug;
  }
}

