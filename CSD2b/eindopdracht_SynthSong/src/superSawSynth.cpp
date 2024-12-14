#include "superSawSynth.h"

SuperSawSynth::SuperSawSynth() {
    std::cout<<"SuperSawSynth - constructor\n";
}

SuperSawSynth::~SuperSawSynth() {
  std::cout<<"SuperSawSynth - destructor\n";
}

void SuperSawSynth::tickAll() {
    for (int i = 0; i < _numSaws; i++) {
        saws[i].tick();
    }
}

float SuperSawSynth::getSamples() {
    float samples = 0;
    for (int i = 0; i < _numSaws; i++) {
        samples += saws[i].getSample();
    }
    return samples/_numSaws;
}