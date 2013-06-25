//mode 0: rainbow all three rows the same
//mode 1: solid color rainbow all leds the same
//mode 2: rainbow through all leds, results in right-left-right run due to led configuration

void initRainbow(uint8_t _mode) {
  effectMode = _mode;
  currDelay = DELAY_FAST;
  LEDS.setBrightness(NORMBRIGHT);
  clearAllLeds();
}

void loopRainbow() {
  switch(effectMode) {
    case 0:
      fill_rainbow( &(ledsrow[0]), NUM_LEDSPERROW, currFrame % 256);
      paintAllRows(ledsrow);
      break;
    case 1:
      solidColor(Wheel(currFrame));
      break;
    case 2:
      fill_rainbow( &(leds[0]), NUM_LEDS, currFrame % 256);
      break;
  }
}
