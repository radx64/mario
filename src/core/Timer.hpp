#ifndef CORE_TIMER_HPP_
#define CORE_TIMER_HPP_

#include <cstdint>

namespace core
{

class Timer
{
public:
    Timer();
    void start();
    void stop();
    uint32_t getTicks();
    bool isRunning();

private:
    uint32_t ticksAtStart_;
    bool running_;
};

}  // namespace core

#endif  // CORE_TIMER_HPP_
