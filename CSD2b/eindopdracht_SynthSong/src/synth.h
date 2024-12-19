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
    virtual ~Synth();

    // set frequency for all oscillators
    virtual void setOscFreqs(float frequency) = 0;

    // call ticks for all oscillators
    virtual void tickAll() = 0;

    // get samples from all oscillators
    virtual float getSamples() = 0;

    void setBitCrusherBypass(bool bypass);
    void setBitDepth(float bitDepth);
    void setTune(std::string tuneSelection);
    float getTuneNote();
    void updateFrameIndex();
    float mtof(float mPitch);

protected:
    // method applies bitcrusher if not bypassed
    float bitCrushIfnBypassed(float samples);

    void updatePitch();

    float _samples;
    float _sampleRate;

    int _frameIndex;
    float _noteDelayFactor;

    BitCrusher bitCrusher;
    Tune* tune; // songs
};

#endif