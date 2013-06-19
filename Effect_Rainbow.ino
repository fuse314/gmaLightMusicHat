// rainbow effect, all three rows show the same

void initRainbow() {
  LEDS.setBrightness(NORMBRIGHT);
}

void loopRainbow(uint8_t theMode) {
  switch(theMode) {
    case 0:
      fill_rainbow( &(ledsrow[0]), NUM_LEDSPERROW, currFrame % 256);
      paintAllRows(ledsrow);
      break;
    case 1:
      LEDS.showColor(Wheel(currFrame));
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
