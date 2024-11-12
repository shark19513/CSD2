#include <iostream>

class Tweeter {
public:
    // constructor
    Tweeter(float diam);
    float diameter;
    float conePosition;
};

Tweeter::Tweeter(float diam) {
    std::cout << "tweeter - constructor" << std::endl;
    // in cm
    diameter = diam;
    conePosition = 0.0f;
}



class Speaker {
public:


};

Speaker::Speaker() {
    std::cout << "Speaker - constructor" << std::endl;
}

int main() {
    Tweeter aTweeter(2.4f);

    std::cout << "Diameter of tweeter is: " << aTweeter.diameter << std::endl;
};