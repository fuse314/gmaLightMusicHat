#ifndef EFFECTRANDOM_H
#define EFFECTRANDOM_H

class EffectRandom : public EffectClass {
  public:
  EffectRandom( uint8_t _mode);
  void step();
  
  protected:
  uint8_t RANDOM_WIDTH 4  // width of random color bar (mode 1)
};
#endif