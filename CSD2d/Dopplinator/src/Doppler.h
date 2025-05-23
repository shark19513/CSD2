//
// Created by Semuel Leijten on 30/04/2025.
//

#ifndef DOPPLER_H
#define DOPPLER_H

#include "Effect.h"
#include "Delay.h"
#include "interpolation.h"
#include <cmath>
#include <iostream>

/* STEREO DELAY BASED DOPPLER EFFECT
 * takes bool that scales panning to the uh
 */
class Doppler : public Effect {
public:
    Doppler(float passByDistance, bool isLeftChannel);
    ~Doppler() override;

    void prepare(float sampleRate) override;
    void applyEffect(const float& input, float& output) override;


    void setPassByDistance(float passByDistance);
    void setObjectPosition(float objectPosition);

private:
    void calculateDistance();
    void calculateDelayTimeMillis();
    void calculateAmplitude(float position); // also in charge of panning

    Delay m_delay;

    float m_speedOfSound;

    /* distance from sound source object in meters */
    float m_distanceMeters;

    /* distance from trajectory in meters */
    std::atomic<float> m_passByDistanceMeters;

    /* position of the object in the trajectory in meters
     * expressed as the absolute distance from the center */
    std::atomic<float> m_objectPositionMeters;

    const bool m_isLeftChannel;
};


#endif //DOPPLER_H
