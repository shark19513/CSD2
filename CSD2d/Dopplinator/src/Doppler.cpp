//
// Created by Semuel Leijten on 30/04/2025.
//

#include "Doppler.h"

Doppler::Doppler(float passByDistance): m_delay(1.0f, 3000.0f),
                    m_distanceMeters(0.0f),
                    m_passByDistanceMeters(passByDistance),
                    m_objectPositionMeters(0.0f),
                    m_speedOfSound(343.0f)
{
    // prepare() should always be called before use
}

Doppler::~Doppler() {}

void Doppler::prepare(float sampleRate) {
    m_delay.prepare(sampleRate);
}

void Doppler::applyEffect(const float& input, float& output){
    m_delay.processFrame(input, output);
  }

void Doppler::calculateDistance() {
    /* Pythagoras go brrrrrrrr */
    const float a = m_passByDistanceMeters;
    const float b = m_objectPositionMeters;
    const float c = std::sqrt(a*a + b*b);

    m_distanceMeters = c;
}

void Doppler::calculateDelayTimeMillis() {
    /* delay = distance / speed of sound * 1000 */
    const float delayTimeMillis = m_distanceMeters/m_speedOfSound * 1000.0f;
    m_delay.setDelayTimeMillis(delayTimeMillis);
}


void Doppler::setPassByDistance(float passByDistance) {
    /* passByDistance can range from 1 to 100 meters */
    if (passByDistance >= 1.0f && passByDistance <= 100.0f) {
        m_passByDistanceMeters = passByDistance;
        calculateDistance();
        calculateDelayTimeMillis();
    } else {
        std::cout << "--Doppler::setPassByDistance --\n"
                  << "! invalid input !\n"
                  << "- please enter a value between 1.0 and 100.0 - \n";
    }
}

void Doppler::setObjectPosition(float objectPosition) {
    /* accepts any signed value ranging from -1000 - 1000
     * the greater the value the greater the distance
     * stores only its absolute value */
     float position = std::abs(objectPosition);
     if (position <= 1000.0f) {
         m_objectPositionMeters = position; //store the absolute distance
         calculateDistance();
         calculateDelayTimeMillis();
     } else {
         std::cout << "--Doppler::setObjectPosition --\n"
                   << "! invalid input !\n"
                   << "- please enter a value between -1000.0 and 1000.0 - \n";
     }
}

