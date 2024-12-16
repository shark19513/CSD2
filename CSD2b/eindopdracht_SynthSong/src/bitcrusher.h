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
    void setBypassBitReduction(bool bypassBitReduction);
    int _bitDepth = 4;
};

#endif