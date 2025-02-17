//
// Created by Semuel Leijten on 11/02/2025.
//

#include "interpolation.h"

float Interpolation::nnMap(float value, float low, float high) {
  if(value < 0) {
    std::cout << "Value is lower than 0, please use values in range [0, 1]" << std::endl;
    return low;
  } else if(value > 1) {
    std::cout << "Value exceeds 1, please use values in range [0, 1]" << std::endl;
    return high;
  }

  if (static_cast<int>(value + 0.5f) == 0) {
    return low;
  }
  return high;
}

float Interpolation::linMap(float value, float low, float high) {
  if(value < 0) {
    std::cout << "Value is lower than 0, please use values in range [0, 1]" << std::endl;
    return low;
  } else if (value > 1) {
    std::cout << "Value exceeds 1, please use values in range [0, 1]" << std::endl;
    return high;
  }

  return low * (1 - value) + high * value;
}

float Interpolation::mapInRange(float value, float fromLow, float fromHigh, float toLow, float toHigh) {

  float partial = (value - fromLow) / (fromHigh - fromLow);
  float delta = toHigh - toLow;

  return toLow + delta * partial;
}