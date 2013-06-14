/*
  Three LED Strips mounted on hat for music festivals
  using MSGEQ7 chip and microphone to react to music
  (c) 2013 by Gottfried Mayer www.gma.name
  
  Uses FastSPI to control WS2811 controller chips
  
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
#include <FastSPI_LED.h>

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

struct CRGB { unsigned char g; unsigned char r; unsigned char b; };
// struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;
struct CRGB *ledsrow;  // used for mirrored effects and one-row-for-all effects
struct CRGB currEQColor;
#define LED_PIN 4

#define NORMBRIGHT 60  // maximum brightness of leds (0-255)
#define MAXBRIGHT 120  // used for "find me" mode


//MSGEQ7 stuff
#define EQ7STROBE_PIN 2
#define EQ7RESET_PIN 3
#define EQ7IN_PIN A1
#define NOISE_LVL 100     // noise cutoff value

uint16_t eq7Values[7];
// [0], [1], [2],  [3],  [4],  [5],   [6]
//  63, 160, 400, 1000, 2500, 6250, 16000 Hz


//button stuff
#define BUTTON_PIN 5

//loop stuff
uint16_t currFrame = 0;
#define MAX_MODE 3       // maximum number of modes
uint8_t currMode = 1;
uint8_t currDelay = 20;
uint8_t todoDelay = 0;


void setup()
{
  FastSPI_LED.setCPUPercentage(50);  // if the stand starts flickering, up this value
  FastSPI_LED.setLeds(NUM_LEDS);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_WS2811);

  FastSPI_LED.setPin(LED_PIN);
  
  FastSPI_LED.init();
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData();  // allocate memory for all leds
  memset(leds, 0, NUM_LEDS * 3);  // clear memory (set to black)
  ledsrow = (struct CRGB*)malloc(NUM_LEDSPERROW * 3); // allocate memory for one line of leds
  memset(ledsrow, 0, NUM_LEDSPERROW * 3);  // clear memory (set to black)
  FastSPI_LED.show();
  
  InitEQ7();
  
  //button stuff
  pinMode(buttonPin, INPUT);
  
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
    FastSPI_LED.show();
    
    CheckButton();  // only check button every "currDelay" microseconds
  }
  
}

