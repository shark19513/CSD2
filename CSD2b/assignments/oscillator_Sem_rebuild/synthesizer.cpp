#include "synthesizer.h"

Synthesizer::Synthesizer() {
    std::cout<<"inside Synthesizer constructor"<<std::endl;
}

Synthesizer::~Synthesizer() {
    std::cout << "inside Synthesizer destructor" << std::endl;
}


void Synthesizer::play() {
    std::cout << "inside Synthesizer play" << std::endl;
}