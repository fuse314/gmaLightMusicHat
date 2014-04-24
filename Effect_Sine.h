#ifndef EFFECTSINE_H
#define EFFECTSINE_H
#include <Arduino.h>
#include "zEffectClass.h"

class EffectSine : public EffectClass {
  public:
  EffectSine(uint8_t _mode, Config_t *_cnf);
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow);
  
  protected:
  uint8_t  _dist[NUM_ROWS][NUM_LEDSPERHALFROW];
  int8_t   _xoffset;
  int8_t   _yoffset;
  uint16_t _freq;
  uint16_t _speed;
  uint8_t  _color;
};
#endif
