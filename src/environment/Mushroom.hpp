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

    virtual void draw() override;
    virtual void onUpdate(std::vector<Object*> gameObjects, double timeStep) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    Sprite* sprite_;
    const float grav_ {300.0};
};

}  // namespace environment

#endif  // ENVIRONMENT_MUSHROOM_HPP
