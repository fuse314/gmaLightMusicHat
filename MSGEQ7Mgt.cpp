#include "MSGEQ7Mgt.h"
#include "gmaLightCommon.h"


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
    _cnf->eq7Values[i] = analogRead(EQ7IN_PIN); 
    digitalWrite(EQ7STROBE_PIN, HIGH);
  }
  
  digitalWrite(EQ7RESET_PIN, LOW);
  digitalWrite(EQ7STROBE_PIN, HIGH);
  
  _cnf->eq7Volumes[0] = max(_cnf->eq7Values[0], max(_cnf->eq7Values[1], _cnf->eq7Values[2]));
  _cnf->eq7Volumes[1] = max(_cnf->eq7Values[3], _cnf->eq7Values[4]);
  _cnf->eq7Volumes[2] = max(_cnf->eq7Values[5], max(_cnf->eq7Values[6], _cnf->eq7Values[7]));
}

CRGB GetEQColor(Config_t *_cnf) {
  CRGB ret;
  if(_cnf->eq7Volumes[2] <= NOISE_LVL) {   // low tones are green
    ret.g = 0;
  } else {
    ret.g = map(_cnf->eq7Volumes[2], NOISE_LVL, MAX_LVL, 1, 255);
  }
  if(_cnf->eq7Volumes[1] <= NOISE_LVL) {   // mid tones are red
    ret.r = 0;
  } else {
    ret.r = map(_cnf->eq7Volumes[1], NOISE_LVL, MAX_LVL, 1, 255);
  }
  if(_cnf->eq7Volumes[0] <= NOISE_LVL) {   // high tones are blue
    ret.b = 0;
  } else {
    ret.b = map(_cnf->eq7Volumes[0], NOISE_LVL, MAX_LVL, 1, 255);
  }
  return ret;
}
