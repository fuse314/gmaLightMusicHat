#ifndef EFFECTSOUND_H
#define EFFECTSOUND_H

class EffectSound : public EffectClass {
  public:
  EffectSound( uint8_t _mode);
  void step(uint16_t *_currFrame);
};
#endif
