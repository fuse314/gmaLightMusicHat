
void CheckButton() {
  if(upButtonPressed == 1) {
    ChangeMode(1);
    upButtonPressed = 0;
  }
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
        initFindMe();
        findMeMode = 1;
      } else {
        InitCurrMode();
        findMeMode = 0;
      }
      findMeButtonPressed = 0;
    }
  }
}

void UpButtonInterruptHandler() {   // interrupt handler function
  if(millis() - lastUpButtonPressed >= DEBOUNCE_TIME) {
    upButtonPressed = 1;
    lastUpButtonPressed = millis();
  }
}

void FindMeButtonInterruptHandler() {   // interrupt handler function
  if(millis() - lastFindMeButtonPressed >= DEBOUNCE_TIME) {
    findMeButtonPressed = 1;
    lastFindMeButtonPressed = millis();
  }
}

void ChangeMode(uint8_t modeUp) {  // change mode up or down, never go to mode 0 (find me), has its own button
  if(modeUp == 0) {
    currMode--;
    if(currMode == 0) {
      currMode = MAX_MODE;
    }
  } else {
    currMode++;
    if(currMode > MAX_MODE) {
      currMode = 1;
    }
  }
  currFrame = 0;
  InitCurrMode();
}


#define MAX_MODE 8       // maximum number of modes

void InitCurrMode() {
  switch(currMode) {
    case 0: // find me
      initFindMe();
      break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      initSound(currMode);
      break;
    case 7:
    case 8:
      initRainbow();
      break;
  }
}

void LoopCurrMode() {
  if ( findMeMode == 0 ) {
    switch(currMode) {
      case 0: // find me
        loopFindMe();
        break;
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
        loopSound();
        break;
      case 7:
        loopRainbow(0);
        break;
      case 8:
        loopRainbow(1);
        break;
    }
  } else {
    loopFindMe();
  }
}
