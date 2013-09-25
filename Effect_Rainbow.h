#ifndef EFFECTRAINBOW_H
#define EFFECTRAINBOW_H

class EffectRainbow : public EffectClass {
  public:
  EffectRainbow( uint8_t _mode);
  void step();
};
#endif