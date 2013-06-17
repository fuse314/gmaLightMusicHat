//mode 0: simple sound
//mode 1: rainbow sound
//mode 2: solid color sound
//mode 3: simple sound with rainbow underlay
//mode 4: rotating sound graph
uint8_t sound_Mode;

void initSound(uint8_t _mode) {
  sound_Mode = _mode;
  LEDS.setBrightness(NORMBRIGHT);
  if(sound_Mode == 4) {
    memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));  // clear all leds
  }
}

void loopSound() {
  GetEQ7();
  if(sound_Mode == 3) {
    fill_rainbow( &(ledsrow[0]), NUM_LEDSPERROW, currFrame % 256);
    paintAllRows(ledsrow);
  }
  if(sound_Mode == 0 || sound_Mode == 1 || sound_Mode == 3) {
    memset(ledsrow, 0, NUM_LEDSPERHALFROW * sizeof(struct CRGB));
  }
  
  
  switch (sound_Mode) {
    case 0:
    case 1:
    case 3:
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        if(eq7Volumes[i] > NOISE_LVL) {
          uint8_t soundlvl = map(eq7Volumes[i], NOISE_LVL, 1024, 1, NUM_LEDSPERHALFROW);
          for(uint8_t j=0; j<soundlvl; j++) {
            if(sound_Mode == 1) {
              ledsrow[j] = Wheel(currFrame % 256);
            } else {
              ledsrow[j] = getEQColor();
            }
          }
        }
        if(sound_Mode == 3) {
          showMirrored(i, ledsrow, 1);  // merge with current line content
        } else {
          showMirrored(i, ledsrow, 0);  // overwrite with content
        }
      }
      break;
    case 2:
      LEDS.showColor(getEQColor());
      break;
    case 4:
      struct CRGB theColor = getEQColor();
      dimLeds();
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        leds[getLedIndex(i,currFrame)] = theColor;
      }
      break;
  }
}
