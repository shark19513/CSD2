#include "sine.h"
#include "math.h" // what is this doing here?

Sine::Sine(float frequency, float samplerate)
    : _frequency(frequency), _amplitude(1.0), _phase(0),
      _sample(0), _samplerate(samplerate)
{
    std::cout << "Sine - constructor\n";
}

Sine::~Sine(){
    std::cout << "Sine - destructor\n";
}

void Sine::setSamplerate(float samplerate) {
    this->_samplerate = samplerate;
}

float Sine::getSample() {
    return _sample;
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

// setters/getters
void Sine::setFrequency(float frequency) {
    // TODO: add check to see if parameter is valid
    this->_frequency = frequency;
}

float Sine::getFrequency() {
    return this->_frequency;
}