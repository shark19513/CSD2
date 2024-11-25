#include "oscillator.h"

#include <list>

Oscillator::Oscillator() : Oscillator(440, 0, "sine")
{
  std::cout << "Inside Oscillator default constructor" << std::endl;
}

Oscillator::Oscillator(std::string waveform)
  :Oscillator(440, 0, waveform)
{
  std::cout << "Inside Oscillator secondary constructor" << std::endl;
}

Oscillator::Oscillator(float frequency, float amplitude, std::string waveform)
  : freq(frequency), amp(amplitude)
{
  std::cout << "Inside Oscillator third constructor" << std::endl;
  sound = waveform; //this string is from the SoundSource baseclass
}

Oscillator::~Oscillator()
{
  std::cout << "Inside Oscillator destructor" << std::endl;
}


// setters/getters
void Oscillator::setFrequency(float frequency)
{
  if (frequency > 0 && frequency < 22050) {
    this->freq = frequency;
  } else {
    std::cout << "Frequency out of range"
    << "\nPlease enter a frequency betweeen 0 and 22050" << std::endl;
  }
}

float Oscillator::getFrequency() {
  return freq;
}

void Oscillator::setWaveform(std::string waveform) {
  std::list<std::string> valid_input = {"sine", "square", "triangle", "saw"};
  //TODO: make if statement that checks if waveform is in list valid_input

}


std::string Oscillator::getWaveform() {
  return sound;
}
