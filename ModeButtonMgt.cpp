#include "ModeButtonMgt.h"
#include "zGlobals.h"
#include "gmaLightMusicHat.h"
#include "Effect_FindMe.h"
#include "Effect_KR.h"
#include "Effect_Rainbow.h"
#include "Effect_Random.h"
#include "Effect_Sound.h"
#include "Effect_Fire.h"
#include "Effect_Sine.h"

void CheckButton() {
  if(upButtonPressed == 1) {
    #ifndef ALWAYSAUTO
    if(autoModeChange == 1) {  // exit auto mode change on button press
      autoModeChange = 0;
    }
    #endif
    ChangeMode(1);
    upButtonPressed = 0;
  }
  #ifndef NOFINDME
    if(findMeMode == 1 && millis() - lastFindMeButtonPressed >= 2000) { // check every 2 seconds if we missed a interrupt event and have to disable find me mode...
      if(digitalRead(FINDMEBUTTON_PIN) == HIGH) {  // active = low
        InitCurrMode();
        findMeMode = 0;
        findMeButtonPressed = 0;
      }
      lastFindMeButtonPressed = millis();
    } else {
      if(findMeButtonPressed == 1) {
        if(digitalRead(FINDMEBUTTON_PIN) == LOW) {  // active = low
          delete currEffect;
          currEffect = new EffectFindMe(0);
          findMeMode = 1;
        } else {
          InitCurrMode(&cnf);
          findMeMode = 0;
        }
        findMeButtonPressed = 0;
      }
    }
  #endif
}

void UpButtonInterruptHandler() {   // interrupt handler function
  if(millis() - lastUpButtonPressed >= DEBOUNCE_TIME) {
    upButtonPressed = 1;
    lastUpButtonPressed = millis();
  }
}

void FindMeButtonInterruptHandler() {   // interrupt handler function
  #ifndef NOFINDME
    if(millis() - lastFindMeButtonPressed >= DEBOUNCE_TIME) {
      findMeButtonPressed = 1;
      lastFindMeButtonPressed = millis();
    }
  #endif
}

void ChangeMode(uint8_t _modeUp) {
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

void CheckAutoModeChange() {
  // auto mode change every AUTOMODE_CHANGE milliseconds, choose random mode
  if(findMeMode == 0 &&  millis() > AUTOMODE_CHANGE && millis() - lastAutoModeChangeTime > AUTOMODE_CHANGE) {
    lastAutoModeChangeTime = millis();
    cnf.currMode = random8(MAX_MODE) + 1; // random number including 0, excluding MAX_MODE
    InitCurrMode(&cnf);
  }
}

void InitCurrMode(Config_t *_cnf) {
  // initialize current mode (called on mode change)
  switch(_cnf->currMode) {
    case 0: // find me
      delete currEffect;
      currEffect = new EffectFindMe(0, _cnf);
      break;
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
    case 11:
      delete currEffect;
      currEffect = new EffectSound(_cnf->currMode, _cnf);
      break;
    case 12:
    case 13:
    case 14:
      delete currEffect;
      currEffect = new EffectRainbow(_cnf->currMode-12, _cnf);
      break;
    case 15:
    case 16:
    case 17:
      delete currEffect;
      currEffect = new EffectRandom(_cnf->currMode-15, _cnf);
      break;
    case 18:
    case 19:
    case 20:
    case 21:
      delete currEffect;
      currEffect = new EffectKR(_cnf->currMode-18, _cnf);
      break;
    case 22:
    case 23:
    case 24:
      delete currEffect;
      currEffect = new EffectFire(_cnf->currMode-22, _cnf);
      break;
    case 25:
    case 26:
    case 27:
    case 28:
      delete currEffect;
      currEffect = new EffectSine(_cnf->currMode-25, _cnf);
      break;
  }
}
