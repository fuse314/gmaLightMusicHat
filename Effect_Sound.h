#ifndef EFFECTSOUND_H
#define EFFECTSOUND_H

class EffectSound : public EffectClass {
  public:
  EffectSound(uint8_t _mode, Config_t *_cnf);
  void step(Config_t *_cnf, CRGB* _leds, CRGB* _ledsrow);
};
#endif
