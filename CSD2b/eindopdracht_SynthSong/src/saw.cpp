#include "saw.h"

Saw::Saw(float frequency) : Oscillator(frequency) {
    std::cout << "Saw - constructor\n";
}

Saw::~Saw() {
    std::cout << "Saw - destructor\n";
}

void Saw::calculate()
{
    _sample = _phase * _amplitude;
}