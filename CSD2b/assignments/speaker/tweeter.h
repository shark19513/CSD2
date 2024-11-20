#ifndef TWEETER_H
#define TWEETER_H

#include "driver.h"

class Tweeter : public Driver {
public:
    // default constructor
    Tweeter();
    // overloaded constructor
    Tweeter(float diam);

};

#endif