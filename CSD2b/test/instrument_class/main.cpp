#include "instrument.h"

int main() {
    Instrument instrument_1;
    Instrument instrument_2("donk");

    instrument_1.play();
    instrument_2.play();

    return 0;
}