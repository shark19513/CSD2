#include <iostream>
#include "audioToFile.h"
#include "customCallback.h"

#define WRITE_TO_FILE 0

//TODO: make all this shit and that shit on line 28, low priority

// struct SynthParameters {
//     std::string synthTyep;
//     std::string melodyName;
//     bool bitCrusherBypass;
//     int bitCrushAmount;
// };


int main () {
    std::cout << "Welcome to The Amazing Digital Synthesizer!!!!" << std::endl;
    std::cout << "loading..." << std::endl;
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource (44100);

#if WRITE_TO_FILE
    AudioToFile audioToFile;
    audioToFile.write (audioSource);
#else

// // hier
//     const auto waarde1 = "Dingetje";
//
//     SynthParameters synthParameters (waarde1, waarde2, waarde3, waarde4);
//     synthParameters.bitCrushAmount = 4;
//
//     audioSource.initializeSynthParameters( synthParameters );
//

    JUCEModule juceModule (audioSource);
    juceModule.init (2, 2);

    std::cout << "Press q + Enter to quit..." << std::endl;
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
        }
    }
#endif
    return 0;
}