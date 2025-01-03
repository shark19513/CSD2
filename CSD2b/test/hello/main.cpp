#include <iostream>

void print(auto text) {
    if (typeid(text) == typeid(int) ||
        typeid(text) == typeid(float) ||
        typeid(text) == typeid(double)) {
            std::cout << std::to_string(text) << std::endl;
    } else {
        std::cout << text << std::endl;
    }
}

int main() {
    int twentySeven = 27;
    print("Hello World!");

    return 0;
}