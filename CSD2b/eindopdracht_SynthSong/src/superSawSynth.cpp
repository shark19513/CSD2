#include "superSawSynth.h"

SuperSawSynth::SuperSawSynth(float sampleRate)
    : Synth(sampleRate)
{
    std::cout << "SuperSawSynth - constructor\n";

    std::array<float, NUM_SAWS> detuneValues = {-8.0f, -4.0f, 0.0f, 4.0f, 8.0f};

    saws.reserve(NUM_SAWS); // prevent saws from being constructed twice by reserving space
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

    if (_bypassBitCrusher == true) { //TODO: this could be more efficient
        return _samples;
    } else {
        return bitCrusher.applyBitReduction(_samples);
    }
}