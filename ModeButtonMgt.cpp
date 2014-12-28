#ifndef MODEBUTTONMGT_H
#define MODEBUTTONMGT_H

#include "zGlobals.h"
#include "gmaLightMusicHat.h"
#include "Effect_KR.cpp"
#include "Effect_Rainbow.cpp"
#include "Effect_Random.cpp"
#include "Effect_Sound.cpp"
#include "Effect_Fire.cpp"
#include "Effect_Sine.cpp"

#define MAX_MODE 28       // maximum number of modes

class ModeButtonMgt {

  public:

static void InitCurrMode(Config_t *_cnf) {
  // initialize current mode (called on mode change)
  switch(_cnf->currMode) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
      delete currEffect;
      currEffect = new EffectSound(_cnf->currMode, _cnf);
      break;
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
      delete currEffect;
      currEffect = new EffectRainbow(_cnf->currMode-11, _cnf);
      break;
    case 16:
    case 17:
    case 18:
    case 19:
      delete currEffect;
      currEffect = new EffectRandom(_cnf->currMode-16, _cnf);
      break;
    case 20:
    case 21:
    case 22:
      delete currEffect;
      currEffect = new EffectKR(_cnf->currMode-20, _cnf);
      break;
    case 23:
    case 24:
    case 25:
      delete currEffect;
      currEffect = new EffectFire(_cnf->currMode-23, _cnf);
      break;
    case 26:
    case 27:
    case 28:
      delete currEffect;
      currEffect = new EffectSine(_cnf->currMode-26, _cnf);
      break;
  }
}

static void ChangeMode(uint8_t _modeUp) {
  // change mode up or down, never go to mode 0 (find me), has its own button
  if(_modeUp == 0) {
    cnf.currMode--;
    if(cnf.currMode == 0) {
      cnf.currMode = MAX_MODE;
    }
  } else {
    cnf.currMode++;
    if(cnf.currMode > MAX_MODE) {
      cnf.currMode = 1;
    }
  }
  //currFrame = 0;
  InitCurrMode(&cnf);
}

static void ModeButton_Click() {
  #ifndef ALWAYSAUTO
  if(autoModeChange == 1) {  // exit auto mode change on button press
    autoModeChange = 0;
  }
  #endif
  ChangeMode(1);
}

static void ModeButton_DoubleClick() {
  #ifndef ALWAYSAUTO
  if(autoModeChange == 1) {  // exit auto mode change on button press
    autoModeChange = 0;
  }
  #endif
  ChangeMode(0);
}

static void ModeButton_Hold() {
  if(autoModeChange) {
    autoModeChange = 0;
    LEDS.showColor(CRGB::Red);
    delay(150);
  } else {
    autoModeChange = 1;
    LEDS.showColor(CRGB::Green);
    delay(150);
  }
}

static void CheckAutoModeChange() {
  // auto mode change every AUTOMODE_CHANGE milliseconds, choose random mode
  if(millis() > AUTOMODE_CHANGE && millis() - lastAutoModeChangeTime > AUTOMODE_CHANGE) {
    lastAutoModeChangeTime = millis();
    cnf.currMode = random8(MAX_MODE) + 1; // random number including 0, excluding MAX_MODE
    InitCurrMode(&cnf);
  }
}

};
#endif

