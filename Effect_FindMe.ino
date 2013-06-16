// Find Me Effect (spinning white light), all three rows show the same

uint8_t iFindMeWidth = 5;

void initFindMe() {
  LEDS.setBrightness(MAXBRIGHT);
}

void loopFindMe() {
  memset(ledsrow, 0, NUM_LEDSPERROW * 3);
  uint8_t startIndex = currFrame % NUM_LEDSPERROW;
  for (uint8_t i = startIndex; i < startIndex + iFindMeWidth; i++) {
    if(i >= NUM_LEDSPERROW) {
      ledsrow[i-NUM_LEDSPERROW] = CRGB(255, 255, 255);   // change color here
    } else {
      ledsrow[i] = CRGB(255, 255, 255);   // change color here
    }
  }
  paintAllRows(ledsrow);
}
