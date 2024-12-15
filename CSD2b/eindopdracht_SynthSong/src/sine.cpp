#include "sine.h"
#include "math.h"

Sine::Sine() {
    std::cout << "Sine - constructor\n";
}

Sine::~Sine() {
    std::cout << "Sine - destructor\n";
}

void Sine::calculate()
{
    _sample = sin(M_PI * 2* _phase * _amplitude);
}