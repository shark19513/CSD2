//
// Created by Semuel Leijten on 05/03/2025.
//

#ifndef STEREOCHORUS_H
#define STEREOCHORUS_H
#include <iostream>
#include "StereoEffect.h"
#include "chorus.h"


class StereoChorus : public StereoEffect {
public:
    StereoChorus(float modDepth, float modRate);
    ~StereoChorus() override;

    void prepare(float sampleRate) override;
};


#endif //STEREOCHORUS_H
