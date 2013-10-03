//mode 0: rainbow all three rows the same
//mode 1: solid color rainbow all leds the same
//mode 2: rainbow through all leds, results in right-left-right run due to led configuration

#include "Effect_Rainbow.h"
#include "LEDColorMgt.h"
#include "gmaLightMusicHat.h"

EffectRainbow::EffectRainbow(uint8_t _mode) : EffectClass(_mode) {
  currDelay = DELAY_FAST;
  LEDS.setBrightness(NORMBRIGHT);
  clearAllLeds();
}

void EffectRainbow::step(uint16_t *_currFrame) {
  switch(_effectMode) {
    case 0:
      fill_rainbow( &(ledsrow[0]), NUM_LEDSPERROW, *_currFrame % 256);
      paintAllRows(ledsrow);
      break;
    case 1:
      solidColor(Wheel(*_currFrame));
      break;
    case 2:
      fill_rainbow( &(leds[0]), NUM_LEDS, *_currFrame % 256);
      break;
  }
}
