#ifndef ENVIRONMENT_SMALLBRICK_HPP_
#define ENVIRONMENT_SMALLBRICK_HPP_

#include "Object.hpp"

#include "math/Vector2.hpp"

class AnimatedSprite;

namespace environment
{

class SmallBrick : public Object
{
public:
    SmallBrick(math::Vector2f initialPosition, math::Vector2f velocity);

    virtual void draw() override;
    virtual void onUpdate(std::vector<Object*> gameObjects, double timeStep) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    AnimatedSprite* bitmap_;
    math::Vector2f velocity_;
};

}  // namespace environment

#endif  // ENVIRONMENT_SMALLBRICK_HPP_
