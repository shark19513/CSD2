#include "oscillator.h"

Oscillator::Oscillator(float sampleRate, float frequency) : m_frequency(frequency), m_amplitude(1),m_phase(0),
  m_sample(0), m_samplerate(sampleRate), m_phaseIncrement(0.0f), m_previousFrequency(-1.0f) {
    // initialize _phaseIncrement when Oscillator first constructed
    updatePhaseIncrement();
}

Oscillator::~Oscillator(){
}

void Oscillator::setSamplerate(float samplerate) {
    this->m_samplerate = samplerate;
}

void Oscillator::updatePhaseIncrement() {
    m_phaseIncrement = m_frequency / m_samplerate;
}

float Oscillator::genNextSample() {
    if (m_frequency != m_previousFrequency) {
        updatePhaseIncrement();
       m_previousFrequency = m_frequency;
    }

    m_phase += m_phaseIncrement;
    if (m_phase > 1.0f) {
        m_phase -= 1.0f;
    }
    calculateNextSample();

    return m_sample *= m_amplitude;
}


void Oscillator::setFrequency(float frequency) {
    if (frequency > 0 && frequency < 22050) {
        this->m_frequency = frequency;
    } else {
        std::cout << "Invalid input"
        << " please enter a value between 0 and 22049";
    }
}

float Oscillator::getFrequency() {
    return this->m_frequency;
}

void Oscillator::setAmplitude(float amplitude) {
    if (amplitude >= 0.0f && amplitude <= 1.0f) {
        this->m_amplitude = amplitude;
        std::cout << "Amplitude: " << this->m_amplitude << "\n";
    } else {
        std::cout << "Invalid input"
        << " please enter a value between 0 and 1.0";
    }
}

float Oscillator::getAmplitude() {
    return this->m_amplitude;
}