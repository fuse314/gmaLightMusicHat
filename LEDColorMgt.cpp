#include "gmaLightMusicHat.h"
#include "LEDColorMgt.h"

CRGB Wheel(uint16_t _wheelPos)
{

  //only has 256 hues... very choppy animation especially with all leds in the same color
  /*
  CHSV rainbowcolor;
  rainbowcolor.hue = WheelPos % 256;
  rainbowcolor.saturation = 187;
  rainbowcolor.value = 255;
  struct CRGB ret;
  hsv2rgb_rainbow( rainbowcolor, ret);
  */
  _wheelPos = _wheelPos % 768;
  CRGB ret;
  switch(_wheelPos >> 8)
  {
    case 0:      // 0 - 255 = red to green
      ret.r=255 - _wheelPos % 256;
      ret.g=_wheelPos % 256;
      ret.b=0;
      break; 
    case 1:      // 256 - 511 = green to blue
      ret.r=0;
      ret.g=255 - _wheelPos % 256;
      ret.b=_wheelPos % 256;
      break; 
    case 2:       // 512 - 767 = blue to red
      ret.r=_wheelPos % 256;
      ret.g=0;
      ret.b=255 - _wheelPos % 256;
      break; 
  }
  
  return(ret);
}


void showMirrored( uint8_t _row, CRGB* _halfleds, uint8_t _merge ) {
  //paint 19 leds mirrored to one row (0,1,2)
  if(_row >= NUM_ROWS)
    _row = NUM_ROWS-1;
  uint16_t startindex = NUM_LEDSPERROW * _row;
  uint16_t endindex = startindex + NUM_LEDSPERROW - 1;
  for(uint8_t i=0; i<NUM_LEDSPERHALFROW; i++) {
    if(_merge == 1) {
      leds[startindex+i] += _halfleds[NUM_LEDSPERHALFROW-1-i];
      leds[endindex-i] += _halfleds[NUM_LEDSPERHALFROW-1-i];
    } else {
      leds[startindex+i] = _halfleds[NUM_LEDSPERHALFROW-1-i];
      leds[endindex-i] = _halfleds[NUM_LEDSPERHALFROW-1-i];
    }
  }
}

void paintAllRows( CRGB* _rowleds ) {
  // paint all rows with rowleds
  for(uint8_t i=0; i<NUM_ROWS; i++) {
    uint16_t startindex = NUM_LEDSPERROW * i;
    for(uint16_t j=0; j<NUM_LEDSPERROW; j++) {
      if(i % 2 == 0) {
        leds[startindex+j] = _rowleds[j];
      } else {
        leds[startindex+j] = _rowleds[NUM_LEDSPERROW-j-1];
      }
    }
  }
}

void solidColor( CRGB _color) {
  // set all leds to _color
  for(uint16_t i=0; i<NUM_LEDS; i++) {
    leds[i] = _color;
  }
}
void solidColorLedsRow( CRGB _color) {
  for(uint16_t i=0; i<NUM_LEDSPERROW; i++) {
    ledsrow[i] = _color;
  }
}

void solidColorRow( CRGB _color, uint8_t _row ) {
  // set one row of leds to _color
  if(_row >= NUM_ROWS)
    _row = NUM_ROWS-1;
  uint16_t endIndex = (_row+1)*NUM_LEDSPERROW;
  for(uint16_t i=_row*NUM_LEDSPERROW; i<endIndex; i++) {
    leds[i] = _color;
  }
}

void shiftLEDs( int8_t _distance ) {
  // shift content of leds per row in one direction or other (positive / negative number), clear leftover leds
  if(_distance == 0) { return; }  // shift by zero: do nothing.
  for(uint8_t i=0; i<NUM_ROWS; i++) {
    if(_distance > 0) {
      for(uint16_t j=0; j<NUM_LEDSPERROW-_distance; j++) {
        leds[getLedIndex(i,j)] = leds[getLedIndex(i,j+_distance)];  // higher index to lower index, iterate upwards
      }
      for(uint16_t j=NUM_LEDSPERROW-_distance; j<NUM_LEDSPERROW; j++) {
        leds[getLedIndex(i,j)] = CRGB(0,0,0);  // clear leftover leds
      }
    } else {
      for(uint16_t j=NUM_LEDSPERROW+NUM_LEDSPERROW+_distance-1; j>=NUM_LEDSPERROW; j--) { // make sure j never goes below 0
        leds[getLedIndex(i,j)] = leds[getLedIndex(i,j+_distance)];  // lower index to higher index, iterate downwards
      }
      for(uint16_t j=0; j<_distance; j++) {
        leds[getLedIndex(i,j)] = CRGB(0,0,0);  // clear leftover leds
      }
    }
  }
}

uint16_t getLedIndex( uint8_t _row, uint16_t _rowindex) {
  // function to get LED index per row
  uint16_t ret = _rowindex%NUM_LEDSPERROW;
  if(_row % 2 == 0) {
    ret += _row*NUM_LEDSPERROW;
  } else {
    ret = (_row+1)*NUM_LEDSPERROW-1-ret;
  }
  return ret;
}

uint16_t getKRLedIndex( uint8_t _row, uint16_t _rowindex, uint8_t _width) {
  // function to get Knight Rider LED index per row
  uint8_t newledsperrow = NUM_LEDSPERROW-_width+1;
  uint16_t ret = _rowindex % (newledsperrow * 2);
  if(ret >= newledsperrow) {
    ret = ret - newledsperrow;
    ret = newledsperrow-1-ret;
  }
  return getLedIndex(_row, ret);
}

void dimLeds(uint8_t _dimspeed, uint8_t _random) {
  // dim contents of all leds by _dimspeed
  if(_random == 0) {
    for(uint16_t i=0; i<NUM_LEDS; i++) {
      leds[i].fadeToBlackBy(_dimspeed);
    }
  } else {
    for(uint16_t i=0; i<NUM_LEDS; i++) {
      leds[i].fadeToBlackBy(random8(_dimspeed,qadd8(_dimspeed,_dimspeed)));
    }
  }
}



// CRGB HeatColor( uint8_t temperature)
// [to be included in the forthcoming FastLED v2.1]
//
// Approximates a 'black body radiation' spectrum for
// a given 'heat' level.  This is useful for animations of 'fire'.
// Heat is specified as an arbitrary scale from 0 (cool) to 255 (hot).
// This is NOT a chromatically correct 'black body radiation'
// spectrum, but it's surprisingly close, and it's extremely fast and small.
//
// On AVR/Arduino, this typically takes around 70 bytes of program memory,
// versus 768 bytes for a full 256-entry RGB lookup table.
 
CRGB HeatColor( uint8_t _temperature)
{
  CRGB heatcolor;
 
  // Scale 'heat' down from 0-255 to 0-191,
  // which can then be easily divided into three
  // equal 'thirds' of 64 units each.
  uint8_t t192 = scale8_video( _temperature, 192);
 
  // calculate a value that ramps up from
  // zero to 255 in each 'third' of the scale.
  uint8_t heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // now figure out which third of the spectrum we're in:
  if( t192 & 0x80) {
    // we're in the hottest third
    heatcolor.r = 255; // full red
    heatcolor.g = 255; // full green
    heatcolor.b = heatramp; // ramp up blue
   
  } else if( t192 & 0x40 ) {
    // we're in the middle third
    heatcolor.r = 255; // full red
    heatcolor.g = heatramp; // ramp up green
    heatcolor.b = 0; // no blue
   
  } else {
    // we're in the coolest third
    heatcolor.r = heatramp; // ramp up red
    heatcolor.g = 0; // no green
    heatcolor.b = 0; // no blue
  }
  return heatcolor;
}


void clearAllLeds() {
  memset(leds, 0, NUM_LEDS * sizeof(CRGB));  // clear all leds
}

void clearRowLeds() {
  memset(ledsrow, 0, NUM_LEDSPERROW * sizeof(CRGB));  // clear work row leds
}
