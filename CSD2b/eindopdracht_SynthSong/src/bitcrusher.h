#ifndef BITCRUSHER_H
#define BITCRUSHER_H

#include <iostream>

class BitCrusher {
  public:
    BitCrusher(bool bypassBitCrusher);
    ~BitCrusher();

    // bitreduction
    float applyBitReduction(float sample);
    void setBitDepth(int bitDepth);
    void setBypassBitReduction(bool bypassBitReduction);
    bool _bypassBitReduction;
    int _bitDepth = 4;
};

#endif