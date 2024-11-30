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
    // TODO: implement frequency / SAMPLERATE in a more efficient way
    _phase += _frequency/_samplerate;
    if (_phase > 1.0f) {
        _phase -= 1.0f;
    }
    _sample = sin(_pi * 2 *_phase) * _amplitude;
}
