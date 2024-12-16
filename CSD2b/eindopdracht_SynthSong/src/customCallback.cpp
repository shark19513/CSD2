#include "customCallback.h"

CustomCallback::CustomCallback (double Fs) : AudioCallback(Fs) {
}

CustomCallback::~CustomCallback() {
}

void CustomCallback::prepare(int sampleRate) {

}

void CustomCallback::process (AudioBuffer buffer) {
    auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

    for (int sample = 0u; sample < numFrames; ++sample) {
        synth.tickAll();
        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            outputChannels[channel][sample] = synth.getSamples();
        }
    }
}