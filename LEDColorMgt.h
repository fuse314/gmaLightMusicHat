#ifndef LEDCOLORMGT_H
#define LEDCOLORMGT_H

#include <FastLED.h>

CRGB Wheel(uint16_t _wheelPos);
void copyRowToAll( CRGB* _leds );
void setColor( CRGB _color, CRGB* _leds, uint16_t _num_leds);
void shiftLeds( int8_t _distance, CRGB* _leds );
uint16_t getKRLedIndex( uint8_t _row, uint16_t _rowindex, uint8_t _width);
void dimLeds(uint8_t _dimspeed, CRGB* _leds, uint8_t _random = 0);
CRGB ColorMap(uint8_t _value, uint8_t _color, uint16_t _var);
void clearLeds(CRGB* _leds, uint16_t _num_leds);

#endif
