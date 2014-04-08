#include "MSGEQ7Mgt.h"
#include "zGlobals.h"


void InitEQ7() {
  pinMode(EQ7IN_PIN, INPUT);
  pinMode(EQ7STROBE_PIN, OUTPUT);
  pinMode(EQ7RESET_PIN, OUTPUT);
  analogReference(DEFAULT);
  digitalWrite(EQ7RESET_PIN, LOW);
  digitalWrite(EQ7STROBE_PIN, HIGH);
}

void GetEQ7(Config_t *_cnf) {
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
  _cnf->eq7Vol[2] = (_cnf->eq7Band[5] + _cnf->eq7Band[6] + _cnf->eq7Band[7]) / 3;                     // high tones
}

CRGB GetEQColor(Config_t *_cnf) {
  CRGB ret;
  ret.g = _cnf->eq7Vol[2];  // high tones are green
  ret.r = _cnf->eq7Vol[1];  // mid  tones are red
  ret.b = _cnf->eq7Vol[0];  // low  tones are blue
  return ret;
}
