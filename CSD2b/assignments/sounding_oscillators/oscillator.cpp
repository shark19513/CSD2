#include "oscillator.h"

Oscillator::Oscillator(float frequency, float samplerate)
: _frequency(frequency), _amplitude(1.0), _phase(0),
  _sample(0), _samplerate(samplerate)
{
    std::cout << "Oscillator - constructor\n";
}

Oscillator::~Oscillator(){
    std::cout << "Oscillator - destructor\n";
}

void Oscillator::setSamplerate(float samplerate) {
    this->_samplerate = samplerate;
}

float Oscillator::getSample() {
    return _sample;
}


// setters/getters
void Oscillator::setFrequency(float frequency) {
    // TODO: add check to see if parameter is valid
    this->_frequency = frequency;
}

float Oscillator::getFrequency() {
    return this->_frequency;
}