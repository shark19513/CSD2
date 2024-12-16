#include "saw.h"

Saw::Saw(float sampleRate) : Oscillator(sampleRate) {
    std::cout << "Saw - primary constructor\n";
}

Saw::Saw(float freqOffset, float sampleRate) : Oscillator(freqOffset, sampleRate) {
    std::cout << "Saw - secondary constructor\n";
}

Saw::~Saw() {
    std::cout << "Saw - destructor\n";
}

void Saw::calculate()
{
    _sample = _phase * _amplitude;
}