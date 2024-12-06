#include "sine.h"
#include "math.h" // what is this doing here?

Sine::Sine(float frequency) : Oscillator(frequency) {
    std::cout << "Sine - constructor\n";
}

Sine::~Sine() {
    std::cout << "Sine - destructor\n";
}

void Sine::tick()
{
    if (_frequency != _previousFrequency) {
        updatePhaseIncrement();
        _previousFrequency = _frequency;
    }
    //TODO: move this stuff to baseclass and rename this function calculate
    _phase += _phaseIncrement;
    if (_phase > 1.0f) {
        _phase -= 1.0f;
    }

    _sample = sin(_pi * 2 *_phase) * _amplitude;
}