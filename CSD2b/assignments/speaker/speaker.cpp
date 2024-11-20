#include "speaker.h"
#include <iostream>

Speaker::Speaker() {
    std::cout << "Speaker - constructor\n";

    std::cout << "The diameter of the tweeter is: "
      << aTweeter.diameter << "\n";

    std::cout << "The diameter of the woofer is: "
      << aWoofer.diameter << "\n";
}