#include "saw.h"

Saw::Saw() {
    std::cout << "Saw - constructor\n";
}

Saw::~Saw() {
    std::cout << "Saw - destructor\n";
}

void Saw::calculate()
{
    _sample = _phase * _amplitude;
}