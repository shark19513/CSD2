#include "saw.h"

Saw::Saw(float frequency, float samplerate)
    : _frequency(frequency), _amplitude(1.0), _phase(0),
      _sample(0), _samplerate(samplerate)
{
    std::cout << "Saw - constructor\n";
}

Saw::~Saw(){
    std::cout << "Saw - destructor\n";
}

void Saw::setSamplerate(float samplerate) {
    this->_samplerate = samplerate;
}

float Saw::getSample() {
    return _sample;
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

// setters/getters
void Saw::setFrequency(float frequency) {
    // TODO: add check to see if parameter is valid
    this->_frequency = frequency;
}

float Saw::getFrequency() {
    return this->_frequency;
}