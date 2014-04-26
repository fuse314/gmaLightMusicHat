// fire effect by Mark Kriegsman
// copied from http://pastebin.com/wmy3gt1P


//mode 0: fire 1
//mode 1: fire 2
//mode 2: sound fire

#include "Effect_Fire.h"
#include "LEDColorMgt.h"
#include "zGlobals.h"

EffectFire::EffectFire(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
  _cnf->currDelay = DELAY_FIRE;
  LEDS.setBrightness(NORMBRIGHT);

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
}

void EffectFire::step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {

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
   
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if(random8() < _sparking ) {
      uint8_t y = random8(7);
      _heat[row][y] = qadd8( _heat[row][y], random8(150,255) );
    }
   
    // Step 4.  Map from heat cells to LED colors
    for(uint8_t j = 0; j < NUM_LEDSPERHALFROW; j++) {
      _leds[getLedIndex(row,NUM_LEDSPERHALFROW+j)] = _leds[getLedIndex(row,NUM_LEDSPERHALFROW-j-1)] = HeatColor(_heat[row][j],0,0);
    }
  }
}

