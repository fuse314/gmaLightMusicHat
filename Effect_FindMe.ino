// Find Me Effect (spinning white light), all three rows show the same

uint8_t iFindMeWidth = 5;

void initFindMe() {
}

void loopFindMe() {
  memset(ledsrow, 0, NUM_LEDSPERROW * 3);
  uint8_t startIndex = currFrame % NUM_LEDSPERROW;
  for (uint8_t i = startIndex; i < startIndex + iFindMeWidth; i++) {
    if(i >= NUM_LEDSPERROW) {
      ledsrow[i-NUM_LEDSPERROW] = GetColor(MAXBRIGHT, MAXBRIGHT, MAXBRIGHT);   // change color here
    } else {
      ledsrow[i] = GetColor(MAXBRIGHT, MAXBRIGHT, MAXBRIGHT);   // change color here
    }
  }
  paintAllRows(ledsrow);
}
