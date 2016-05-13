#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <cstdint>

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

#endif  // TIMER_HPP_
