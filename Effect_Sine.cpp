// sine interference effect

//mode 0: sine 1
//mode 1: sine 2

#include "Effect_Sine.h"
#include "LEDColorMgt.h"
#include "zGlobals.h"

EffectFire::EffectSine(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
  _cnf->currDelay = DELAY_NORMAL;
  LEDS.setBrightness(NORMBRIGHT);

  switch(_effectMode) {
    case 0:
      sinval[0] = 17;
      sinval[1] = 31;
      sinval[2] = 47;
      break;
    case 1:
      sinval[0] = 23;
      sinval[1] = 37;
      sinval[2] = 43;
      break;
  }
}

void EffectSine::step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {
  
  
}

