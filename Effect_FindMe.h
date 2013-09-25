#ifndef EFFECTFINDME_H
#define EFFECTFINDME_H

class EffectFindMe : public EffectClass {
  public:
  EffectFindMe( uint8_t _mode);
  void step();
  protected:
  uint8_t FINDME_WIDTH 2
};
#endif