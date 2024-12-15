#include "audiocomponent.h"
//  Daan Schrier
#include "squareBassSynth.h"
#include "superSawSynth.h"

#ifndef CUSTOMCALLBACK_H
#define CUSTOMCALLBACK_H

struct CustomCallback : AudioCallback {
    explicit CustomCallback (double Fs) : AudioCallback(Fs) {

    }

    ~CustomCallback() override {

    }

    void prepare (int sampleRate) override {

    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int sample = 0u; sample < numFrames; ++sample) {
            bassSynth.tickAll();
            superSawSynth.tickAll();
            for (int channel = 0u; channel < numOutputChannels; ++channel) {
                outputChannels[channel][sample] = (bassSynth.getSamples()+superSawSynth.getSamples())/2;
            }
        }
    }

private:
    SuperSawSynth superSawSynth;
    SquareBassSynth bassSynth;
};

#endif
