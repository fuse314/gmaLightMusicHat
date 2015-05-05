// sine interference effect

//mode 0: sine 1 (red)
//mode 1: sine 2 (multi color)
//mode 2: sine 3 (variable color)

#ifndef EFFECTSINE_H
#define EFFECTSINE_H

#include "zEffectClass.h"
#include "LEDColorMgt.h"

class EffectSine : public EffectClass {
  protected:
  uint8_t  _dist[M_WIDTH][M_HALFWIDTH];
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
    }
    uint8_t mlt256 = 256 / (M_HALFWIDTH + M_HEIGHT);
    for(uint8_t y=0; y<M_HEIGHT; y++) {
      for(uint8_t x=0; x<M_HALFWIDTH; x++) {
        _dist[x][y] = sqrt((x+_xoffset)*(x+_xoffset) + (y+_yoffset)*(y+_yoffset)) * mlt256;
      }
    }
  }

  void step(Config_t *_cnf, CRGB* _leds) {
    if(_effectMode == 2) {
      _var = _cnf->currFrame;
    }
    for(uint8_t y=0; y<M_HEIGHT; y++) {
      for(uint8_t x=0; x<M_HALFWIDTH; x++) {
          _leds[XY(M_HALFWIDTH+x,y)] = _leds[XY(M_HALFWIDTH-x-1,y)] = 
            ColorMap(quadwave8(((_dist[x][y] * _freq) - (_cnf->currFrame * _speed)%256)),_color,_var);
      }
    }
  }
};
#endif

