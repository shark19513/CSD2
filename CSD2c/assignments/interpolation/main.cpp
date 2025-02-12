#include <iostream>
#include "interpolation.h"

int main() {
   std::cout << Interpolation::nnMap(0.6f, 4, 8) << std::endl;
   std::cout << Interpolation::linMap(0.6f, 4, 8) << std::endl;
}