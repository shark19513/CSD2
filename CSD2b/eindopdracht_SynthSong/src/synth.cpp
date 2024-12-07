#include "synth.h"

Synth::Synth() {
  std::cout << "Synth - Constructor\n";
  userInterface();
}

Synth::~Synth() {
  std::cout << "Synth - Destructor\n";
}

void Synth::userInterface() { //TODO: this is not working
  std::cout << "Synth - User Interface\n";
  while (true) {
    switch (std::cin.get()) {
      case 'f-sine':
        float frequency = std::cin.get();
        sineOsc.setFrequency(frequency);
    }
  }
}


void Synth::tickAll() {
  sineOsc.tick();
  sawOsc.tick();
  squareOsc.tick();
}

float Synth::getSamples() {
  return (sineOsc.getSample()+sawOsc.getSample()+squareOsc.getSample())/3;
}