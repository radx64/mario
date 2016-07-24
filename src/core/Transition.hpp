#ifndef CORE_TRANSITION_HPP_
#define CORE_TRANSITION_HPP_

namespace core
{

class State;

struct Transition
{
    State* source;
    State* destination;
    const std::string eventName;
};

}  // namespace core

#endif  // CORE_STATE_HPP_
