#ifndef SYNTH_H
#define SYNTH_H

#include "sine.h"
#include "saw.h"
#include "square.h"
#include "tune.h"

class Synth {
public:
    Synth();
    ~Synth();

protected:
    // set frequency for all oscillators
    virtual void setOscFreqs(float frequency) = 0;

    // call ticks for all oscillators
    virtual void tickAll() = 0;

    // get samples from all oscillators
    virtual float getSamples() = 0;

    // userInterface ui; //TODO: build UI

    // tune playing stuff
    double mtof(float mPitch);
    void updatePitch();
    void updateFrameIndex();

    int _frameIndex = 0;
    double _noteDelayFactor = 0.1;

    Tune tune;

    //TODO: make array with tunes? or something
};

#endif