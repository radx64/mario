#ifndef CORE_STATEMACHINE_EVENT_HPP_
#define CORE_STATEMACHINE_EVENT_HPP_

#include <string>

namespace core
{
namespace stateMachine
{

class Event
{
public:
    Event(std::string name);
    virtual ~Event();
    std::string name() const;

private:
    std::string name_;
};

}  // namespace stateMachine
}  // namespace core

#endif  // CORE_STATEMACHINE_EVENT_HPP_
