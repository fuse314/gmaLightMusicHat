// Find Me Effect (spinning white light), all three rows show the same

#include "zEffectClass.h"
#include "Effect_FindMe.h"

EffectFindMe::EffectFindMe(uint8_t _mode) : EffectClass(_mode) {
  currDelay = DELAY_SLOW;
  clearAllLeds();
  LEDS.setBrightness(MAXBRIGHT);
  currColor = CRGB(255,255,255);
}

void EffectFindMe::step() {
  clearAllLeds();
  for(uint8_t i=0; i<NUM_ROWS; i++) {
    for(uint8_t j=0; j<FINDME_WIDTH; j++) {
      leds[getLedIndex(i,currFrame+j)] = currColor;  // for police blue-red pattern use CRGB(255,0,0)
      leds[getLedIndex(i,currFrame+NUM_LEDSPERHALFROW+j)] = currColor;  // and CRGB(0,0,255)
    }
  }
}
