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
  // -0.5 to shift the phase 0.5, due to the phase shift
  // that occurs by applying the modDepth
  float modSignal = m_sine.genNextSample() * -0.5 + 0.5;
  // apply modDepth
  modSignal *= m_modDepth;
  modSignal += 1.0f - m_modDepth;

  output = input * modSignal;
}

void Tremolo::setModFreq(float freq) {
  //TODO: add validation
  m_sine.setFrequency(freq);
}