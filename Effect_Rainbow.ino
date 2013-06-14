// rainbow effect, all three rows show the same

void initRainbow() {
  //fadeCurrStep = 0; // stop any fading
  //fadeSteps = FADE_SLOW;
}

void loopRainbow() {
  for (uint16_t i=0; i < NUM_LEDSPERROW; i++) {
    ledsrow[i] = Wheel((i+currFrame) % 768);
    
    // for rainbow effect all around the hat, use this:
    // ledsrow[i] = Wheel(((i*768 / NUM_LEDSPERROW) + currFrame) % 768);
    
  }
  paintAllRows(ledsrow);
}
