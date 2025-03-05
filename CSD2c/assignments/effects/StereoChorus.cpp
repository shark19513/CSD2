//
// Created by Semuel Leijten on 05/03/2025.
//

#include "StereoChorus.h"

StereoChorus::StereoChorus(float modDepth, float modRate) {
    std::cout << "-- StereoCHorus constructor --" << std::endl;
    // init 2 chori and multiply the modDepth of the second by -1
    // this inverts the amplitude of the modulating triangle
    m_channel1 = new Chorus(modDepth, modRate);
    m_channel2 = new Chorus(modDepth * -1, modRate);
}

StereoChorus::~StereoChorus() {
    std::cout << "-- StereoCHorus destructor --" << std::endl;
    delete m_channel1;
    delete m_channel2;
    m_channel1 = nullptr;
    m_channel2 = nullptr;
}

void StereoChorus::prepare(float sampleRate) {
  m_channel1->prepare(sampleRate);
  m_channel2->prepare(sampleRate);
}