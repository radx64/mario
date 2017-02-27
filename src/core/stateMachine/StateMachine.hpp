#ifndef CORE_STATEMACHINE_STATEMACHINE_HPP_
#define CORE_STATEMACHINE_STATEMACHINE_HPP_

#include <list>
#include <set>
#include <queue>

#include "core/stateMachine/Event.hpp"
#include "core/stateMachine/State.hpp"
#include "core/stateMachine/Transition.hpp"

namespace core
{
namespace stateMachine
{

class StateMachine
{
public:
using TransitionMap = std::list<Transition>;

StateMachine(const TransitionMap& tm);
~StateMachine();
void setInitialState(State* initialState);
void processEvent(Event event);

private:
State* findDestination(const Event& event);

void run();
    State* internalState_;
    std::set<State*> states_;
    TransitionMap transitions_;
    std::queue<Event> eventsQueue_;
    bool running_;
};

}  // namespace stateMachine
}  // namespace  core

#endif  // CORE_STATEMACHINE_STATEMACHINE_HPP_
