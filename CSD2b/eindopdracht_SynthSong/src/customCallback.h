#include <iostream>

#include "audiocomponent.h"
#include "uiUtility.h"
#include "squareBassSynth.h"
#include "superSawSynth.h"

#ifndef CUSTOMCALLBACK_H
#define CUSTOMCALLBACK_H

#define SAMPLE_RATE 44100.0f

struct CustomCallback : AudioCallback {
    explicit CustomCallback (double Fs);
    ~CustomCallback() override;

    void prepare (int sampleRate = SAMPLE_RATE) override;

    void process (AudioBuffer buffer) override;

    void initSynthType(float sampleRate);
    void initBitCrusher();
    void initTune();

private:
    std::vector<std::string> _options;
    int _numOptions;
    std::string _selection;

    Synth* synth;
};

#endif
