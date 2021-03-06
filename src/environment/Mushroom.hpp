#ifndef ENVIRONMENT_MUSHROOM_HPP
#define ENVIRONMENT_MUSHROOM_HPP

#include <memory>
#include <vector>

#include "Object.hpp"

class Sprite;

namespace environment
{

class Mushroom : public Object
{
public:
    Mushroom();

    virtual void draw(double delta_time) override;
    virtual void on_simulate(double timeStep) override;
    virtual void on_collision(Collision collision, Object& object) override;

protected:
    enum class State
    {
        Spawning,
        Spawned
    };

    State state_;
    Sprite* sprite_;
};

}  // namespace environment

#endif  // ENVIRONMENT_MUSHROOM_HPP
