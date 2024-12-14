#include "superSawSynth.h"

SuperSawSynth::SuperSawSynth() {
    std::cout<<"SuperSawSynth - constructor\n";
}

SuperSawSynth::~SuperSawSynth() {
  std::cout<<"SuperSawSynth - destructor\n";
}

void SuperSawSynth::tickAll(TunePlayer& tunePlayer) {
    for (int i = 0; i < NUM_SAWS; i++) {
        saws[i].tick();
    }
    // im not sure if this should be here
    if (tunePlayer._frameIndex >= tunePlayer._noteDelayFactor * SAMPLE_RATE) {
        tunePlayer._frameIndex = 0;
        tunePlayer.updatePitch(tunePlayer.tune, synth);
    }
}

float SuperSawSynth::getSamples() {
    float samples = 0;
    for (int i = 0; i < NUM_SAWS; i++) {
        samples += saws[i].getSample();
    }
    return samples/NUM_SAWS;
}