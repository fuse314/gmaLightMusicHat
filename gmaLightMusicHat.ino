/*
  Three LED Strips mounted on hat for music festivals
  using MSGEQ7 chip and microphone to react to music
  (c) 2013 by Gottfried Mayer www.gma.name
  
  Uses FastSPI_LED2 (rc3) to control WS2811 controller chips
  
  Inspiration from here:
  http://www.macetech.com/blog/node/118
  
  Code partially copied and modified from here:
  http://hackaday.com/2012/09/11/disco-planet-a-massive-rgbw-led-array-in-a-6-globe/
  
*/


#include "gmaLightMusicHat.h"
#include "LEDColorMgt.h"
#include "MSGEQ7Mgt.h"
#include "ModeButtonMgt.h"

// LED stuff
#include <FastSPI_LED2.h>

#ifdef SerialDebug
#include <Streaming.h>
#endif

//struct CRGB { unsigned char g; unsigned char r; unsigned char b; };
CRGB leds[NUM_LEDS];
CRGB ledsrow[NUM_LEDSPERROW];  // used for mirrored effects and one-row-for-all effects
//CRGB currColor;

uint16_t eq7Values[7];
// [0], [1], [2],  [3],  [4],  [5],   [6]
//  63, 160, 400, 1000, 2500, 6250, 16000 Hz
uint16_t eq7Volumes[3];
// 0 = low tones, 1 = mid tones, 3 = high tones

volatile uint8_t upButtonPressed;
volatile uint32_t lastUpButtonPressed;
volatile uint8_t findMeButtonPressed;
volatile uint32_t lastFindMeButtonPressed;
EffectClass *currEffect;
uint8_t currMode;
uint16_t currFrame;
uint8_t currDelay;
uint8_t todoDelay;
uint8_t findMeMode;
uint8_t autoModeChange;
uint32_t lastAutoModeChangeTime;


void setup()
{
  //FastSPI_LED2 rc1 library
  LEDS.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  clearAllLeds();
  clearRowLeds();
  LEDS.show();  // push black
  
  //initialize MSGEQ7 chip
  InitEQ7();
  
  //button stuff
  upButtonPressed = 0;
  lastUpButtonPressed = 0;
  findMeButtonPressed = 0;
  lastFindMeButtonPressed = 0;
  
  pinMode(UPBUTTON_PIN, INPUT);
  digitalWrite(UPBUTTON_PIN, HIGH);  // pullup resistor
  attachInterrupt(0, UpButtonInterruptHandler, FALLING);
  pinMode(FINDMEBUTTON_PIN, INPUT);
  digitalWrite(FINDMEBUTTON_PIN, HIGH);  // pullup resistor
  attachInterrupt(1, FindMeButtonInterruptHandler, FALLING);
  
  //mode stuff
  currFrame = 0;
  todoDelay = 0;
  findMeMode = 0;
  autoModeChange = 1;
  lastAutoModeChangeTime = 0;
  currMode = 15; // start with random effect 0
  InitCurrMode();
  
  #ifdef SerialDebug
  Serial.begin(9600);
  Serial << "Setup done" << endl;
  Serial << "ram " << freeRam() << endl;
  #endif
}

void loop() {
  if(todoDelay > 0) {
    // count down todoDelay until 0
    todoDelay--;
    delay(1);
  } else {
    // time for the next frame
    todoDelay = currDelay;
    
    // call effect loop
    currEffect->step(&currFrame);
    //LoopCurrMode();
    // push pixels to led strip
    LEDS.show();
    // increment currFrame after effect loop - this variable may roll over
    currFrame++;
    
    // check if any buttons have been pressed
    CheckButton();
    
    #ifdef SerialDebug
      if(currFrame % 200 == 0) {
        Serial << "m=" << currMode << " r=" << freeRam() << endl;
      }
    #endif
    
    // only check random mode change every currDelay*150 milliseconds, default 1050 ms (one second)
    if(autoModeChange == 1 && currFrame % 150 == 0) {
      CheckAutoModeChange();
    }
  }
}


#ifdef SerialDebug
int freeRam ()  // function returns distance between stack and heap (available ram)
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

#endif
