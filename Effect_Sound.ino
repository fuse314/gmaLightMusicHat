//mode 1: simple sound
//mode 2: rainbow sound
//mode 3: solid color sound
//mode 4: simple sound with rainbow underlay
//mode 5: rotating sound graph
//---mode 6: fixed sound graph with rotating (shift position)
uint8_t sound_Mode;

void initSound(uint8_t _mode) {
  sound_Mode = _mode;
  currDelay = DELAY_NORMAL;
  LEDS.setBrightness(NORMBRIGHT);
  if(sound_Mode == 5 || sound_Mode == 3) {
    memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));  // clear all leds
  }
}

void loopSound() {
  GetEQ7();
  if(sound_Mode == 4) {
    fill_rainbow( &(ledsrow[0]), NUM_LEDSPERROW, currFrame % 256);
    paintAllRows(ledsrow);
  }
  if(sound_Mode == 1 || sound_Mode == 2 || sound_Mode == 4) {
    memset(ledsrow, 0, NUM_LEDSPERHALFROW * sizeof(struct CRGB));
  }
  
  struct CRGB theColor;
  switch (sound_Mode) {
    case 1:
    case 2:
    case 4:
      theColor = getEQColor();
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        if(eq7Volumes[i] > NOISE_LVL) {
          uint8_t soundlvl = map(eq7Volumes[i], NOISE_LVL, 1023, 1, NUM_LEDSPERHALFROW);
          for(uint8_t j=0; j<soundlvl; j++) {
            if(sound_Mode == 2) {
              ledsrow[j] = Wheel(currFrame);
            } else {
              ledsrow[j] = theColor;  // idea: dim lights from the middle in higher volumes... something with .nscale8(0-255);
            }
          }
        }
        if(sound_Mode == 4) {
          showMirrored(i, ledsrow, 1);  // merge with current line content
        } else {
          showMirrored(i, ledsrow, 0);  // overwrite with content
        }
      }
      break;
    case 3:
      //LEDS.showColor(getEQColor());
      solidColor(getEQColor());
      break;
    case 5:
      theColor = getEQColor();
      dimLeds();
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        leds[getLedIndex(i,currFrame)] = theColor;
      }
      break;
    case 6:
      theColor = getEQColor();
      shiftLEDs(1);
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        leds[getLedIndex(i,NUM_LEDSPERROW-1)] = theColor;
      }
      break;
  }
}
