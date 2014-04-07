#ifndef GMANRFMGT_H
#define GMANRFMGT_H

#include <SPI.h>
#include <RF24.h>
#include "gmaLightCommon.h"

struct rf_hat_payload_t {
  uint8_t command;
  uint8_t mode;
  uint16_t[3] vol;
};

RF24 radio(9,10);

void RF_Init();

void RF_SoundForEveryone(Config_t *_cnf);

void RF_Read();

void RF_RgbLightCommand(rf_hat_payload_t *_command);
#endif