#include "square.h"

Square::Square(float frequency, float samplerate)
    : _frequency(frequency), _amplitude(1.0), _phase(0),
      _sample(0), _samplerate(samplerate)
{
    std::cout << "Square - constructor\n";
}

Square::~Square(){
    std::cout << "Square - destructor\n";
}

void Square::setSamplerate(float samplerate) {
    this->_samplerate = samplerate;
}

float Square::getSample() {
    return _sample;
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

// setters/getters
void Square::setFrequency(float frequency) {
    // TODO: add check to see if parameter is valid
    this->_frequency = frequency;
}

float Square::getFrequency() {
    return this->_frequency;
}