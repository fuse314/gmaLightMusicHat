#ifndef GMANRFMGT_H
#define GMANRFMGT_H

#include "zGlobals.h"

#include <RF24.h>
#include <gmaRGBLight.h>

struct rf_hat_payload_t {
  uint8_t command;
  uint8_t mode;
  uint8_t vol[7];
};

extern RF24 radio;
extern uint32_t sound_last_request;
#define SOUND_REQUEST_INTERVAL 120000  // 2 minutes

void RF_Init();

void RF_SoundForEveryone(Config_t *_cnf);

void RF_Read();

void RF_RgbLightCommand(rf_hat_payload_t *_command);
#endif
