#include "synthesizer.h"

Synthesizer::Synthesizer() {
    std::cout << "inside Synthesizer constructor" << std::endl;
    std::cout << "Osc1 freq: " << osc1.getFrequency() << std::endl;
    std::cout << "Osc1 waveform: " << osc1.getWaveform() << std::endl;
    std::cout << "Osc2 freq: " << osc2.getFrequency() << std::endl;
    std::cout << "Osc2 waveform: " << osc2.getWaveform() << std::endl;
    std::cout << "Osc3 freq: " << osc3.getFrequency() << std::endl;
    std::cout << "Osc3 waveform: " << osc3.getWaveform() << std::endl;

}

Synthesizer::~Synthesizer() {
    std::cout << "inside Synthesizer destructor" << std::endl;
}


void Synthesizer::play() {
    std::cout << "inside Synthesizer play" << std::endl;
}