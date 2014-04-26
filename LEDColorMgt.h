#ifndef LEDCOLORMGT_H
#define LEDCOLORMGT_H

#include <Arduino.h>
#include <FastLED.h>

CRGB Wheel(uint16_t _wheelPos);
void showMirrored( uint8_t _row, CRGB* _halfleds, CRGB* _leds, uint8_t _merge );
void paintAllRows( CRGB* _rowleds, CRGB* _leds );
void solidColor( CRGB _color, CRGB* _leds, uint16_t _num_leds);
void solidColorRow( CRGB _color, uint8_t _row, CRGB* _leds );
void shiftLeds( int8_t _distance, CRGB* _leds );
uint16_t getLedIndex( uint8_t _row, uint16_t _rowindex);
uint16_t getKRLedIndex( uint8_t _row, uint16_t _rowindex, uint8_t _width);
void dimLeds(uint8_t _dimspeed, CRGB* _leds, uint8_t _random = 0);
CRGB HeatColor(uint8_t _temperature, uint8_t _color, uint16_t _var);
void clearLeds(CRGB* _leds, uint16_t _num_leds);

#endif
