#ifndef EFFECTCLASS_H
#define EFFECTCLASS_H
// abstract class EffectClass to be inherited by different Effects
class EffectClass {
  public:
    // constructor
    EffectClass(uint8_t _mode = 0);
    // step function is called from loop
    virtual void step() = 0; 
};

#endif
