#ifndef MODEBUTTONMGT_H
#define MODEBUTTONMGT_H
#include <Arduino.h>
#include "zGlobals.h"

void CheckButton();
void UpButtonInterruptHandler();
void FindMeButtonInterruptHandler();
#define MAX_MODE 30       // maximum number of modes
void ChangeMode(uint8_t _modeUp);
void CheckAutoModeChange();
void InitCurrMode(Config_t *_cnf);
#endif
