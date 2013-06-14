
void CheckButton() {
  if(upButtonPressed == 1) {
    ChangeMode(1);
    upButtonPressed = 0;
  }
  if(findMeButtonPressed == 1) {
    if(digitalRead(FINDMEBUTTON_PIN) == HIGH) {
      findMeMode = 1;
    } else {
      findMeMode = 0;
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
  //  lastFindMeButtonPressed = millis();
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
      initSound(currMode);
      break;
    case 3: // rainbow
      initRainbow();
      break;
    case 4: // find me
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
        loopSound();
        break;
      case 3: // rainbow
        loopRainbow();
        break;
      case 4: // find me
        loopFindMe();
        break;
    }
  } else {
    loopFindMe();
  }
}