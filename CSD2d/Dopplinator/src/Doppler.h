//
// Created by Semuel Leijten on 30/04/2025.
//

#ifndef DOPPLER_H
#define DOPPLER_H

#include "Effect.h"
#include "Delay.h"
#include <cmath>
#include <iostream>

class Doppler : public Effect {
public:
    Doppler(float passByDistance);
    ~Doppler() override;

    void prepare(float sampleRate) override;
    void applyEffect(const float& input, float& output) override;


    void setPassByDistance(float passByDistance);
    void setObjectPosition(float objectPosition);

private:
    void calculateDistance();
    void calculateDelayTimeMillis();

    Delay m_delay;

    /* distance from sound source object in meters */
    float m_distanceMeters;

    /* distance from trajectory in meters */
    std::atomic<float> m_passByDistanceMeters;

    /* position of the object in the trajectory in meters
     * expressed as the absolute distance from the center or magnitude */
    std::atomic<float> m_objectPositionMeters;

    float m_speedOfSound;
};



#endif //DOPPLER_H
