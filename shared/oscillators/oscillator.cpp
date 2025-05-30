#include "oscillator.h"

Oscillator::Oscillator(float frequency)
    : Oscillator(44100.0f, frequency, 0.0f) {}

Oscillator::Oscillator(float frequency, float phase)
    : Oscillator(44100.0f, frequency, phase) {}

Oscillator::Oscillator(float sampleRate, float frequency, float phase)
    : m_samplerate(sampleRate), m_frequency(frequency),m_amplitude(1), m_phase(phase),
    m_phaseIncrement(0.0f), m_previousFrequency(-1.0f), m_sample(0) {
    // initialize m_phaseIncrement when Oscillator first constructed
    updatePhaseIncrement();
}

Oscillator::~Oscillator(){}

void Oscillator::prepare(float samplerate) {
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
    // amplitude is calculated in calculateNextSample()
    calculateNextSample();

    return m_sample;
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