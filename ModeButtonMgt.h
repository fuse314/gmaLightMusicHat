#ifndef MODEBUTTONMGT_H
#define MODEBUTTONMGT_H
#include <Arduino.h>
void CheckButton();
void UpButtonInterruptHandler();
void FindMeButtonInterruptHandler();
#define MAX_MODE 23       // maximum number of modes
void ChangeMode(uint8_t _modeUp);
void CheckAutoModeChange();
void InitCurrMode();
#endif
