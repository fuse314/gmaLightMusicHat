//mode 0: random pixels effect
//mode 1: random color block sweep (iRandomWith wide block, one round per color)
//mode 2: random color solid sweep (fill leds with one color, next color)

#include "zEffectClass.h"
#include "Effect_Random.h"

EffectRandom::EffectRandom(uint8_t _mode) : EffectClass(_mode) {
  currDelay = DELAY_SLOW;
  LEDS.setBrightness(NORMBRIGHT);
  randomSeed(analogRead(0));   // initialize random numbers
  if(effectMode == 0) {
    clearAllLeds();
  }
  if(effectMode == 1) {
    currColor = Wheel(random(0,768));
  }
}

void EffectRandom::step() {

  if(effectMode == 1 || effectMode == 2) {
    if(currFrame % NUM_LEDSPERROW == 0) {  // new color on new round
      currColor = Wheel(random(0,768));
    }
  }

  switch(effectMode) {
    case 0:
      dimLeds();
      leds[random(0,NUM_LEDS)] = Wheel(random(0,768));
    break;
    case 1:
      clearAllLeds();
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        for(uint8_t j=0; j<RANDOM_WIDTH; j++) {
          leds[getLedIndex(i,currFrame+j)] = currColor;
        }
      }
    break;
    case 2:
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        leds[getLedIndex(i,currFrame)] = currColor;
      }
    break;
  }
}
