//mode 1: volume dependent width, eqColor bars
//mode 2: volume dependent width, rainbow bars
//mode 3: all leds solid eqColor
//mode 4: volume dependent width, eqColor bars with rainbow underlay
//mode 5: rotating eqColor sound graph
//mode 6: fixed eqColor sound graph with rotating (shift all leds)
//mode 7: volume dependent width, volume dependent color blue to red bars
//mode 8: volume dependent width, volume dependent color green to blue bars
//mode 9: volume dependent width, red bars with blue background
//mode 10: volume dependent brightness, red solid color per row
//mode 11: volume dependent brightness, volume dependent color green to blue per row
uint8_t sound_Mode;

void initSound(uint8_t _mode) {
  sound_Mode = _mode;
  currDelay = DELAY_NORMAL;
  LEDS.setBrightness(NORMBRIGHT);
  if(sound_Mode == 5) {
    memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));  // clear all leds
  }
}

void loopSound() {
  GetEQ7();
  if(sound_Mode == 4) {
    fill_rainbow( &(ledsrow[0]), NUM_LEDSPERROW, currFrame % 256);
    paintAllRows(ledsrow);
  }
  if(sound_Mode == 9) {
    solidColor(CRGB(0,0,128)); // blue base color
  }
  if(sound_Mode == 1 || sound_Mode == 2 || sound_Mode == 4 || sound_Mode == 7 || sound_Mode == 10) {
    memset(ledsrow, 0, NUM_LEDSPERHALFROW * sizeof(struct CRGB));
  }
  
  struct CRGB theColor;
  switch (sound_Mode) {
    case 1:
    case 2:
    case 4:
    case 7:
    case 8:
    case 9:
      if(sound_Mode == 1 || sound_Mode == 2 || sound_Mode == 4) {
        theColor = getEQColor();
      }
      if(sound_Mode == 9) {
        theColor = CRGB(255,0,0); // red bar
      }
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        if(eq7Volumes[i] >= NOISE_LVL) {
          if(sound_Mode == 7) {  // color depending on volume from blue(512) to red(767)
            theColor = Wheel(map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 512, 767));
          }
          if(sound_Mode == 8) {  // color depending on volume from green(256) to blue(511)
            theColor = Wheel(map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 256, 511));
          }
          uint8_t soundlvl = map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 1, NUM_LEDSPERHALFROW);
          for(uint8_t j=0; j<soundlvl; j++) {
            if(sound_Mode == 2) {
              ledsrow[j] = Wheel(currFrame);
            } else {
              ledsrow[j] = theColor;  // idea: dim lights from the middle in higher volumes... something with .nscale8(0-255);
            }
          }
        }
        if(sound_Mode == 4 || sound_Mode == 9) {
          showMirrored(i, ledsrow, 1);  // merge with current line content
        } else {
          showMirrored(i, ledsrow, 0);  // overwrite with content
        }
      }
      break;
    case 3:
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
        leds[getLedIndex(i,0)] = theColor;
      }
      break;
    case 10:
    case 11:
      for(uint8_t i=0; i<NUM_ROWS; i++) {
        if(eq7Volumes[i] >= NOISE_LVL) {
          if(sound_Mode == 10) {
            theColor = CRGB(map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 0, 255),0,0);  // red, dependent on volume
          } else {
            if(sound_Mode == 11) {            //      from blue(512) to red(767)  , dim from 0-255 depending on volume
              theColor = Wheel(map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 512, 767)).nscale8(map(eq7Volumes[i], NOISE_LVL, MAX_LVL, 0, 255));
            }
          }
        } else {
          theColor = CRGB(0,0,0);
        }
        uint16_t endIndex = (i+1)*NUM_LEDSPERROW;
        for(uint16_t j=i*NUM_LEDSPERROW; j<endIndex; j++) {
          led[j] = theColor;
        }
      }
      break;
  }
}
