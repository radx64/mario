#include "core/Event.hpp"

namespace core
{

Event::Event(std::string name) : name_(name) {}

Event::~Event() {};

std::string Event::name() const
{
    return name_;
}

}  // namespace core
