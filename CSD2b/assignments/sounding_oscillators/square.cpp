#include "square.h"

Square::Square(float frequency) : Oscillator(frequency) {
    std::cout << "Square - constructor\n";
}

Square::~Square() {
    std::cout << "Square - destructor\n";
}


void Square::tick()
{
    if (_frequency != _previousFrequency) {
        updatePhaseIncrement();
        _previousFrequency = _frequency;
    }

    _phase += _phaseIncrement;
    if (_phase > 1.0f) {
        _phase -= 1.0f;
    }
    
    if (_phase < 0.5f) {
        _sample = _amplitude;
    } else {
        _sample = -_amplitude;
    }
}