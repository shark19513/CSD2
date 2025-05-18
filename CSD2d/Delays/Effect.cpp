//
// Created by Semuel Leijten on 10/02/2025.
//

#include "Effect.h"

Effect::Effect() : m_bypassed(false), m_wetLevel(1) {
}

Effect::~Effect() {
}

void Effect::processFrame(const float& input, float& output) {
    if (m_bypassed) {
        output = input;
    } else {
        // method of dry/wet blending below is partially written by an AI model
        // store dry and wet separately
        float drySignal = input;
        float wetSignal = 0.0f;

        applyEffect(input, wetSignal);
        // blend dry and wet
        output = (1.0f - m_wetLevel) * drySignal + m_wetLevel * wetSignal;
    }
}

void Effect::setWetLevel(float wetLevel) {
    if (wetLevel >= 0.0f && wetLevel <= 1.0f) {
        this->m_wetLevel = wetLevel;
    } else {
        std::cout << "- Effect::setWetLevel -\n"
        << "! invalid input !\n"
        << "- please enter a value between 0.0 and 1.0 -\n";
    }
}

void Effect::setBypassState(bool bypassed) {
    this->m_bypassed = bypassed;
}

float Effect::getWetLevel() {
    return this->m_wetLevel;
}

bool Effect::getBypassState() {
    return this->m_bypassed;
}
