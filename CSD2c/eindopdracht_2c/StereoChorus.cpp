//
// Created by Semuel Leijten on 05/03/2025.
//

#include "StereoChorus.h"

StereoChorus::StereoChorus(float modDepth, float modRate) {
    std::cout << "-- StereoChorus constructor --" << std::endl;
    // init 2 chori
    // phase of the modulating signal is shifted for channel 2 for stereo effect
    m_channel1 = new Chorus(modDepth, modRate);
    m_channel2 = new Chorus(modDepth, modRate, 0.25);
}

StereoChorus::~StereoChorus() {
    std::cout << "-- StereoChorus destructor --" << std::endl;
    delete m_channel1;
    delete m_channel2;
    m_channel1 = nullptr;
    m_channel2 = nullptr;
}