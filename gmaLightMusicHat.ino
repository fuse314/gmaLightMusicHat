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
#include "zGlobals.h"
#include "LEDColorMgt.h"
#include "MSGEQ7Mgt.h"
#include "ModeButtonMgt.h"
#include "zEffectClass.h"
#ifndef NOWIRELESS
#include <SPI.h>
#include <RF24.h>
#include <gmaRGBLight.h>
#include "nRFMgt.h"
#endif


// LED stuff
#include <FastLED.h>

#ifdef SerialDebug
#include <Streaming.h>
#endif

// button stuff
#include <OneButton.h>

CRGB leds[NUM_LEDS];

EffectClass *currEffect;

uint8_t autoModeChange;
uint32_t lastAutoModeChangeTime;
uint8_t soundForEveryone;

Config_t cnf;

MSGEQ7Mgt eq;
ModeButtonMgt modeMgt;

// setup button
OneButton modeButton(MODEBUTTON_PIN,true);

void setup()
{
  //FastLED library
  LEDS.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  clearLeds(&leds[0], NUM_LEDS);
  //clearLeds(&ledsrow[0], M_WIDTH);
  LEDS.show();  // push black
  
  //initialize MSGEQ7 chip
  eq.InitEQ7();
  
  soundForEveryone = 0;
  #ifndef NOWIRELESS
  //RF24 stuff
  RF_Init();
  #endif
  
  //button stuff
  modeButton.setClickTicks(300);
  modeButton.attachClick(modeMgt.ModeButton_Click);
  modeButton.attachDoubleClick(modeMgt.ModeButton_DoubleClick);
  modeButton.attachLongPressStart(modeMgt.ModeButton_Hold);

  //mode stuff
  cnf.currFrame = 0;
  cnf.currHue = 0;
  autoModeChange = 1;
  lastAutoModeChangeTime = 0;
  cnf.currMode = 18;  // first mode to run
  modeMgt.InitCurrMode(&cnf);
  
  #ifdef SerialDebug
  Serial.begin(9600);
  Serial << "Setup done" << endl;
  Serial << "ram " << freeRam() << endl;
  //cnf.debug = 1;
  #endif
}

void loop() {
  
  // call effect loop
  currEffect->step(&cnf, leds);
  if(LEDS.getBrightness() != cnf.currBright) {  // update global brightness
    LEDS.setBrightness(cnf.currBright);
  }
  // push pixels to led strip
  LEDS.show();
  // increment currFrame after effect loop - these variables will roll over
  cnf.currFrame++;
  cnf.currHue++;
  
  // random modes every 100 frames, fire mode every 20 frames
  if(((cnf.currMode > 14) && (cnf.currFrame % 100 == 0)) || ((cnf.currMode >= 22) && (cnf.currFrame % 13 == 0))) {
    random16_add_entropy(analogRead(0));   // re-initialize random numbers
  }
  
  if((soundForEveryone == 1) || (cnf.currMode <= 11/* sound */) || 
     (cnf.currMode == 21 /* kr */) || (cnf.currMode == 24/* fire */)) {
    eq.GetEQ7(&cnf);
  }
  
  // check if any buttons have been pressed
  modeButton.tick();
  
  #ifdef SerialDebug
    if(cnf.currFrame % 200 == 0) {
      Serial << "m=" << cnf.currMode << " d=" << cnf.currDelay << " r=" << freeRam() << endl;
    }
  #endif
  
  #ifndef NOWIRELESS
  //RF24 stuff
  RF_Read();
  
  if(soundForEveryone == 1) {
    RF_SoundForEveryone(&cnf);
  }
  
  #endif
  
  // only check random mode change every currDelay*150 milliseconds, default 1050 ms (one second)
  if(autoModeChange == 1 && cnf.currFrame % 150 == 0) {
    modeMgt.CheckAutoModeChange();
  }
  FastLED.delay(cnf.currDelay);
}


uint16_t XY( uint8_t x, uint8_t y)
{
  // wrap around variables
  if(x >= M_WIDTH) { x = x % M_WIDTH; }
  if(y >= M_HEIGHT) { y = y % M_HEIGHT; }
  
  uint16_t i;

  if( y & 0x01) {
    // Odd rows run backwards
    uint8_t reverseX = (M_WIDTH - 1) - x;
    i = (y * M_WIDTH) + reverseX;
  } else {
    // Even rows run forwards
    i = (y * M_WIDTH) + x;
  }
  
  return i;
}


#ifdef SerialDebug
int freeRam ()  // function returns distance between stack and heap (available ram)
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

#endif
