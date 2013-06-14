#include <FastSPI_LED.h>

// 38 LEDs * 3
// configuration:
//   ==> 76 77 78 79 .. 112 113
//   <== 75 74 73 72 ..  39  38
//   ==>  0  1  2  3 ..  36  37
#define NUM_LEDS 114
#define NUM_ROWS 3
#define NUM_LEDSPERROW 38
struct CRGB { unsigned char g; unsigned char r; unsigned char b; };
// struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;
struct CRGB *ledsrow[NUM_LEDSPERROW];
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
uint8_t  currMode = 1;


void setup()
{
  FastSPI_LED.setCPUPercentage(50);  // if the stand starts flickering, up this value
  FastSPI_LED.setLeds(NUM_LEDS);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_WS2811);

  FastSPI_LED.setPin(LED_PIN);
  
  FastSPI_LED.init();
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData();
  memset(leds, 0, NUM_LEDS * 3);
  memset(ledsrow, 0, NUM_LEDSPERROW * 3);
  FastSPI_LED.show();
  
  InitEQ7();
  
  //button stuff
  pinMode(buttonPin, INPUT);
}

void loop() { 
  
  currFrame++;
  
  
  
  
  for (int currFrame = 0; currFrame < NUM_LEDS*4; currFrame++) {
    for (int i=0; i < NUM_LEDS; i++) {
      leds[i] = Wheel((i+currFrame) % 96);
    }
    FastSPI_LED.show();
    delay(6);
  }
  
  for (int i=0; i < 14; i++) {
    if( i % 2 == 1) {
      SetSolidColor(GetColor(0,0,0));
    } else {
      SetSolidColor(GetColor(255,255,255));
    }
    FastSPI_LED.show();
    delay(1000);
  }
  
}

