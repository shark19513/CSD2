#ifndef SYNTH_H
#define SYNTH_H

#include "sine.h"
#include "saw.h"
#include "square.h"
#include "tunes.h"
#include "bitcrusher.h"

class Synth {
public:
    Synth(float sampleRate);
    ~Synth();

    // set frequency for all oscillators
    virtual void setOscFreqs(float frequency) = 0;

    // call ticks for all oscillators
    virtual void tickAll() = 0;

    // get samples from all oscillators
    virtual float getSamples() = 0;

    void setBypassBitCrusher(bool bypassBitCrusher);
    void setBitDepth(int bitDepth);
    void setTune(std::string tuneSelection);

protected:
    // tune playing methods
    double mtof(float mPitch);
    void updatePitch();
    void updateFrameIndex();

    float _samples;
    float _sampleRate;

    int _frameIndex = 0;
    double _noteDelayFactor = 0.11;

    BitCrusher bitCrusher;
    Tune* tune;
};

#endif