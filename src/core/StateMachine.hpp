#ifndef CORE_STATEMACHINE_HPP_
#define CORE_STATEMACHINE_HPP_

#include <list>
#include <set>
#include <queue>

#include "core/Event.hpp"
#include "core/State.hpp"
#include "core/Transition.hpp"

namespace core
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

}  // namespace  core

#endif  // CORE_STATEMACHINE_HPP_
