#ifndef EFFECTKR_H
#define EFFECTKR_H

class EffectKR : public EffectClass {
  public:
  EffectKR( uint8_t _mode);
  void step();
  
  protected:
  uint8_t KR_WIDTH 9
};
#endif