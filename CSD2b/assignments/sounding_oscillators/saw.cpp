#include "saw.h"

Saw::Saw(float frequency) : Oscillator(frequency) {
    std::cout << "Saw - constructor\n";
}

Saw::~Saw() {
    std::cout << "Saw - destructor\n";
}

void Saw::tick()
{
    // TODO: implement frequency / SAMPLERATE in a more efficient way
    _phase += _frequency/_samplerate;
    if (_phase > 1.0f) {
        _phase -= 1.0f;
    }
    _sample = _phase * _amplitude;
}
