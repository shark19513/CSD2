#include "square.h"

Square::Square(float sampleRate) : Oscillator(sampleRate) {
}

Square::Square(float freqOffset, float sampleRate) : Oscillator(freqOffset, sampleRate) {
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