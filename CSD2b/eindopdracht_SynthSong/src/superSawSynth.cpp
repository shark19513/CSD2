#include "superSawSynth.h"

SuperSawSynth::SuperSawSynth() {
    std::cout<<"SuperSawSynth - constructor\n";
}

SuperSawSynth::~SuperSawSynth() {
  std::cout<<"SuperSawSynth - destructor\n";
}


void SuperSawSynth::setOscFreq(float frequency) {
    std::cout << "setOscFreq " << frequency << std::endl;
    for (int i = 0; i < NUM_SAWS; i++) {
        saws[i].setFrequency(frequency);
    }
}

void SuperSawSynth::tickAll() {
    for (int i = 0; i < NUM_SAWS; i++) {
        saws[i].tick();
    }
    if (_frameIndex >= _noteDelayFactor * SAMPLE_RATE) {
        _frameIndex = 0;
        updatePitch();
    } else {
        _frameIndex++;
    }
}

float SuperSawSynth::getSamples() {
    float samples = 0;
    for (int i = 0; i < NUM_SAWS; i++) {
        samples += saws[i].getSample();
    }

    return samples/NUM_SAWS;
}

void SuperSawSynth::updatePitch() {
    float note = tune.getNote();
    double freq = mtof(note);
    std:: cout << "next note: " << note << ", has frequency " << freq << "\n";
    setOscFreq(freq);
}