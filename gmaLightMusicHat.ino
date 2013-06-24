/*
  Three LED Strips mounted on hat for music festivals
  using MSGEQ7 chip and microphone to react to music
  (c) 2013 by Gottfried Mayer www.gma.name
  
  Uses FastSPI_LED2 (rc1) to control WS2811 controller chips
  
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
struct CRGB leds[NUM_LEDS];
struct CRGB ledsrow[NUM_LEDSPERROW];  // used for mirrored effects and one-row-for-all effects
#define LED_PIN 11

#define NORMBRIGHT 45  // maximum brightness of leds (0-255)
#define MAXBRIGHT 120  // used for "find me" mode

#define DIMSPEED 15    // the higher the slower...

//MSGEQ7 stuff
#define EQ7STROBE_PIN 7
#define EQ7RESET_PIN 8
#define EQ7IN_PIN A1
#define NOISE_LVL 100     // noise cutoff value

uint16_t eq7Values[7];
// [0], [1], [2],  [3],  [4],  [5],   [6]
//  63, 160, 400, 1000, 2500, 6250, 16000 Hz
uint16_t eq7Volumes[3];
// 0 = low tones, 1 = mid tones, 3 = high tones

//button stuff

#define DEBOUNCE_TIME 120
#define UPBUTTON_PIN 2  //interrupt 0
volatile uint8_t upButtonPressed = 0;
volatile uint32_t lastUpButtonPressed = 0;

#define FINDMEBUTTON_PIN 3  //interrupt 1
volatile uint8_t findMeButtonPressed = 0;
volatile uint32_t lastFindMeButtonPressed = 0;

//loop stuff
uint16_t currFrame = 0;
uint8_t currMode = 1;   // start with 1

#define DELAY_NORMAL 7
#define DELAY_FAST 4
#define DELAY_SLOW 18
uint8_t currDelay = DELAY_NORMAL;
uint8_t todoDelay = 0;
uint8_t findMeMode = 0;

void setup()
{
  //New FastSPI_LED2 library
  //LEDS.setBrightness(NORMBRIGHT);
  LEDS.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);

  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));  // clear memory (set to black)
  memset(ledsrow, 0, NUM_LEDSPERROW * sizeof(struct CRGB));  // clear memory (set to black)
  
  LEDS.show();
  
  InitEQ7();
  
  //button stuff
  pinMode(UPBUTTON_PIN, INPUT);
  digitalWrite(UPBUTTON_PIN, HIGH);  // pullup resistor
  attachInterrupt(0, UpButtonInterruptHandler, FALLING);
  pinMode(FINDMEBUTTON_PIN, INPUT);
  digitalWrite(FINDMEBUTTON_PIN, HIGH);  // pullup resistor
  attachInterrupt(1, FindMeButtonInterruptHandler, FALLING);
  
  //mode stuff
  InitCurrMode();
  
  #ifdef SerialDebug
  Serial.begin(9600);
  Serial << "Setup done" << endl;
  #endif
}

void loop() {
  
  if(todoDelay > 0) {
    todoDelay--;
    delay(1);
  } else {
    todoDelay = currDelay;
    
    LoopCurrMode();
    currFrame++;
    LEDS.show();
    
    CheckButton();  // only check button every "currDelay" milliseconds
  }
  
}

