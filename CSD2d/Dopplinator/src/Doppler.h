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
 * takes bool that flips panning
 */
class Doppler : public Effect {
public:
    Doppler(float passByDistanceMeters, bool isLeftChannel);
    ~Doppler() override;

    void prepare(float sampleRate) override;
    void applyEffect(const float& input, float& output) override;


    void setPassByDistance(float passByDistance);
    void setObjectPosition(float sliderPosition);

private:
    float calculateDistance(float objectPositionMeters);
    void calculateDelayTimeMillis();
    void calculatePanning(float sliderPosition);
    void calculateAmplitude();

    Delay m_delay;

    float m_speedOfSound;

    /* distance from sound source object in meters */
    float m_distanceMeters;
    float m_maxDistanceMeters; //max value distance can be with current pass by distance

    /* distance from trajectory in meters */
    std::atomic<float> m_passByDistanceMeters;

    /* position of the object in the trajectory in meters
     * expressed as the absolute distance from the center */
    std::atomic<float> m_objectPositionMeters;

    /* fields used for panning logic*/
    const bool m_isLeftChannel;
    float m_toLeft;
    float m_toRight;
    float m_panning;
};


#endif //DOPPLER_H
