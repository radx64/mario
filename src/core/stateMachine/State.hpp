#ifndef CORE_STATEMACHINE_STATE_HPP_
#define CORE_STATEMACHINE_STATE_HPP_

#include <string>

class Event;

namespace core
{
namespace stateMachine
{

class State
{
public:
    State(std::string name);
    std::string name() const;
    virtual void onEnter(const Event& event) = 0;
    virtual void onExit(const Event& event) = 0;
    virtual ~State();

protected:
    std::string name_;
};

class DemoState : public State
{
public:
    DemoState(std::string name);
    virtual void onEnter(const Event& event) override;
    virtual void onExit(const Event& event) override;
};

}  // namespace stateMachine
}  // namespace core

#endif  // CORE_STATEMACHINE_STATE_HPP_
