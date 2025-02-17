//
// Created by Semuel Leijten on 10/02/2025.
//

#include "effect.h"

Effect::Effect() : m_bypassed(false), m_wetLevel(1) {
}

Effect::~Effect() {
}

void Effect::processFrame(const float& input, float& output) {
    if (m_bypassed) {
        output = input;
    } else {
        // store dry and wet separately
        float drySignal = input;
        float wetSignal = 0.0f;

        applyEffect(input, wetSignal);
        // blend dry and wet
        output = (1.0f - m_wetLevel) * drySignal + m_wetLevel * wetSignal;
    }
}

void Effect::setWetLevel(float wetLevel) {
    // TODO: add validation
    this->m_wetLevel = wetLevel;
}

void Effect::setBypassState(bool bypassed) {
    this->m_bypassed = bypassed;
}

