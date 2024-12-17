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
    int _bitDepth = 2;
    bool _bypassBitCrusher = false;
};

#endif