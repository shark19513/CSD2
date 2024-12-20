#include "superSawSynth.h"

SuperSawSynth::SuperSawSynth(float sampleRate, float detune)
    : Synth(sampleRate) {
    float detuneMultiplier = detune;
    // initialize super saw with detuneness
    std::array<float, NUM_SAWS> detuneValues = {-2 * detuneMultiplier, -1 * detuneMultiplier, 0.0,
                                                    1 * detuneMultiplier, 2 * detuneMultiplier};
    // prevent saws from being constructed twice by reserving space
    saws.reserve(NUM_SAWS);
    for (float detuneValue : detuneValues) {
        saws.emplace_back(detuneValue, sampleRate);
    }
}

SuperSawSynth::~SuperSawSynth() {
}


void SuperSawSynth::setOscFreqs(float frequency) {
    // got uint8_t from Daan (it gives warnings otherwise)
    for (uint8_t i = 0; i < NUM_SAWS; i++) {
        saws[i].setFrequency(frequency);
    }
}

void SuperSawSynth::tickAll() {
    for (uint8_t i = 0u; i < NUM_SAWS; i++) {
        saws[i].tick();
    }
}

float SuperSawSynth::getSamples() {
    float samples = 0;
    for (uint8_t i = 0; i < NUM_SAWS; i++) {
        samples += saws[i].getSample();
    }
    _samples = samples/NUM_SAWS;
return bitCrushIfnBypassed(_samples);
}