#ifndef EFFECTFIRE_H
#define EFFECTFIRE_H
#include <Arduino.h>
#include "zEffectClass.h"

class EffectFire : public EffectClass {
  public:
  EffectFire(uint8_t _mode, Config_t *_cnf);
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow);
  
  protected:
  uint8_t _heat[NUM_ROWS][NUM_LEDSPERHALFROW];
  // COOLING: How much does the air cool as it rises?
  // Less cooling = taller flames.  More cooling = shorter flames.
  // Default 55, suggested range 20-100
  uint8_t _cooling;
  // SPARKING: What chance (out of 255) is there that a new spark will be lit?
  // Higher chance = more roaring fire.  Lower chance = more flickery fire.
  // Default 120, suggested range 50-200.
  uint8_t _sparking;
};
#endif
