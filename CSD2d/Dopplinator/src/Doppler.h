//
// Created by Semuel Leijten on 30/04/2025.
//

#ifndef DOPPLER_H
#define DOPPLER_H

#include "Effect.h"

class Doppler : public Effect {
public:
    Doppler();
    ~Doppler() override;

    void prepare(float sampleRate) override;
    void applyEffect(const float& input, float& output) override;

};



#endif //DOPPLER_H
