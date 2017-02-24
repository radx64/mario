#ifndef FPS_COUNTER_HPP_
#define FPS_COUNTER_HPP_

#include <cstdint>

#include "Timer.hpp"

class FpsCounter
{
public:
    FpsCounter();
    float measure();
    float getLastMeasurement();

private:
    Timer timer_;
    uint32_t lasttick_{};
    float lastMeasurement_{};
    const float smoothing_{};
};

#endif // FPS_COUNTER_HPP_
