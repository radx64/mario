#include "Timer.hpp"

#include <SDL2/SDL.h>

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
    uint32_t currentTime{0};

    if (!running_)
    {
        return currentTime;
    }

    return SDL_GetTicks() - ticksAtStart_;
}

bool Timer::isRunning()
{
    return running_;
}
