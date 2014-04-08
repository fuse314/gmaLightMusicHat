#ifndef MYCONFIG_H
#define MYCONFIG_H

#include <Arduino.h>
#include <FastLED.h>
#include "zGlobals.h"
#include "zEffectClass.h"

//uncomment this for debug over serial port
//#define SerialDebug

#ifdef SerialDebug
#include <Streaming.h>
#endif


//struct CRGB { unsigned char g; unsigned char r; unsigned char b; };
extern CRGB leds[NUM_LEDS];
extern CRGB ledsrow[NUM_LEDSPERROW];  // used for mirrored effects and one-row-for-all effects
//CRGB currColor;
#define LED_PIN 11

//button stuff
#define DEBOUNCE_TIME 150
#define UPBUTTON_PIN 2  //interrupt 0
extern volatile uint8_t upButtonPressed;
extern volatile uint32_t lastUpButtonPressed;

// FINDME or not FINDME
#define NOFINDME

#ifndef NOFINDME
  #define FINDMEBUTTON_PIN 3  //interrupt 1
  extern volatile uint8_t findMeButtonPressed;
  extern volatile uint32_t lastFindMeButtonPressed;
#endif

//effect stuff
#include "zEffectClass.h"
#include "Effect_Random.h"  // only include first effect for setup()
extern EffectClass *currEffect;

extern Config_t cnf;

//loop stuff
extern uint8_t findMeMode;

//auto mode change stuff
extern uint8_t autoModeChange;  // start in auto mode change mode
#define AUTOMODE_CHANGE 60000  // change every 60 seconds
extern uint32_t lastAutoModeChangeTime;
// next line controls if auto mode change stays always on
#define ALWAYSAUTO

#ifdef SerialDebug
int freeRam ();  // function returns distance between stack and heap (available ram)
#endif
#endif
