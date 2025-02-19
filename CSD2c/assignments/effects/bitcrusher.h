//
// Created by Semuel Leijten on 19/02/2025.
//

#ifndef BITCRUSHER_H
#define BITCRUSHER_H
#include <iostream>
#include "effect.h"


class BitCrusher : public Effect {
public:
    BitCrusher(unsigned int bitDepth);
    ~BitCrusher() override;

    void prepare(float sampleRate) override;
    void applyEffect(const float& input, float& output) override;
    void setBitDepth(unsigned int bitDepth);

private:
    unsigned int m_bitDepth;
    float m_stepSize;
};



#endif //BITCRUSHER_H
