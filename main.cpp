#define UNUSED(x) (void)(x)

#include <exception>
#include <iostream>
#include <stdexcept>
#include "Main.hpp"


int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    std::cout << "Hello from the Mario World!" << std::endl;
    Main main;
    try
    {
        main.init();
        main.loop();
    }
    catch(const std::runtime_error& ex)
    {
        std::cerr << "Exception was thrown: " << ex.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "Exception was thrown" << std::endl;
    }
    std::cout << "Good bye!" << std::endl;
    return 0;
}
