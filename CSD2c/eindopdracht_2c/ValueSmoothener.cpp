//
// Created by Semuel Leijten on 18/03/2025.
//

#include "ValueSmoothener.h"

ValueSmoothener::ValueSmoothener() :
    m_currentValue(0), m_delta(0), m_timeInSamples(24000) {}

ValueSmoothener::~ValueSmoothener() {}

void ValueSmoothener::setNewValue(float newValue) {
  float distance = m_currentValue - newValue;
  m_currentValue = newValue;
  m_delta = distance / static_cast<float>(m_timeInSamples);
}

float ValueSmoothener::genNextValue() {
  m_currentValue += m_delta;
  return m_currentValue;
}