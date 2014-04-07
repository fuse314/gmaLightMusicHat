// fire effect by Mark Kriegsman
// copied from http://pastebin.com/wmy3gt1P


//mode 0: red kr effect
//mode 1: blue kr effect
//mode 2: green kr effect
//mode 3: rainbow kr effect 

#include "Effect_Fire.h"
#include "LEDColorMgt.h"
#include "gmaLightCommon.h"

EffectFire::EffectFire(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
  _cnf->currDelay = DELAY_FIRE;
  LEDS.setBrightness(NORMBRIGHT);
  clearAllLeds();

  switch(_effectMode) {
    case 0:
      _cooling = 50;
      _sparking = 122;
      break;
    case 1:
      _cooling = 80;
      _sparking = 180;
      break;
  }
}

void EffectFire::step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow) {

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
      _leds[getLedIndex(row,NUM_LEDSPERHALFROW+j)] = _leds[getLedIndex(row,NUM_LEDSPERHALFROW-j-1)] = HeatColor(_heat[row][j]);
    }
  }
}

