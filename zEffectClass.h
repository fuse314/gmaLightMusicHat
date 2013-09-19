#ifndef EFFECTCLASS_H
#define EFFECTCLASS_H
// abstract class EffectClass to be inherited by different Effects
class EffectClass {
  public:
    // constructor
    EffectClass(uint8_t _mode);
    // initialize effect animation
    virtual void init(uint8_t _mode) { /* not implemented */ }
    // step function is called from loop
    virtual void step() { /* not implemented */ } 
};
#endif