#ifndef GMANRFMGT_H
#define GMANRFMGT_H

#include "gmaLightCommon.h"

struct rf_hat_payload_t {
  uint8_t command;
  uint8_t mode;
  uint16_t volLow;
  uint16_t volMid;
  uint16_t volHigh;
};

//extern RF24 radio;

void RF_Init();

void RF_SoundForEveryone(Config_t *_cnf);

void RF_Read();

void RF_RgbLightCommand(rf_hat_payload_t *_command);
#endif
