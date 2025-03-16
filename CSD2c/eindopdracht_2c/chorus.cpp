#include "chorus.h"

Chorus::Chorus(float modDepth, float modRate)
    : Chorus(modDepth, modRate, 0.0f) {}

Chorus::Chorus(float modDepth, float modRate, float modSignalPhase)
    : Delay(20.0f, 40.0f),
      m_sine(modRate, modSignalPhase) {
    setModDepth(modDepth);
    setWetLevel(0.5);
}

Chorus::~Chorus() {}

void Chorus::prepare(float sampleRate) {
    this->m_sampleRate = sampleRate;
    m_sine.prepare(sampleRate);

    m_bufferSize = millisecondsToSamples(m_maxDelayTimeMillis);
    allocateBuffer();
    setDelayTime(m_delayTimeMillis);
}

void Chorus::applyEffect(const float& input, float& output) {
  // modsignal is bipolar so no phase shift
  float modSignal = m_sine.genNextSample();
  // scale modulation and convert to samples
  unsigned int modDelaySamples = millisecondsToSamples(m_delayTimeMillis
                                              + (modSignal * m_modDepth));
  setDistanceRW(modDelaySamples);

  // apply delay
  output = m_buffer[m_readH];
  incrReadH();
  m_buffer[m_writeH] = input + output * m_feedback;
  incrWriteH();
}

void Chorus::setModDepth(float modDepth) {
if (modDepth >= 0.1f && modDepth <= 15.0f) {
  this->m_modDepth = modDepth;
} else {
    std::cout << "- Chorus::setModDepth -\n"
    << "! invalid input !\n"
    << "- please enter a value between 0.0 and 15.0 -\n";
    }
}

void Chorus::setModRate(float modRate) {
    if (modRate >= 0.1f && modRate <= 10.0f) {
        m_sine.setFrequency(modRate);
    } else {
        std::cout << "- Chorus::setModRate -\n"
        << "! invalid input !\n"
        << "- please enter a value between 0.0 and 15.0 -\n";
    }
}