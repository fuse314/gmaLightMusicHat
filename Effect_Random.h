#ifndef EFFECTRANDOM_H
#define EFFECTRANDOM_H

#include <Arduino.h>
#include "zEffectClass.h"

#define RANDOM_WIDTH 5      // width of random colored band (mode 1)
#define RANDOM_NUM_LINES 9  // number of random lines (mode x)

class EffectRandom : public EffectClass {
  public:
  EffectRandom( uint8_t _mode, Config_t *_cnf);
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _rowleds);
  
  protected:
  
  struct rndline_t {
    uint16_t start;       // start index
    uint8_t  length;      // length
    uint8_t  hue;         // hue
    uint8_t  anim_idx;    // animation index (brightness)
    uint8_t  anim_speed;  // animation speed
  };
  
  rndline_t _rndLines[RANDOM_NUM_LINES];  // array of random line variables
  
  void initLine(rndline_t *_line);       // initialize line variable
  void stepLine(rndline_t *_line);       // step line animation
};
#endif
