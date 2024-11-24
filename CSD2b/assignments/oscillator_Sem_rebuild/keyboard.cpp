#include "keyboard.h"
#include <iostream>

Keyboard::Keyboard() : Keyboard(61)
{
    std::cout << "inside keyboard default constructor" << std::endl;
}

Keyboard::Keyboard(int numOfKeys)
    :keys(numOfKeys)
{
  std::cout << "inside keyboard secondary constructor" << std::endl;
}

Keyboard::~Keyboard()
{
  std::cout << "inside keyboard destructor" << std::endl;
}