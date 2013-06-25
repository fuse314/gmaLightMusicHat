// Find Me Effect (spinning white light), all three rows show the same

#define iFindMeWidth 2

void initFindMe() {
  currDelay = DELAY_SLOW;
  clearAllLeds();
  LEDS.setBrightness(MAXBRIGHT);
  currColor = CRGB(255,255,255);
}

void loopFindMe() {
  clearAllLeds();
  for(uint8_t i=0; i<NUM_ROWS; i++) {
    for(uint8_t j=0; j<iFindMeWidth; j++) {
      leds[getLedIndex(i,currFrame+j)] = currColor;  // for police blue-red pattern use CRGB(255,0,0)
      leds[getLedIndex(i,currFrame+NUM_LEDSPERHALFROW+j)] = currColor;  // and CRGB(0,0,255)
    }
  }
}
