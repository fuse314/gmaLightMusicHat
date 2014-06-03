/*
  Three LED Strips mounted on hat for music festivals
  using MSGEQ7 chip and microphone to react to music
  (c) 2012-2014 by Gottfried Mayer www.gma.name
  
  Uses FastLED to control WS2811 controller chips
  
  Inspiration from here:
  http://www.macetech.com/blog/node/118
  
  Code partially copied and modified from here:
  http://hackaday.com/2012/09/11/disco-planet-a-massive-rgbw-led-array-in-a-6-globe/
  
*/

#include "gmaLightMusicHat.h"
#include "LEDColorMgt.h"
#include "MSGEQ7Mgt.h"
#include "ModeButtonMgt.h"
#include "zEffectClass.h"
#include "nRFMgt.h"

// LED stuff
#include <FastLED.h>

#ifdef SerialDebug
#include <Streaming.h>
#endif

CRGB leds[NUM_LEDS];
CRGB ledsrow[NUM_LEDSPERROW];  // used for mirrored effects and one-row-for-all effects

volatile uint8_t upButtonPressed;
volatile uint32_t lastUpButtonPressed;
#ifndef NOFINDME
  volatile uint8_t findMeButtonPressed;
  volatile uint32_t lastFindMeButtonPressed;
#endif
EffectClass *currEffect;

uint8_t findMeMode;
uint8_t autoModeChange;
uint32_t lastAutoModeChangeTime;
uint8_t soundForEveryone;

Config_t cnf;

void setup()
{
  //FastLED library
  LEDS.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  clearLeds(&leds[0], NUM_LEDS);
  clearLeds(&ledsrow[0], NUM_LEDSPERROW);
  LEDS.show();  // push black
  
  //initialize MSGEQ7 chip
  InitEQ7();
  
  soundForEveryone = 0;
  #ifndef NOWIRELESS
  //RF24 stuff
  RF_Init();
  #endif
  
  //button stuff
  upButtonPressed = 0;
  lastUpButtonPressed = 0;
  #ifndef NOFINDME
    findMeButtonPressed = 0;
    lastFindMeButtonPressed = 0;
  #endif
  
  pinMode(UPBUTTON_PIN, INPUT);
  digitalWrite(UPBUTTON_PIN, HIGH);  // pullup resistor
  attachInterrupt(0, UpButtonInterruptHandler, FALLING);
  #ifndef NOFINDME
    pinMode(FINDMEBUTTON_PIN, INPUT);
    digitalWrite(FINDMEBUTTON_PIN, HIGH);  // pullup resistor
    attachInterrupt(1, FindMeButtonInterruptHandler, FALLING);
  #endif  

  //mode stuff
  cnf.currFrame = 0;
  findMeMode = 0;
  autoModeChange = 1;
  lastAutoModeChangeTime = 0;
  cnf.currMode = 25;  // first mode to run
  InitCurrMode(&cnf);
  
  #ifdef SerialDebug
  Serial.begin(9600);
  Serial << "Setup done" << endl;
  Serial << "ram " << freeRam() << endl;
  cnf.debug = 1;
  #endif
}

void loop() {
  
  // call effect loop
  currEffect->step(&cnf, leds, ledsrow);
  //LoopCurrMode();
  // push pixels to led strip
  LEDS.show();
  // increment currFrame after effect loop - this variable may roll over
  cnf.currFrame++;
  
  // random modes every 100 frames, fire mode every 20 frames
  if(((cnf.currMode > 14) && (cnf.currFrame % 100 == 0)) || ((cnf.currMode >= 22) && (cnf.currFrame % 20 == 0))) {
    random16_add_entropy(analogRead(0));   // re-initialize random numbers
  }
  
  if((soundForEveryone == 1) || (cnf.currMode <= 11/* sound */) || 
     (cnf.currMode == 21 /* kr */) || (cnf.currMode == 24/* fire */)) {
    GetEQ7(&cnf);
  }
  
  // check if any buttons have been pressed
  CheckButton();
  
  #ifdef SerialDebug
    if(cnf.currFrame % 200 == 0) {
      Serial << "m=" << cnf.currMode << " d=" << cnf.currDelay << " r=" << freeRam() << " t=" << cnf.debug << endl;
    }
  #endif
  
  #ifndef NOWIRELESS
  //RF24 stuff
  RF_Read();
  #endif
  
  // only check random mode change every currDelay*150 milliseconds, default 1050 ms (one second)
  if(autoModeChange == 1 && cnf.currFrame % 150 == 0) {
    CheckAutoModeChange();
  }
  FastLED.delay(cnf.currDelay);
}


#ifdef SerialDebug
int freeRam ()  // function returns distance between stack and heap (available ram)
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

#endif
