// rainbow effect, all three rows show the same
uint8_t rainbowMode = 0;

void initRainbow(uint8_t _mode) {
  rainbowMode = _mode;
  LEDS.setBrightness(NORMBRIGHT);
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));  // clear all leds
}

void loopRainbow() {
  switch(rainbowMode) {
    case 0:
      fill_rainbow( &(ledsrow[0]), NUM_LEDSPERROW, currFrame % 256);
      paintAllRows(ledsrow);
      break;
    case 1:
      LEDS.showColor(Wheel(currFrame));
      break;
    case 2:
      fill_rainbow( &(leds[0]), NUM_LEDS, currFrame % 256);
      break;
  }
  /*
  for (uint16_t i=0; i < NUM_LEDSPERROW; i++) {
    ledsrow[i] = Wheel((i+currFrame) % 768);
    
    // for rainbow effect all around the hat, use this:
    // ledsrow[i] = Wheel(((i*768 / NUM_LEDSPERROW) + currFrame) % 768);
    
  }
  paintAllRows(ledsrow);
  */
}
