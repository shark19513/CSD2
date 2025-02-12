//
// Created by Semuel Leijten on 10/02/2025.
//

#include "effect.h"

Effect::Effect() {

}

Effect::~Effect() {

}

void Effect::processFrame(const float &input, float &output) {
    //TODO: bypass check
    applyEffect(input, output);
    //TODO: dry/wet
}
