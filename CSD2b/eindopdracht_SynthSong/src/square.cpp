#include "square.h"

Square::Square(float sampleRate) : Oscillator(sampleRate) {
    std::cout << "Square - primary constructor\n";
}

Square::Square(float freqOffset, float sampleRate) : Oscillator(freqOffset, sampleRate) {
    std::cout << "Square - secondary constructor\n";
}

Square::~Square() {
    std::cout << "Square - destructor\n";
}

void Square::calculate()
{
    if (_phase < 0.5f) {
        _sample = _amplitude;
    } else {
        _sample = -_amplitude;
    }
}