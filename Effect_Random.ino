//mode 0: random pixels effect
//mode 1: random color block sweep (iRandomWith wide block, one round per color)
//mode 2: random color solid sweep (fill leds with one color, next color)
#define iRandomWidth 4  // width of random color bar (mode 1)

void initRandom(uint8_t _mode) {
  effectMode = _mode;
  currDelay = DELAY_NORMAL;
  LEDS.setBrightness(NORMBRIGHT);
  randomSeed(analogRead(0));   // initialize random numbers
  if(effectMode == 0) {
    clearAllLeds();
  }
  if(effectMode == 1) {
    currColor = Wheel(random(0,768));
  }
}

void loopRandom() {

  if(effectMode == 1 || effectMode == 2) {
    if(currFrame % NUM_LEDS == 0) {  // new color on new round
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
        for(uint8_t j=0; j<iRandomWidth; j++) {
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
