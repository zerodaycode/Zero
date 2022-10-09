import zero;

#ifdef _WIN32
    #include <iostream>
    #include <optional>
#else
    import <iostream>;
    import <optional>;
    import <vector>;
#endif

using namespace zero;

int main() {
    // TODO Now that the Testing Suite is integrated into the project,
    // this file should dissapear. Only stays here until a way to #include
    // headers // BUG (Only on WIN32) in a main file when importing modules that already uses
    // imports are found
    return 0;
}
    