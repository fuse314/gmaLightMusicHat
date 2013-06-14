
struct CRGB Wheel(uint16_t WheelPos)
{
  struct CRGB ret;
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
  
  ret.r = map(ret.r, 0, 255, 0, NORMBRIGHT);  // limit brightness
  ret.g = map(ret.g, 0, 255, 0, NORMBRIGHT);
  ret.b = map(ret.b, 0, 255, 0, NORMBRIGHT);
  
  return(ret);
}

struct CRGB GetColor(uint8_t r, uint8_t g, uint8_t b) {
  struct CRGB ret;
  ret.r = r;
  ret.g = g;
  ret.b = b;
  return(ret);
}

void SetSolidColor(CRGB color) {
  for (int i=0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
}

void showMirrored( uint8_t row, struct CRGB* halfleds ) {
  //paint 19 leds mirrored to row (0,1,2)
  if(row >= NUM_ROWS)
    row = NUM_ROWS-1;
  uint16_t startindex = NUM_LEDSPERROW * row;
  uint16_t endindex = startindex + NUM_LEDSPERROW - 1
  for(uint8_t i=0; i<NUM_LEDSPERHALFROW; i++) {
    leds[startindex+i] = halfleds[i];
    leds[endindex-i] = halfleds[i];
  }
}

void paintAllRows( struct CRGB* rowleds ) {
  // paint all rows with rowleds
  for(uint8_t i=0; i<NUM_ROWS; i++) {
    uint16_t startindex = NUM_LEDSPERROW * i;
    if(i % 2 == 0) {
      memcpy(leds[startindex], rowleds, NUM_LEDSPERROW*3);
    } else {
      for(uint16_t j=0; j<NUM_LEDSPERROW; j++) {
        led[startindex+j] = rowleds[NUM_LEDSPERROW-j-1];
      }
    }
  }
}
