#ifndef CORE_FPS_COUNTER_HPP_
#define CORE_FPS_COUNTER_HPP_

#include <cstdint>

#include "core/Timer.hpp"

namespace core
{

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

}  // namespace core

#endif // CORE_FPS_COUNTER_HPP_
