//mode 0: red kr effect
//mode 1: blue kr effect
//mode 2: green kr effect
#define iKRWith = 6;

void initKR(uint8_t _mode) {
  effectMode = _mode;
  currDelay = DELAY_NORMAL;
  LEDS.setBrightness(NORMBRIGHT);
  switch(effectMode) {
    case 0:
      currColor = CRGB(255,32,0); // red
    break;
    case 1:
      currColor = CRGB(32,128,255); // blue-ish
    break;
    case 2:
      currColor = CRGB(0,255,0); // green
    break;
  }
}

void loopKR() {

  //switch(effectMode) {
  //  case 0:
  //  case 1:
  //  case 2:
      clearAllLeds();
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        uint16_t startIndex = getKRLedIndex(i, currFrame, iKRWidth);
        uint16_t endIndex = startIndex + iKRWidth;
        for(uint16_t j=startIndex; j<endIndex; j++) {
          if((j==startIndex || j==endIndex-1) && i%2==0) { // fade edges for better effect
            led[j] = currColor.nscale8(128);
          } else {
            led[j] = currColor;
          }
        }
      }
  //  break;
  //}
}
