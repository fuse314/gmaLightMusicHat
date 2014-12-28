// fire effect by Mark Kriegsman
// copied from http://pastebin.com/wmy3gt1P


//mode 0: fire 1
//mode 1: fire 2
//mode 2: sound fire

#include "zEffectClass.cpp"
#include "LEDColorMgt.h"

class EffectFire : public EffectClass {
  protected:
  // _heat holds the 8bit heat map for half of the leds (displayed mirrored)
  uint8_t _heat[M_HALFWIDTH][M_HEIGHT];
  // _cooling defines how fast the fire "cools" off (higher value=shorter flames)
  uint8_t _cooling;
  // _sparking defines how often a spark is created at the bottom of the flame
  uint8_t _sparking;
  
  CRGBPalette16 _palette;
  
  public:
  EffectFire(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
    _cnf->currDelay = DELAY_FIRE;
    _cnf->currBright = NORMBRIGHT;
  
    switch(_effectMode) {
      case 0:
        _cooling = 45;
        _sparking = 120;
        break;
      case 1:
        _cooling = 70;
        _sparking = 170;
        break;
    }
    _palette = HeatColors_p;
  }
  
  void step(Config_t *_cnf, CRGB* _leds) {
    if(_effectMode == 1) {
      CRGB _darkcolor  = CHSV(_cnf->currHue,255,192); // pure hue, three-quarters brightness
      CRGB _lightcolor = CHSV(_cnf->currHue,128,255); // half 'whitened', full brightness
      _palette = CRGBPalette16( CRGB::Black, _darkcolor, _lightcolor, CRGB::White);
    }
    if(_effectMode == 2) {
      _cooling = map(_cnf->eq7Vol[1],0,255, 40,90);
      _sparking = map(_cnf->eq7Vol[1],0,255, 32,100);
    }
  
    for (uint8_t row = 0; row < M_HEIGHT; row++) {
    // Step 1.  Cool down every cell a little
      for(uint8_t i = 0; i < M_HALFWIDTH; i++) {
        _heat[i][row] = qsub8( _heat[i][row],  random8(0, ((_cooling * 10) / M_HALFWIDTH) + 2));
      }
     
      // Step 2.  Heat from each cell drifts 'up' and diffuses a little
      for(uint8_t k= M_HALFWIDTH - 1; k > 0; k--) {
        _heat[k][row] = (_heat[k-1][row] + _heat[k-2][row] + _heat[k-2][row] ) / 3;
      }
      // step 2.5 Heat from each cell drifts 'left' and diffuses a little
      if(row < (M_HEIGHT-1)) {
        for(uint8_t m=M_HALFWIDTH-1; m > 0; m--) {
          _heat[m][row+1] = (_heat[m][row+1] + _heat[m][row+1] + _heat[m][row+1] + _heat[m][row] ) / 4;
        }
      }
     
      // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
      if(random8() < _sparking ) {
        uint8_t y = random8(7);
        _heat[y][row] = qadd8( _heat[y][row], random8(150,255) );
      }
     
      // Step 4.  Map from heat cells to LED colors
      uint8_t palIndex;
      for(uint8_t j = 0; j < M_HALFWIDTH; j++) {
        palIndex = scale8(_heat[j][row], 240); // scale for better results with palette colors
        _leds[XY(M_HALFWIDTH+j,row)] = _leds[XY(M_HALFWIDTH-j-1,row)] = ColorFromPalette(_palette, palIndex);
      }
    }
  }
};

