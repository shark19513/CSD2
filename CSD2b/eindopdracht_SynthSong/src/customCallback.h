#include "audiocomponent.h"
//  Daan Schrier
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
    SuperSawSynth synth{SAMPLE_RATE}; // make if statement: if 1 synth 1 if 2 synth 2
    // SquareBassSynth synth{SAMPLE_RATE};
};

#endif
