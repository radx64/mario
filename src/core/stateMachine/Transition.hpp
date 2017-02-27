#ifndef CORE_TRANSITION_HPP_
#define CORE_TRANSITION_HPP_

namespace core
{
namespace stateMachine
{

class State;

struct Transition
{
    State* source;
    State* destination;
    const std::string eventName;
};

}  // namespace stateMachine
}  // namespace core

#endif  // CORE_STATE_HPP_
