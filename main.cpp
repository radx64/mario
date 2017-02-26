#define UNUSED(x) (void)(x)

#include <exception>
#include <iostream>
#include <stdexcept>
#include "Main.hpp"

#include "core/StateMachine.hpp"


int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    std::cout << "Hello from the Mario World!" << std::endl;

    /** Some PoC of state machines, not yet incorporated into game itself **/
    core::DemoState start("Start");
    core::DemoState running("End");

    core::StateMachine sm({
        core::Transition {&start, &running, "Go"},
        core::Transition {&running, &start, "Stop"}
    });

    sm.setInitialState(&start);
    sm.processEvent(core::Event("Stop"));
    sm.processEvent(core::Event("Go"));
    sm.processEvent(core::Event("Stop"));

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
