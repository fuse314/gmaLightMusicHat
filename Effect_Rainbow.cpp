//mode 0: rainbow all three rows the same
//mode 1: solid color rainbow all leds the same
//mode 2: rainbow through all leds, results in right-left-right run due to led configuration
//mode 3: horizontal rain
//mode 4: slanted bars

#include "zEffectClass.cpp"
#include "LEDColorMgt.h"

class EffectRainbow : public EffectClass {
  private:
  uint8_t _pos;
  public:
  EffectRainbow(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode) {
    _pos = 0;
    if(_mode == 3) {
      _cnf->currDelay = DELAY_KR;
    } else {
      _cnf->currDelay = DELAY_FAST;
    }
    _cnf->currBright = NORMBRIGHT;
  }

  void step(Config_t *_cnf, CRGB* _leds) {
    switch(_effectMode) {
      case 0:
        fill_rainbow( &(_leds[0]), M_WIDTH, _cnf->currFrame % 256);
        copyRowToAll(_leds);
      break;
      case 1:
        for(uint8_t i=0;i<M_WIDTH;i++) {
          _leds[i] = Wheel(_cnf->currFrame);
        }
        copyRowToAll(_leds);
      break;
      case 2:
        fill_rainbow( &(_leds[0]), NUM_LEDS, _cnf->currFrame % 256);
      break;
      case 3:
        shiftLeds(1, _leds);
        for(uint8_t i=0;i<M_HEIGHT;i++) {
          _leds[XY(M_WIDTH-1,i)] = CRGB::Black;
        }
        _leds[XY(M_WIDTH-1,random8(M_HEIGHT))] = Wheel(_cnf->currFrame);
      break;
      case 4:
        for(uint8_t i=0; i<M_WIDTH; i++) {
          for(uint8_t j=0; j<M_HEIGHT; j++) {
            _leds[XY(i,j)] = CHSV(_cnf->currHue,255,quadwave8(i*32+j*32+_pos));
          }
        }
        _pos-=4;
      break;
    }
  }
};



