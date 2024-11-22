#include "speaker.h"
#include <iostream>

Speaker::Speaker() {
    std::cout << "Speaker - constructor\n";

    std::cout << "The diameter of the tweeter is: "
      << aTweeter.diameter << "\n";

    std::cout << "The cone position of the tweeter is: "
      << aTweeter.conePosition << "\n";

    std::cout << "The diameter of the woofer is: "
      << aWoofer.diameter << "\n";

    std::cout << "The cone position of the woofer is: "
      << aWoofer.conePosition << "\n";
}