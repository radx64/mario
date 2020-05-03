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

    virtual void draw(double delta_time) override;
    virtual void on_simulate(double timeStep) override;
    virtual void on_collision(Collision collision, Object& object) override;

protected:
    AnimatedSprite* bitmap_;
    math::Vector2f velocity_;
};

}  // namespace environment

#endif  // ENVIRONMENT_SMALLBRICK_HPP_
