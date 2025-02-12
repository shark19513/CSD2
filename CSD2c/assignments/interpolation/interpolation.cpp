//
// Created by Semuel Leijten on 11/02/2025.
//

#include "interpolation.h"

float Interpolation::nnMap(float value, float low, float high) {
  // TODO: should do something with casting to int
  if (value >= 0.5f) {
    return high;
  } else {
    return low;
  }
}

float Interpolation::linMap(float value, float low, float high) {
  return low * (1 - value) + high * value;
}