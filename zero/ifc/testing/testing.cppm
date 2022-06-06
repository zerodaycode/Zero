module;

#include <iostream>

export module testing;

// export namespace zero {
export void say_hello() {
    std::cout << "Hi, from the Zero project from the testing module!" << std::endl;
}
// }
    