// Find Me Effect (spinning white light), all three rows show the same

uint8_t iFindMeWidth = 4;

void initFindMe() {
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));  // clear all leds
  LEDS.setBrightness(MAXBRIGHT);
}

void loopFindMe() {
  dimLeds();
  for(uint8_t i=0; i<NUM_ROWS; i++) {
    for(uint8_t j=0; j<iFindMeWidth; j++) {
      leds[getLedIndex(i,currFrame+j)] = CRGB(255, 0, 0); // red
      leds[getLedIndex(i,currFrame+NUM_LEDSPERHALFROW+j)] = CRGB(0, 0, 255); // blue
    }
  }
}
