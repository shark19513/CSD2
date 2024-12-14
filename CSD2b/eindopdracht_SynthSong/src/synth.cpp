#include "synth.h"

Synth::Synth() : oscillators(_numOsc) {
  std::cout << "Synth - Constructor\n";

  // this stuff is temporary
  // oscillators.resize(_numOsc);
  // oscillators[0] = new Sine(440, 0.2);
  // oscillators[1] = new  Saw(440, 0.2);

}

Synth::~Synth() {
  std::cout << "Synth - Destructor\n";
}

void Synth::tickAll() {
  for (int i = 0; i < _numOsc; i++) {
    oscillators[i].tick();
  }
  // sineOsc.tick();
  // sawOsc.tick();
  // squareOsc.tick();
}

float Synth::getSamples() {
  float samples = 0;
  for (int i = 0; i < _numOsc; i++) {
    samples += oscillators[i].getSample();
  }
  // return (sineOsc.getSample()+sawOsc.getSample()+squareOsc.getSample())/3;
  return samples;
}

//TODO: make setnumOsc function???? find a way to pass numOsc to synth baseclass