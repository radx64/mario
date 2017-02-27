#include "core/Timer.hpp"

#include <SDL2/SDL.h>

namespace core
{

Timer::Timer() : ticksAtStart_(0), running_(false)
{}

void Timer::start()
{
    running_ = true;
    ticksAtStart_ = SDL_GetTicks();
}

void Timer::stop()
{
    running_ = false;
    ticksAtStart_ = 0;
}

uint32_t Timer::getTicks()
{
    if (!running_)
    {
        return 0;
    }

    return SDL_GetTicks() - ticksAtStart_;
}

bool Timer::isRunning()
{
    return running_;
}

}  // namespace core