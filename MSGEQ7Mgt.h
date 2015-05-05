#ifndef EQ7_H
#define EQ7_H
#include <FastLED.h>
#include "zGlobals.h"
#include "LEDColorMgt.h"


//MSGEQ7 stuff
#define EQ7STROBE_PIN 7
#define EQ7RESET_PIN 8
#define EQ7IN_PIN A1
#define NOISE_LVL 100     // noise cutoff value
#define MAX_LVL 1024      // maximum volume value

// this value overwrites the bright white color when loud noise is present with a rainbow color, dimmed according to loudness
// as soon as the average loudness level (0-255) of eq7Vol is greater than (EQ7RAINBOW_LVL), the sound color is replaced with the rainbow color.
#define EQ7RAINBOW_LVL 140   // set this to 256 to disable rainbow colors in GetEQColor(...)
class MSGEQ7Mgt {
  //private:
  //static LEDColorMgt cmgt;
  public:
  static void InitEQ7() {
    pinMode(EQ7IN_PIN, INPUT);
    pinMode(EQ7STROBE_PIN, OUTPUT);
    pinMode(EQ7RESET_PIN, OUTPUT);
    analogReference(DEFAULT);
    digitalWrite(EQ7RESET_PIN, LOW);
    digitalWrite(EQ7STROBE_PIN, HIGH);
  }

  static void GetEQ7(Config_t *_cnf) {
    digitalWrite(EQ7RESET_PIN, HIGH);
    digitalWrite(EQ7RESET_PIN, LOW);
    
    for (uint8_t i = 0; i < 7; i++)
    {
      digitalWrite(EQ7STROBE_PIN, LOW);
      delayMicroseconds(30); // to allow analog signal to settle
      _cnf->eq7Band[i] = map(constrain(analogRead(EQ7IN_PIN),NOISE_LVL,MAX_LVL),NOISE_LVL,MAX_LVL,0,255);
      digitalWrite(EQ7STROBE_PIN, HIGH);
    }
    
    digitalWrite(EQ7RESET_PIN, LOW);
    digitalWrite(EQ7STROBE_PIN, HIGH);
    
    _cnf->eq7Vol[0] = (_cnf->eq7Band[0] + _cnf->eq7Band[1] + _cnf->eq7Band[2] + _cnf->eq7Band[2]) / 4;  // low tones
    _cnf->eq7Vol[1] = (_cnf->eq7Band[3] + _cnf->eq7Band[4]) / 2;                                        // mid tones
    _cnf->eq7Vol[2] = (_cnf->eq7Band[5] + _cnf->eq7Band[6] + _cnf->eq7Band[6]) / 3;                     // high tones
  }

  static CRGB GetEQColor(Config_t *_cnf) {
    CRGB ret;
    uint16_t avgVol = _cnf->eq7Vol[0] + _cnf->eq7Vol[1] + _cnf->eq7Vol[2];  // calculate average "loudness"
    avgVol = avgVol / 3;
    if(avgVol > EQ7RAINBOW_LVL) {  // overwrite loud noises (usually bright white) with rainbow color
      ret = Wheel(_cnf->currFrame);
      ret.fadeToBlackBy(280-avgVol);
    } else {
      ret.g = _cnf->eq7Vol[2];  // high tones are green
      ret.r = _cnf->eq7Vol[1];  // mid  tones are red
      ret.b = _cnf->eq7Vol[0];  // low  tones are blue
    }
    return ret;
  }
};
#endif

