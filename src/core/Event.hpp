#ifndef CORE_EVENT_HPP_
#define CORE_EVENT_HPP_

#include <string>

namespace core
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

}  // namespace core

#endif  // CORE_EVENT_HPP_
