#include "woofer.h"
#include <iostream>

Woofer::Woofer() : Woofer(7) {
    std::cout << "Woofer - default constructor" << std::endl;

    conePosition = 0.0f;
}

Woofer::Woofer(float diam) {
    std::cout << "Woofer - overloaded constructor" << std::endl;

    diameter = diam;
    conePosition = 0.0f;
}