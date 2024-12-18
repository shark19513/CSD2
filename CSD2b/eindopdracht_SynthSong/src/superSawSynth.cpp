#include "superSawSynth.h"

SuperSawSynth::SuperSawSynth(float sampleRate)
    : Synth(sampleRate)
{
    std::cout << "SuperSawSynth - constructor\n";

    // initialize saws with hardcoded detune values
    std::array<float, NUM_SAWS> detuneValues = {-8.0, -4.0, 0.0, 4.0, 8.0};
    // prevent saws from being constructed twice by reserving space
    saws.reserve(NUM_SAWS);

    for (float detune : detuneValues) {
        saws.emplace_back(detune, sampleRate);
    }
}

SuperSawSynth::~SuperSawSynth() {
    std::cout << "SuperSawSynth - destructor\n";
}


void SuperSawSynth::setOscFreqs(float frequency) {
    for (int i = 0; i < NUM_SAWS; i++) {
        saws[i].setFrequency(frequency);
    }
}

void SuperSawSynth::tickAll() {
    for (int i = 0; i < NUM_SAWS; i++) {
        saws[i].tick();
    }
    updateFrameIndex();
}

float SuperSawSynth::getSamples() {
    float samples = 0;
    for (int i = 0; i < NUM_SAWS; i++) {
        samples += saws[i].getSample();
    }
    _samples = samples/NUM_SAWS;
return bitCrushIfnBypassed(_samples);
}