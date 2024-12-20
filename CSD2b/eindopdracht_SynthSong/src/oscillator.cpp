#include "oscillator.h"

Oscillator::Oscillator(float sampleRate) : _frequency(220), _freqOffset(0), _amplitude(1), _phase(0),
  _sample(0), _samplerate(sampleRate), _phaseIncrement(0.0f), _previousFrequency(-1.0f) {
    // initialize _phaseIncrement when Oscillator first constructed
    updatePhaseIncrement();
}

Oscillator::Oscillator(float freqOffset, float sampleRate) : Oscillator(sampleRate) {
    _freqOffset = freqOffset;
    _frequency += _freqOffset;
}

Oscillator::~Oscillator(){
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

void Oscillator::tick() {
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


void Oscillator::setFrequency(float frequency) {
    if (frequency > 0 && frequency < 22050) {
        this->_frequency = frequency+_freqOffset;
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