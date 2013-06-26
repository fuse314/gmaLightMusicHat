
void CheckButton() {
  if(upButtonPressed == 1) {
    if(autoModeChange == 1) {  // exit auto mode change on button press
      autoModeChange == 0;
    }
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

#define MAX_MODE 20       // maximum number of modes

void ChangeMode(uint8_t _modeUp) {
  // change mode up or down, never go to mode 0 (find me), has its own button
  if(_modeUp == 0) {
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
  //currFrame = 0;
  InitCurrMode();
}

void CheckAutoModeChange() {
  // auto mode change every AUTOMODE_CHANGE milliseconds, choose random mode
  if(findMeMode == 0 &&  millis() > AUTOMODE_CHANGE && millis() - lastAutoModeChange > AUTOMODE_CHANGE) {
    currMode = random(0, MAX_MODE) + 1; // random number including 0, excluding MAX_MODE
    InitCurrMode();
  }
}

void InitCurrMode() {
  // initialize current mode (called on mode change)
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
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
      initSound(currMode);
      break;
    case 12:
    case 13:
    case 14:
      initRainbow(currMode-12);
      break;
    case 15:
    case 16:
    case 17:
      initRandom(currMode-15);
      break;
    case 18:
    case 19:
    case 20:
      initKR(currMode-18);
      break;
  }
}

void LoopCurrMode() {
  // loop current mode (called every frame)
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
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
        loopSound();
        break;
      case 12:
      case 13:
      case 14:
        loopRainbow();
        break;
      case 15:
      case 16:
      case 17:
        loopRandom();
        break;
      case 18:
      case 19:
      case 20:
        loopKR();
        break;
    }
  } else {
    loopFindMe();
  }
}
