
struct CRGB Wheel(uint16_t WheelPos)
{
  CHSV rainbowcolor;
  rainbowcolor.hue = WheelPos % 256;
  rainbowcolor.saturation = 187;
  rainbowcolor.value = 255;
  struct CRGB ret;
  hsv2rgb_rainbow( rainbowcolor, ret);
  
  /*
  switch(WheelPos >> 8)
  {
    case 0:      // red to green
      ret.r=255 - WheelPos % 256;
      ret.g=WheelPos % 256;
      ret.b=0;
      break; 
    case 1:      //green to blue
      ret.r=0;
      ret.g=255 - WheelPos % 256;
      ret.b=WheelPos % 256;
      break; 
    case 2:       //blue to red
      ret.r=WheelPos % 256;
      ret.g=0;
      ret.b=255 - WheelPos % 256;
      break; 
  }
  */
  return(ret);
}

/*
struct CRGB GetColor(uint8_t r, uint8_t g, uint8_t b) {
  struct CRGB ret;
  ret.r = r;
  ret.g = g;
  ret.b = b;
  return(ret);
}
*/

/*
void SetSolidColor(CRGB color) {
  for (int i=0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
}
*/

void showMirrored( uint8_t row, struct CRGB* halfleds, uint8_t merge ) {
  //paint 19 leds mirrored to row (0,1,2)
  if(row >= NUM_ROWS)
    row = NUM_ROWS-1;
  uint16_t startindex = NUM_LEDSPERROW * row;
  uint16_t endindex = startindex + NUM_LEDSPERROW - 1;
  for(uint8_t i=0; i<NUM_LEDSPERHALFROW; i++) {
    if(merge == 1) {
      leds[startindex+i] += halfleds[NUM_LEDSPERHALFROW-1-i];
      leds[endindex-i] += halfleds[NUM_LEDSPERHALFROW-1-i];
    } else {
      leds[startindex+i] = halfleds[NUM_LEDSPERHALFROW-1-i];
      leds[endindex-i] = halfleds[NUM_LEDSPERHALFROW-1-i];
    }
  }
}

void paintAllRows( struct CRGB* rowleds ) {
  // paint all rows with rowleds
  for(uint8_t i=0; i<NUM_ROWS; i++) {
    uint16_t startindex = NUM_LEDSPERROW * i;
    for(uint16_t j=0; j<NUM_LEDSPERROW; j++) {
      if(i % 2 == 0) {
        leds[startindex+j] = rowleds[j];
      } else {
        leds[startindex+j] = rowleds[NUM_LEDSPERROW-j-1];
      }
    }
  }
}

uint16_t getLedIndex( uint8_t row, uint16_t rowindex) {
  uint16_t ret = rowindex % NUM_LEDSPERROW;
  if(row % 2 == 0) {
    ret += row * NUM_LEDSPERROW;
  } else {
    ret = (row+1) * NUM_LEDSPERROW - 1 - ret;
  }
  return ret;
}

void dimLeds() {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
    if(leds[i].r > DIMSPEED) { leds[i].r -= leds[i].r / DIMSPEED; } else { if(leds[i].r > 0) leds[i].r--; }
    if(leds[i].g > DIMSPEED) { leds[i].g -= leds[i].g / DIMSPEED; } else { if(leds[i].g > 0) leds[i].g--; }
    if(leds[i].b > DIMSPEED) { leds[i].b -= leds[i].b / DIMSPEED; } else { if(leds[i].b > 0) leds[i].b--; }
  }
}

