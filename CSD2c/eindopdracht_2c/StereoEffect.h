//
// Created by Semuel Leijten on 05/03/2025.
//

#ifndef STEREOEFFECT_H
#define STEREOEFFECT_H
#include <iostream>

#include "effect.h"

class StereoEffect {
public:
    StereoEffect();
    virtual ~StereoEffect();

    virtual void prepare(float sampleRate);
    void processFrame(const float& input1, const float& input2,
                        float& output1, float& output2);
    void setWetLevel(float wetLevel);
    void setBypassState(bool state);

protected:
    Effect* m_channel1;
    Effect* m_channel2;
};


#endif //STEREOEFFECT_H
