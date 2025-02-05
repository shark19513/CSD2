#include "sine.h"
#include "math.h"

Sine::Sine(float sampleRate, float frequency) : Oscillator(sampleRate, frequency) {
}

Sine::~Sine() {
}

void Sine::calculate()
{
    _sample = sin(M_PI * 2* _phase * _amplitude);
}