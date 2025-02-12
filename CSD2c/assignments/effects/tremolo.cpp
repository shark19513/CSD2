#include "tremolo.h"

Tremolo::Tremolo(float frequency, float modDepth)
    : m_sine(frequency), m_modDepth(modDepth) {}

Tremolo::~Tremolo() {}

void Tremolo::prepare(float sampleRate) {
  //TODO: add validation
  m_sine.prepare(sampleRate);
}

void Tremolo::applyEffect(const float& input, float& output) {
  // transform sine in range [-1, 1] to range [0, 1]
  float modSignal = m_sine.genNextSample();
  // apply modDepth
  modSignal *= m_modDepth;
  modSignal += 1.0f - m_modDepth;
  // apply mod signal to input
  output = input * modSignal;
}

void Tremolo::setModFreq(float freq) {
  //TODO: add validation
  m_sine.setFrequency(freq);
}