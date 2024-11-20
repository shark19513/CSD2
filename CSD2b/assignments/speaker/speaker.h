#ifndef SPEAKER_H
#define SPEAKER_H

#include "tweeter.h"
#include "woofer.h"

class Speaker{
public:
    Speaker();

    Tweeter aTweeter;
    Woofer aWoofer;
};

#endif