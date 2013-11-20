#ifndef MYCONFIG_H
#define MYCONFIG_H

#include <Arduino.h>
#include <FastSPI_LED2.h>

//uncomment this for debug over serial port
#define SerialDebug

#ifdef SerialDebug
#include <Streaming.h>
#endif


#define NUM_LEDS 114
#define NUM_ROWS 3
#define NUM_LEDSPERROW 38
#define NUM_LEDSPERHALFROW 19 //NUM_LEDSPERROW / 2

//struct CRGB { unsigned char g; unsigned char r; unsigned char b; };
extern CRGB leds[NUM_LEDS];
extern CRGB ledsrow[NUM_LEDSPERROW];  // used for mirrored effects and one-row-for-all effects
//CRGB currColor;
#define LED_PIN 11

#define NORMBRIGHT 40  // maximum brightness of leds (0-255)
#define MAXBRIGHT 120  // used for "find me" mode

#define DIMSPEED 15    // the higher the slower...

//MSGEQ7 stuff
#define EQ7STROBE_PIN 7
#define EQ7RESET_PIN 8
#define EQ7IN_PIN A1
#define NOISE_LVL 100     // noise cutoff value
#define MAX_LVL 1023      // maximum volume value

extern uint16_t eq7Values[7];
// [0], [1], [2],  [3],  [4],  [5],   [6]
//  63, 160, 400, 1000, 2500, 6250, 16000 Hz
extern uint16_t eq7Volumes[3];
// 0 = low tones, 1 = mid tones, 3 = high tones


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
extern uint8_t currMode;
extern uint16_t currFrame;
//uint8_t effectMode; // used in effects


//loop stuff
#define DELAY_NORMAL 7
#define DELAY_FAST 4
#define DELAY_SLOW 18
#define DELAY_KR 25
extern uint8_t currDelay;
extern uint8_t todoDelay;
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
