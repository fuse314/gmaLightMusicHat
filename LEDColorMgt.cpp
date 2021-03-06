#include "zGlobals.h"
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

void copyRowToAll( CRGB* _leds ) {
  for(uint8_t y=1; y<M_HEIGHT; y++) {
    for(uint8_t x=0; x<M_WIDTH; x++) {
      _leds[XY(x,y)] = _leds[XY(x,0)];
    }
  }
}

void setColor( CRGB _color, CRGB* _leds, uint16_t _num_leds) {
  // set all leds to _color
  for(uint16_t i=0; i<_num_leds; i++) {
    _leds[i] = _color;
  }
}

void shiftLeds( int8_t _distance, CRGB* _leds ) {
  // shift content of leds per row in one direction or other (positive / negative number), clear leftover leds
  if(_distance == 0) { return; }  // shift by zero: do nothing.
  for(uint8_t i=0; i<M_HEIGHT; i++) {
    if(_distance > 0) {
      for(uint16_t j=0; j<M_WIDTH-_distance; j++) {
        _leds[XY(j,i)] = _leds[XY(j+_distance,i)];  // higher index to lower index, iterate upwards
      }
      for(uint16_t j=M_WIDTH-_distance; j<M_WIDTH; j++) {
        _leds[XY(j,i)] = CRGB(0,0,0);  // clear leftover leds
      }
    } else {
      for(uint16_t j=M_WIDTH+M_WIDTH+_distance-1; j>=M_WIDTH; j--) { // make sure j never goes below 0
        _leds[XY(j,i)] = _leds[XY(j+_distance,i)];  // lower index to higher index, iterate downwards
      }
      for(uint16_t j=0; j<_distance; j++) {
        _leds[XY(j,i)] = CRGB(0,0,0);  // clear leftover leds
      }
    }
  }
}

uint16_t getKRLedIndex( uint8_t _row, uint16_t _rowindex, uint8_t _width) {
  // function to get Knight Rider LED index per row
  uint8_t newledsperrow = M_WIDTH-_width+1;
  uint16_t ret = _rowindex % (newledsperrow * 2);
  if(ret >= newledsperrow) {
    ret = ret - newledsperrow;
    ret = newledsperrow-1-ret;
  }
  return XY(ret,_row);
}

void dimLeds(uint8_t _dimspeed, CRGB* _leds, uint8_t _random) {
  // dim contents of all leds by _dimspeed
  if(_random == 0) {
    for(uint16_t i=0; i<NUM_LEDS; i++) {
      _leds[i].fadeToBlackBy(_dimspeed);
    }
  } else {
    for(uint16_t i=0; i<NUM_LEDS; i++) {
      _leds[i].fadeToBlackBy(random8(_dimspeed,qadd8(_dimspeed,_dimspeed)));
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
 
CRGB ColorMap( uint8_t _value, uint8_t _color, uint16_t _var)
{
  CRGB ret;
  if(_color == 0) {
    // Scale 'heat' down from 0-255 to 0-191,
    // which can then be easily divided into three
    // equal 'thirds' of 64 units each.
    uint8_t t192 = scale8_video( _value, 192);
   
    // calculate a value that ramps up from
    // zero to 255 in each 'third' of the scale.
    uint8_t ramp = t192 & 0x3F; // 0..63
    ramp <<= 2; // scale up to 0..252
   
    // now figure out which third of the spectrum we're in:
    if( t192 & 0x80) {
      // we're in the hottest third
      ret.r = 255; // full red
      ret.g = 255; // full green
      ret.b = ramp; // ramp up blue
     
    } else if( t192 & 0x40 ) {
      // we're in the middle third
      ret.r = 255; // full red
      ret.g = ramp; // ramp up green
      ret.b = 0; // no blue
     
    } else {
      // we're in the coolest third
      ret.r = ramp; // ramp up red
      ret.g = 0; // no green
      ret.b = 0; // no blue
    }
  } else {
    ret.r = 0;
    ret.g = 0;
    ret.b = 0;
    if(_color == 1) { ret.r = _value; }
    if(_color == 2) { ret.g = _value; }
    if(_color == 3) { ret.b = _value; }
    if(_color == 4) { ret = Wheel(_var+_value); ret.fadeToBlackBy(_value); }
  }
  return ret;
}


void clearLeds(CRGB* _leds, uint16_t _num_leds) {
  memset8(_leds, 0, _num_leds * sizeof(CRGB));  // clear all leds
}

