#include "core/stateMachine/StateMachine.hpp"

#include <iostream>

namespace core
{
namespace stateMachine
{

StateMachine::StateMachine(const TransitionMap& tm)
: transitions_(tm), running_(false)
{
    for (auto& transition : transitions_)
    {
        states_.insert(transition.source);
        states_.insert(transition.destination);
    }
}

StateMachine::~StateMachine()
{
}

void StateMachine::setInitialState(State* initialState)
{
    internalState_ = initialState;
}

State* StateMachine::findDestination(const Event& event)
{
    for (auto& transition : transitions_)
    {
        if ((transition.source == internalState_) && (transition.eventName == event.name()))
        {
            return transition.destination;
        }
    }
    return nullptr;
}

void StateMachine::run()
{
    while(!eventsQueue_.empty())
    {

        Event event = eventsQueue_.front();
        eventsQueue_.pop();

        State* destination = findDestination(event);
        if (destination == nullptr)
        {
            std::cout << "Event from the moon. Staying where I am now." << std::endl;
        }
        else
        {
            internalState_->onExit(event);
            std::cout << "Moving from: " << internalState_->name() << " to " << destination->name() << std::endl;
            internalState_ = destination;
            destination->onEnter(event);
        }

    }
    running_ = false;
}

void StateMachine::processEvent(Event event)
{
    eventsQueue_.push(event);
    if (running_) return;
    run();
}

}  // namespace stateMachine
}  // namespace  core
