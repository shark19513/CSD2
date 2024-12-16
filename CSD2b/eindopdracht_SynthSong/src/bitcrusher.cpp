#include "bitcrusher.h"

BitCrusher::BitCrusher() {
  std::cout<<"BitCrusher - constructor\n";
}

BitCrusher::~BitCrusher() {
  std::cout<<"BitCrusher - destructor\n";
}

//bitreduction
float BitCrusher::applyBitReduction(float sample) {
  float stepSize = 1.0f / (1 << _bitDepth);
  return std::round(sample / stepSize) * stepSize;
}

void BitCrusher::setBitDepth(int bitDepth) {
  if (bitDepth > 0 && bitDepth <= 32 && std::floor(bitDepth) == bitDepth) {
    this->_bitDepth = bitDepth;
    std::cout << "Bit-Depth: " << this->_bitDepth << "\n";
  } else {
    std::cout << "Invalid input"
    << " please enter an integer between 0 and 32";
  }
}