#ifndef CORE_STATEMACHINE_HPP_
#define CORE_STATEMACHINE_HPP_

#include <list>
#include <queue>

namespace core
{

class Event
{
public:
    Event(std::string name) : name_(name) {}
    virtual ~Event() {};

    std::string name() const
    {
        return name_;
    }


private:
    std::string name_;
};

class State
{
public:
    State(std::string name) : name_(name){};
    std::string name() const
    {
        return name_;
    }
    virtual void onEnter(const Event& event) = 0;
    virtual void onExit(const Event& event) = 0;

protected:
    std::string name_;
};

class TState : public State
{
public:
    TState(std::string name) : State(name){};
    virtual void onEnter(const Event& event) override
    {
        std::cout << "onEnter " << name() << " due to: " << event.name() << std::endl;
    };
    virtual void onExit(const Event& event) override
    {
        std::cout << "onExit " << name() << " due to: " << event.name() << std::endl;
    };
};

struct Transition
{
    State* source;
    State* destination;
    const std::string eventName;
};

class StateMachine
{
public:
using TransitionMap = std::list<Transition>;

StateMachine(const TransitionMap& tm)
: transitions_(tm), running_(false)
{
    for (auto& transition : transitions_)
    {
        std::cout << transition.source->name() << " -> "
        <<  transition.destination->name()
        << " due to "<< transition.eventName << std::endl;
    }
}

void setInitialState(State* initialState)
{
    internalState_ = initialState;
}

State* findDestination(const Event& event)
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

void run()
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
}

void processEvent(Event event)
{
    eventsQueue_.push(event);
    if (running_) return;
    run();
}

private:
    State* internalState_;
    TransitionMap transitions_;
    std::queue<Event> eventsQueue_;
    bool running_;
};

}  // namespace  core

#endif  // CORE_STATEMACHINE_HPP_
