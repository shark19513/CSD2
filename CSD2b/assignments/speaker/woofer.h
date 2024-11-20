#ifndef WOOFER_H
#define WOOFER_H

#include "driver.h"

class Woofer : public Driver {
public:
    // default constructor
    Woofer();
    // overloaded constructor
    Woofer(float diam);

};

#endif