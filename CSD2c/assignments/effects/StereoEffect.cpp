//
// Created by Semuel Leijten on 05/03/2025.
//

#include "StereoEffect.h"

StereoEffect::StereoEffect()
    : m_channel1(nullptr), m_channel2(nullptr){
    std::cout << "-- StereoEffect constructor --" << std::endl;
}

StereoEffect::~StereoEffect() {
    std::cout << "-- StereoEffect destructor --" << std::endl;
}

void StereoEffect::processFrame(const float& input1, const float& input2,
                                    float& output1, float& output2) {
    m_channel1->processFrame(input1, output1);
    m_channel2->processFrame(input2, output2);
}

void StereoEffect::setWetLevel(float wetLevel) {
    m_channel1->setWetLevel(wetLevel);
    m_channel2->setWetLevel(wetLevel);
}

void StereoEffect::setBypassState(bool state) {
    m_channel1->setBypassState(state);
    m_channel2->setBypassState(state);
}
