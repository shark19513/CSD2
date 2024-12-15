#include "square.h"

Square::Square() {
    std::cout << "Square - primary constructor\n";
}

Square::Square(float freqOffset) : Oscillator(freqOffset) {
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