#include "square.h"

Square::Square() {
    std::cout << "Square - constructor\n";
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