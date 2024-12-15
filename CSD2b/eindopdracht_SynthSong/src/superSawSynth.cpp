#include "superSawSynth.h"

SuperSawSynth::SuperSawSynth() {
    std::cout<<"SuperSawSynth - constructor\n";
}

SuperSawSynth::~SuperSawSynth() {
  std::cout<<"SuperSawSynth - destructor\n";
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

    return samples/NUM_SAWS;
}