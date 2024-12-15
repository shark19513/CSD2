#include "sine.h"
#include "math.h"

Sine::Sine() {
    std::cout << "Sine - primary constructor\n";
}

Sine::Sine(float freqOffset) : Oscillator(freqOffset) {
    std::cout << "Sine - secondary constructor\n";
}

Sine::~Sine() {
    std::cout << "Sine - destructor\n";
}

void Sine::calculate()
{
    _sample = sin(M_PI * 2* _phase * _amplitude);
}