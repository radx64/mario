#include "core/Event.hpp"
#include "core/State.hpp"

namespace core
{

State::State(std::string name) : name_(name)
{

};

std::string State::name() const
{
    return name_;
}

State::~State()
{
    std::cout << "Destroing " << name() << std::endl;
};

DemoState::DemoState(std::string name) : State(name)
{

};

void DemoState::onEnter(const Event& event)
{
    std::cout << "onEnter " << name() << " due to: " << event.name() << std::endl;
};

void DemoState::onExit(const Event& event)
{
    std::cout << "onExit " << name() << " due to: " << event.name() << std::endl;
};

}  // namespace core
