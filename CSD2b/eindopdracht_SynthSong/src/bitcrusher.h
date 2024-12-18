#ifndef BITCRUSHER_H
#define BITCRUSHER_H

#include <iostream>

class BitCrusher {
  public:
    BitCrusher();
    ~BitCrusher();

    // bitreduction
    float applyBitReduction(float sample);
    void setBitDepth(int bitDepth);
    void setBypassState(bool bypass);
    bool getBypassState();

private:
    bool _bypassState = false;
    int _bitDepth = 2;
};

#endif