//mode 0: simple sound
//mode 1: rainbow sound
//mode 2: solid color sound
uint8_t sound_Mode;

void initSound(uint8_t _mode) {
  sound_Mode = _mode;
  LEDS.setBrightness(NORMBRIGHT);
}

void loopSound() {
  GetEQ7();
  uint16_t howLoud = max(eq7Values[5], max(eq7Values[4], max(eq7Values[3], eq7Values[2])));
  switch (sound_Mode) {
    case 0:
    case 1:
      memset(ledsrow, 0, NUM_LEDSPERHALFROW * 3);
      if(howLoud > NOISE_LVL) {
        uint8_t soundlvl = map(howLoud, NOISE_LVL, 1024, 1, NUM_LEDSPERHALFROW);
        for(uint8_t i=0; i<soundlvl; i++) {
          if(sound_Mode == 0) {
            ledsrow[i] = getEQColor();
          } else {
            ledsrow[i] = Wheel(currFrame % 256);
          }
        }
      }
      showMirrored(0,ledsrow);  // maybe use high, mid, low volume for rows...
      showMirrored(1,ledsrow);
      showMirrored(2,ledsrow);
      break;
    case 2:
      LEDS.showColor(getEQColor());
      break;
  }
}
