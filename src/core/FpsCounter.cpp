#include "FpsCounter.hpp"

namespace core
{

FpsCounter::FpsCounter() : smoothing_(0.1f)
{
    timer_.start();
}

float FpsCounter::measure()
{
    uint32_t currentTick = timer_.getTicks();
    float frametime = currentTick - lasttick_;
    float measurement = smoothing_ * frametime + (1.0f - smoothing_) * lastMeasurement_ ;
    lasttick_ = currentTick;
    lastMeasurement_ = measurement;
    return 1000.0f / measurement;
}

float FpsCounter::getLastMeasurement()
{
    return 1000.0f / lastMeasurement_;
}

}  // namespace core