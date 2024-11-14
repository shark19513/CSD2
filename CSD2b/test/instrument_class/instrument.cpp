#include "instrument.h"
#include <iostream>

// default constructor
Instrument::Instrument() {
    cout << "Instrument - default constructor\n";

    sound = "silence";
}

// overloaded constructor
Instrument::Instrument(string snd) {
    cout << "Instrument - overloaded constructor\n";

    sound = snd;
}