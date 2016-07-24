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

    std::cout << "Hello in Mario World!" << std::endl;

    core::DemoState* start = new core::DemoState("Start");
    core::DemoState* running  = new core::DemoState("End");

    core::StateMachine sm({
        core::Transition {start, running, "Go"},
        core::Transition {running, start, "Stop"}
    });

    sm.setInitialState(start);
    sm.processEvent(core::Event("Stop"));
    sm.processEvent(core::Event("Go"));
    sm.processEvent(core::Event("Stop"));

    return 0;

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
    return 0;
}
