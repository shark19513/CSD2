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

protected:

    float _samples;
    float _sampleRate;

    //bitcrusher
    BitCrusher bitCrusher;
    void setBypassBitCrusher(bool bypassBitCrusher);
    bool _bypassBitCrusher = false;

    // tune playing stuff
    FairyTune fairyTune;
    ArpeggioTune arpeggioTune;

    double mtof(float mPitch);
    void updatePitch();
    void updateFrameIndex();
    void setTuneselection(int tuneselection);

    int _frameIndex = 0;
    double _noteDelayFactor = 0.11;
    int _tuneSelection = 1;
};

#endif