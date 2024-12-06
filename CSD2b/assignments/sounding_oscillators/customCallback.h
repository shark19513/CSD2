#include "audiocomponent.h"
//  Daan Schrier
#include "sine.h"
#include "saw.h"
#include "square.h"
#include "synth.h"

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
            synth.tickAll();
            for (int channel = 0u; channel < numOutputChannels; ++channel) {
                outputChannels[channel][sample] = synth.getSamples();
            }
        }
    }

private:
    Synth synth;
};
