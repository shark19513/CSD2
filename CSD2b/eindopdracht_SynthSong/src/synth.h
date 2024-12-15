#ifndef SYNTH_H
#define SYNTH_H

#include "sine.h"
#include "saw.h"
#include "square.h"
#include "tunes.h"

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
    float _samples;

    // bitreduction
    float applyBitReduction(float sample);
    void setBitDepth(int bitDepth);
    void setBypassBitReduction(bool bypassBitReduction);
    bool _bypassBitReduction = false;
    int _bitDepth = 4;

    // tune playing stuff
    double mtof(float mPitch);
    void updatePitch();
    void updateFrameIndex();

    int _frameIndex = 0;
    double _noteDelayFactor = 0.11;

    FairyTune tune;
    //TODO: make array with tunes? or make the tune in a method? elif tree?? idk????

    // userInterface ui; //TODO: build UI
};

#endif