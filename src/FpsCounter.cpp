#include "FpsCounter.hpp"

FpsCounter::FpsCounter() : smoothing_(0.2)
{
    timer_.start(); 
}

float FpsCounter::measure()
{
    uint32_t currentTick = timer_.getTicks();
    float frametime = currentTick - lasttick_;
    float measurement = smoothing_ * frametime + (1.0 - smoothing_) * lastMeasurement_ ;
    lasttick_ = currentTick;
    lastMeasurement_ = measurement;
    return 1000.0 / measurement;
}
