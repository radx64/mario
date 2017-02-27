#include "core/stateMachine/Event.hpp"

namespace core
{
namespace stateMachine
{

Event::Event(std::string name) : name_(name) {}

Event::~Event() {};

std::string Event::name() const
{
    return name_;
}

}  // namespace stateMachine
}  // namespace core
