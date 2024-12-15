#include "oscillator.h"
//TODO: first note is now always 220 Hz, find a way to fix
Oscillator::Oscillator() : _frequency(220), _freqOffset(0), _amplitude(1), _phase(0),
  _sample(0), _samplerate(SAMPLE_RATE) {
    std::cout << "Oscillator - primary constructor\n";
    updatePhaseIncrement(); // initialize _phaseIncrement when Oscillator first constructed
}

Oscillator::Oscillator(float freqOffset) : Oscillator() {
    std::cout << "Oscillator - secondary constructor\n";
    _freqOffset = freqOffset;
    _frequency += _freqOffset;
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

void Oscillator::tick() {
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
        this->_frequency = frequency+_freqOffset;
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