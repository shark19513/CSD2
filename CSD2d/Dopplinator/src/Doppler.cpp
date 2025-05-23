//
// Created by Semuel Leijten on 30/04/2025.
//

#include "Doppler.h"

#define MAX_OBJECT_POSITION 100.0f

Doppler::Doppler(float passByDistance, bool isLeftChannel):
                    m_delay(1.0f, 3000.0f),
                    m_speedOfSound(343.0f),
                    m_distanceMeters(0.0f),
                    m_passByDistanceMeters(passByDistance),
                    m_objectPositionMeters(0.0f),
                    m_isLeftChannel(isLeftChannel) {
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

void Doppler::calculateAmplitude(float position) {
    /* scales the signed position from -MAX_OBJECT_POSITION to MAX_OBJECT_POSITION
     * to create panning effect when paired with second instance */
    //TODO: this might be a really inefficient way to do panning
    float panning = 0.0f; //NOTE: ?????
    if (m_isLeftChannel) {
        setAmplitude(Interpolation::mapInRange(position,
                                        -MAX_OBJECT_POSITION, MAX_OBJECT_POSITION,
                                        1.0f, 0.0f));
    } else {
        setAmplitude(Interpolation::mapInRange(position,
                                        -MAX_OBJECT_POSITION, MAX_OBJECT_POSITION,
                                        0.0f, 1.0f));
    }
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
     float position = std::abs(objectPosition); //store the absolute value
     if (position <= MAX_OBJECT_POSITION) {
         m_objectPositionMeters = position;
         calculateDistance();
         calculateDelayTimeMillis();
         calculateAmplitude(objectPosition); //this method does need the signed value though
     } else {
         std::cout << "--Doppler::setObjectPosition --\n"
                   << "! invalid input !\n"
                   << "- please enter a value between -" << MAX_OBJECT_POSITION
                   << " and " << MAX_OBJECT_POSITION << " -\n";
     }
}

