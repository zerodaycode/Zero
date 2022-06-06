module;

#include <iostream>

export module testing2;

export namespace zero {
    void say_hello_2() {
        std::cout << "Hi, from the Zero project from the testing2 module!" << std::endl;
    }
}