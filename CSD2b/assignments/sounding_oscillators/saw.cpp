#include "saw.h"

Saw::Saw(float frequency) : Oscillator(frequency) {
    std::cout << "Saw - constructor\n";
}

Saw::~Saw() {
    std::cout << "Saw - destructor\n";
}

void Saw::tick()
{
    if (_frequency != _previousFrequency) {
        updatePhaseIncrement();
        _previousFrequency = _frequency;
    }

    _phase += _phaseIncrement;
    if (_phase > 1.0f) {
        _phase -= 1.0f;
    }

    _sample = _phase * _amplitude;
}
