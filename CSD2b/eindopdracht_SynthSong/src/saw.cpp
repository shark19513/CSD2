#include "saw.h"

Saw::Saw() {
    std::cout << "Saw - primary constructor\n";
}

Saw::Saw(float freqOffset) : Oscillator(freqOffset) {
    std::cout << "Saw - secondary constructor\n";
}

Saw::~Saw() {
    std::cout << "Saw - destructor\n";
}

void Saw::calculate()
{
    _sample = _phase * _amplitude;
}