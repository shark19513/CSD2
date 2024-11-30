#include "synthesizer.h"

int main() {
    std::cout << "\nin main\n";
    Synthesizer synth;

    std::cout << "osc1 frequency is: " << synth.osc1.getFrequency() << std::endl;
    synth.osc1.setFrequency(216);
    std::cout << "osc1 frequency is: " << synth.osc1.getFrequency() << std::endl;

    return 0;
}

// TODO: make keyboard setters and getters
// TODO: use more setters and getters in general

