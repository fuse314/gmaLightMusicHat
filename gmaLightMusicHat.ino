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

//uncomment this for debug over serial port
//#define SerialDebug

#ifdef SerialDebug
#include <Streaming.h>
#endif

// LED stuff
#include <FastSPI_LED2.h>

// 38 LEDs * 3
// configuration:
//   ==> 76 77 78 79 .. 112 113
//   <== 75 74 73 72 ..  39  38
//   ==>  0  1  2  3 ..  36  37
// this is due to cabling (shorter wires) and removability (LEDs are mounted with velcro strip)
#define NUM_LEDS 114
#define NUM_ROWS 3
#define NUM_LEDSPERROW 38
uint8_t NUM_LEDSPERHALFROW = NUM_LEDSPERROW / 2;

//struct CRGB { unsigned char g; unsigned char r; unsigned char b; };
CRGB leds[NUM_LEDS];
CRGB ledsrow[NUM_LEDSPERROW];  // used for mirrored effects and one-row-for-all effects
CRGB currColor;
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

uint16_t eq7Values[7];
// [0], [1], [2],  [3],  [4],  [5],   [6]
//  63, 160, 400, 1000, 2500, 6250, 16000 Hz
uint16_t eq7Volumes[3];
// 0 = low tones, 1 = mid tones, 3 = high tones

//button stuff

#define DEBOUNCE_TIME 150
#define UPBUTTON_PIN 2  //interrupt 0
volatile uint8_t upButtonPressed = 0;
volatile uint32_t lastUpButtonPressed = 0;

#define FINDMEBUTTON_PIN 3  //interrupt 1
volatile uint8_t findMeButtonPressed = 0;
volatile uint32_t lastFindMeButtonPressed = 0;

//effect stuff
#include "zEffectClass.h"
#include "Effect_Random.h"  // only include first effect for setup()
EffectClass *currEffect;
uint8_t currMode;
uint16_t currFrame = 0;
uint8_t effectMode; // used in effects


#define DELAY_NORMAL 7
#define DELAY_FAST 4
#define DELAY_SLOW 18
#define DELAY_KR 25
uint8_t currDelay;
uint8_t todoDelay = 0;
uint8_t findMeMode = 0;

//auto mode change stuff
uint8_t autoModeChange = 1;  // start in auto mode change mode
#define AUTOMODE_CHANGE 60000  // change every 60 seconds
uint32_t lastAutoModeChangeTime = 0;


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
  pinMode(UPBUTTON_PIN, INPUT);
  digitalWrite(UPBUTTON_PIN, HIGH);  // pullup resistor
  attachInterrupt(0, UpButtonInterruptHandler, FALLING);
  pinMode(FINDMEBUTTON_PIN, INPUT);
  digitalWrite(FINDMEBUTTON_PIN, HIGH);  // pullup resistor
  attachInterrupt(1, FindMeButtonInterruptHandler, FALLING);
  
  //mode stuff
  currMode = 15 // start with random effect 0
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
    currEffect->step();
    //LoopCurrMode();
    // push pixels to led strip
    LEDS.show();
    // increment currFrame after effect loop - this variable may roll over
    currFrame++;
    
    // check if any buttons have been pressed
    CheckButton();
    
    #ifdef SerialDebug
      if(currFrame % 200 == 0) {
        Serial << "m=" << currMode << " r=" << freeRam << endl;
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