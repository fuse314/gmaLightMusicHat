
void CheckButton() {
  if(upButtonPressed == 1) {
    ChangeMode(1);
    upButtonPressed = 0;
  }
  if(findMeMode == 1 && millis() - lastFindMeButtonPressed >= 2000) { // check every 2 seconds if we missed a interrupt event and have to disable find me mode...
    if(digitalRead(FINDMEBUTTON_PIN) == LOW) {
      InitCurrMode();
      findMeMode = 0;
      findMeButtonPressed = 0;
    }
    lastFindMeButtonPressed = millis();
  } else {
    if(findMeButtonPressed == 1) {
      if(digitalRead(FINDMEBUTTON_PIN) == HIGH) {
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

void UpButtonInterruptHandler() {
  if(millis() - lastUpButtonPressed >= DEBOUNCE_TIME) {
    upButtonPressed = 1;
    lastUpButtonPressed = millis();
  }
}

void FindMeButtonInterruptHandler() {
  //if(millis() - lastFindMeButtonPressed >= DEBOUNCE_TIME) {   //no debounce for CHANGE interrupt
    findMeButtonPressed = 1;
    lastFindMeButtonPressed = millis();
  //}
}

void ChangeMode(uint8_t modeUp) {
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


void InitCurrMode() {
  switch(currMode) {
    case 0: // simple sound
    case 1: // rainbow sound
    case 2: // solid color sound
    case 3: // simple sound with rainbow underlaid
    case 4: // rotating sound graph
      initSound(currMode);
      break;
    case 5: // rainbow
      initRainbow();
      break;
    case 6: // find me
      initFindMe();
      break;
  }
}

void LoopCurrMode() {
  if ( findMeMode == 0 ) {
    switch(currMode) {
      case 0: // simple sound
      case 1: // rainbow sound
      case 2: // solid color sound
      case 3: // simple sound with rainbow underlaid
      case 4: // rotaing sound graph
        loopSound();
        break;
      case 5: // rainbow
        loopRainbow();
        break;
      case 6: // find me
        loopFindMe();
        break;
    }
  } else {
    loopFindMe();
  }
}
