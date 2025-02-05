#include "square.h"

Square::Square(float sampleRate, float frequency) : Oscillator(sampleRate, frequency) {
}

Square::~Square() {
}

void Square::calculate()
{
    if (_phase < 0.5f) {
        _sample = _amplitude;
    } else {
        _sample = -_amplitude;
    }
}