#include "saw.h"

Saw::Saw(float sampleRate) : Oscillator(sampleRate) {
}

Saw::Saw(float freqOffset, float sampleRate) : Oscillator(freqOffset, sampleRate) {
}

Saw::~Saw() {
}

void Saw::calculate()
{
    _sample = _phase * _amplitude;
}