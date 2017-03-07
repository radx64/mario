#include "core/Timer.hpp"

namespace core
{

Timer::Timer() : running_(false)
{}

void Timer::start()
{
    running_ = true;
    start_ = std::chrono::system_clock::now();
}

void Timer::stop()
{
    running_ = false;
    start_ = TimePoint();
}

double Timer::getTicks()
{
    if (!running_)
    {
        return 0.0;
    }

    return (std::chrono::system_clock::now() - start_).count() / 1000000.0f;
}

bool Timer::isRunning()
{
    return running_;
}

}  // namespace core