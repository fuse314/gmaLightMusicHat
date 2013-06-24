// Find Me Effect (spinning white light), all three rows show the same

uint8_t iFindMeWidth = 2;

void initFindMe() {
  currDelay = DELAY_SLOW;
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));  // clear all leds
  LEDS.setBrightness(MAXBRIGHT);
}

void loopFindMe() {
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));  // clear all leds
  for(uint8_t i=0; i<NUM_ROWS; i++) {
    for(uint8_t j=0; j<iFindMeWidth; j++) {
      leds[getLedIndex(i,currFrame+j)] = CRGB(255,255,255);
      leds[getLedIndex(i,currFrame+NUM_LEDSPERHALFROW+j)] = CRGB(255,255,255);
    }
  }
  /* police siren blue red pattern
  dimLeds();
  for(uint8_t i=0; i<NUM_ROWS; i++) {
    for(uint8_t j=0; j<iFindMeWidth; j++) {
      leds[getLedIndex(i,currFrame+j)] = CRGB(255, 0, 0); // red
      leds[getLedIndex(i,currFrame+NUM_LEDSPERHALFROW+j)] = CRGB(0, 0, 255); // blue
    }
  }
  */
}
