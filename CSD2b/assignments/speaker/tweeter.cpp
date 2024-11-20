#include "tweeter.h"
#include <iostream>

Tweeter::Tweeter() : Tweeter(2.5f) {
    std::cout << "Tweeter - default constructor\n";
    // number with an f --> indicate it is a float
    conePosition = 0.0f;
}

Tweeter::Tweeter(float diam) {
    std::cout << "Tweeter - overloaded constructor\n";
    // in cm
    diameter = diam;
    // number with an f --> indicate it is a float
    conePosition = 0.0f;
}