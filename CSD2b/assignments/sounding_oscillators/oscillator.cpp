#include "oscillator.h"

Oscillator::Oscillator(float frequency, float samplerate)
: _frequency(frequency), _amplitude(1.0), _phase(0),
  _sample(0), _samplerate(samplerate)
{
    std::cout << "Oscillator - constructor\n";
    updatePhaseIncrement(); // initialize _phaseIncrement when Osc first constructed
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

void Oscillator::updatePhaseIncrement() {
    _phaseIncrement = _frequency / _samplerate;
}


// setters/getters
void Oscillator::setFrequency(float frequency) {
    if (frequency > 0 && frequency < 22050) {
        this->_frequency = frequency;
        std::cout << "Frequency: " << this->_frequency << "\n";
    } else {
        std::cout << "Invalid input"
        << " please enter a value between 0 and 22049";
    }
}

float Oscillator::getFrequency() {
    return this->_frequency;
}