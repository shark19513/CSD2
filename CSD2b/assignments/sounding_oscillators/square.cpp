#include "square.h"

Square::Square(float frequency) : Oscillator(frequency) {
    std::cout << "Square - constructor\n";
}

Square::~Square() {
    std::cout << "Square - destructor\n";
}


void Square::tick()
{
    // TODO: implement frequency / SAMPLERATE in a more efficient way
    _phase += _frequency/_samplerate;
    if (_phase > 1.0f) {
        _phase -= 1.0f;
    }
    if (_phase < 0.5f) {
        _sample = _amplitude;
    } else {
        _sample = -_amplitude;
    }
}