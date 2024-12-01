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

        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            for (int sample = 0u; sample < numFrames; ++sample) {
                // write sample to buffer at channel 0, amp = 0.25
                outputChannels[channel][sample] = synth.sineOsc.getSample();
                synth.sineOsc.tick();
            }
        }
    }

private:
    //TODO: add these signals up so they can be outputted at the same time
    // Sine sine{440};
    // Saw saw{440};
    // Square square{440};

    Synth synth;
};
