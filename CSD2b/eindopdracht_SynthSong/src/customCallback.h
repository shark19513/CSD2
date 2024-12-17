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

private:
    Synth* synth;
};

#endif
