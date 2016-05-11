#include <iostream>
#include "dummyWindow.hpp"

#define UNUSED(x) (void)(x)

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);
    std::cout << "Hello in Mario World!" << std::endl;
    DummyWindow dw;
    dw.create();
    return 0;
}
