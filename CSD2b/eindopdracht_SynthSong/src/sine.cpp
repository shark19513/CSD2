#include "sine.h"
#include "math.h"

Sine::Sine(float sampleRate) : Oscillator(sampleRate) {
}

Sine::Sine(float freqOffset, float sampleRate) : Oscillator(freqOffset, sampleRate) {
}

Sine::~Sine() {
}

void Sine::calculate()
{
    _sample = sin(M_PI * 2* _phase * _amplitude);
}