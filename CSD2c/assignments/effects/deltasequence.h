//
// Created by Dean on 28/02/2024.
//

// Complex Wissel Signaal
# pragma once

#include <iostream>
#include "Filters.h"


struct DeltaSequence {
    static void run(Filter& filter){
        std::cout << "- DELTA SEQUENCE -" << std::endl;
        for (auto i = -3; i < 14; ++i){
            std::cout << i << ": " << filter.process( i == 0 ? 1 : 0  ) << std::endl;
        }
    }
};

