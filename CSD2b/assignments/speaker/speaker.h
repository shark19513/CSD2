#ifndef SPEAKER_H
#define SPEAKER_H

#include "tweeter.h"
#include "woofer.h"

class Speaker{
public:
    Speaker();

    Tweeter aTweeter{1.2f};
    Woofer aWoofer{5.5f};
};

#endif