
void CheckButton(int debounceTime) {
  uint8_t buttonState = digitalRead(BUTTON_PIN);
  if(buttonState == HIGH) {  // wait debounceTime milliseconds and check again
    delay(debounceTime);
    buttonState = digitalRead(BUTTON_PIN);
    if(buttonState == HIGH) {
      ChangeMode(1);  // button is still pressed, execute.
    }
  }
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
}