// random pixels effect

void initRandom() {
  currDelay = DELAY_NORMAL;
  LEDS.setBrightness(NORMBRIGHT);
  randomSeed(analogRead(0));   // initialize random numbers
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));  // clear all leds
}

void loopRandom() {
  dimLeds();
  leds[random(0,NUM_LEDS)] = Wheel(random(0,768));
}
