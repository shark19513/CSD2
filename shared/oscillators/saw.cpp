#include "saw.h"

Saw::Saw(float sampleRate, float frequency) : Oscillator(sampleRate, frequency) {
}

Saw::~Saw() {
}

void Saw::calculate()
{
    _sample = _phase * _amplitude;
}