#ifndef CORE_TIMER_HPP_
#define CORE_TIMER_HPP_

#include <chrono>

namespace core
{

class Timer
{
public:
    Timer();
    void start();
    void stop();
    double getTicks();
    bool isRunning();

private:

    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    TimePoint start_;
    bool running_;
};

}  // namespace core

#endif  // CORE_TIMER_HPP_
