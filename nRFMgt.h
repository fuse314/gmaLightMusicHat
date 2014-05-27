#ifndef GMANRFMGT_H
#define GMANRFMGT_H

#include "zGlobals.h"

#ifndef NOWIRELESS
#include <RF24.h>

struct rf_hat_payload_t {
  uint8_t command;
  uint8_t mode;
  uint8_t vol[7];
};

extern RF24 radio;

void RF_Init();

void RF_SoundForEveryone(Config_t *_cnf);

void RF_Read();

void RF_RgbLightCommand(rf_hat_payload_t *_command);
#endif
#endif
