// sine interference effect

//mode 0: sine 1 (red)
//mode 1: sine 2 (multi color)
//mode 2: sine 3 (variable color)
//mode 3: sine 4 (interference colors)

#ifndef EFFECTSINE_H
#define EFFECTSINE_H

#include "zEffectClass.cpp"
#include "LEDColorMgt.h"

class EffectSine : public EffectClass {
  protected:
  uint8_t  _dist[NUM_ROWS][NUM_LEDSPERHALFROW];
  int8_t   _xoffset;
  int8_t   _yoffset;
  uint16_t _freq;
  uint16_t _speed;
  uint8_t  _color;
  uint16_t _var;
  
  public:
  EffectSine(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
    _cnf->currDelay = DELAY_NORMAL;
    _cnf->currBright = NORMBRIGHT;
  
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
        _xoffset = 1;
        _yoffset = -5;
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
        break;
      case 3:
        _xoffset = 1;
        _yoffset = -6;
        _freq = 3;
        _speed = 2;
    }
    uint8_t mlt256 = 256 / (NUM_ROWS + NUM_LEDSPERHALFROW);
    for(uint8_t y=0; y<NUM_ROWS; y++) {
      for(uint8_t x=0; x<NUM_LEDSPERHALFROW; x++) {
        _dist[y][x] = sqrt((x+_xoffset)*(x+_xoffset) + (y+_yoffset)*(y+_yoffset)) * mlt256;
      }
    }
  }

  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
    if(_effectMode == 2) {
      _var = _cnf->currFrame;
    }
    if(_cnf->debug != 0 && _cnf->currFrame % 200 == 0) {
      _cnf->debug = millis();
    }
    for(uint8_t y=0; y<NUM_ROWS; y++) {
      for(uint8_t x=0; x<NUM_LEDSPERHALFROW; x++) {
        if(_effectMode == 3) {
          _leds[getLedIndex(y,NUM_LEDSPERHALFROW+x)].r = _leds[getLedIndex(y,NUM_LEDSPERHALFROW-x-1)].r =
            //red
            scale8_video(quadwave8(((_dist[y][x] * _freq) + (_cnf->currFrame )%256)),230);
          _leds[getLedIndex(y,NUM_LEDSPERHALFROW+x)].g = _leds[getLedIndex(y,NUM_LEDSPERHALFROW-x-1)].g =
            //green
            scale8_video(quadwave8(((_dist[y][x] * _freq) - (_cnf->currFrame * 3)%256)),180);
          _leds[getLedIndex(y,NUM_LEDSPERHALFROW+x)].b = _leds[getLedIndex(y,NUM_LEDSPERHALFROW-x-1)].b =
            //blue
            scale8_video(quadwave8(((_dist[y][x] * _freq) - (_cnf->currFrame * 2 )%256)),200);
        } else {
          _leds[getLedIndex(y,NUM_LEDSPERHALFROW+x)] = _leds[getLedIndex(y,NUM_LEDSPERHALFROW-x-1)] = 
            ColorMap(quadwave8(((_dist[y][x] * _freq) - (_cnf->currFrame * _speed)%256)),_color,_var);
        }
      }
    }
    if(_cnf->debug != 0 && _cnf->currFrame % 200 == 0) {
      _cnf->debug = millis() - _cnf->debug;
    }
  }
};
#endif

