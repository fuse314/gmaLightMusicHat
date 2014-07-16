#ifndef EFFECTFIRE_H
#define EFFECTFIRE_H
#include <Arduino.h>
#include "zEffectClass.h"

class EffectFire : public EffectClass {
  public:
  EffectFire(uint8_t _mode, Config_t *_cnf);
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow);
  
  protected:
  // _heat holds the 8bit heat map for half of the leds (displayed mirrored)
  uint8_t _heat[NUM_ROWS][NUM_LEDSPERHALFROW];
  // _cooling defines how fast the fire "cools" off (higher value=shorter flames)
  uint8_t _cooling;
  // _sparking defines how often a spark is created at the bottom of the flame
  uint8_t _sparking;
  // _palette defines the color palette for the effect
  CRGBPalette16 _palette;
};
#endif
