#ifndef ENVIRONMENT_EXPLOSION_HPP_
#define ENVIRONMENT_EXPLOSION_HPP_

#include "Object.hpp"

#include "math/Vector2.hpp"

class AnimatedSprite;

namespace environment
{

class Explosion : public Object
{
public:
    Explosion(math::Vector2f initialPosition);

    virtual void draw(double delta_time) override;
    virtual void on_simulate(double timeStep) override;
    virtual void on_collision(Collision collision, Object& object) override;

protected:
    AnimatedSprite* bitmap_;
};

}  // namespace environment

#endif  // ENVIRONMENT_EXPLOSION_HPP_
