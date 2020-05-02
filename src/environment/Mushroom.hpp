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
    virtual void onUpdate(std::vector<Object*> gameObjects, double timeStep) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    enum class State
    {
        Spawning,
        Spawned
    };

    State state_;
    Sprite* sprite_;
    const float grav_ {300.0};
};

}  // namespace environment

#endif  // ENVIRONMENT_MUSHROOM_HPP
