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

void Oscillator::tick()
{
    // calculate _frequency/_samplerate only when the frequency changes
    if (_frequency != _previousFrequency) {
        updatePhaseIncrement();
        _previousFrequency = _frequency;
    }

    _phase += _phaseIncrement;
    if (_phase > 1.0f) {
        _phase -= 1.0f;
    }
    calculate();
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

void Oscillator::setAmplitude(float amplitude) {
    if (amplitude >= 0.0f && amplitude <= 1.0f) {
        this->_amplitude = amplitude;
        std::cout << "Amplitude: " << this->_amplitude << "\n";
    } else {
        std::cout << "Invalid input"
        << " please enter a value between 0 and 1.0";
    }
}

float Oscillator::getAmplitude() {
    return this->_amplitude;
}