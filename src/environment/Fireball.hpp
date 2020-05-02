#ifndef ENVIRONMENT_FIREBALL_HPP_
#define ENVIRONMENT_FIREBALL_HPP_

#include "Object.hpp"

#include "math/Vector2.hpp"

class AnimatedSprite;

namespace environment
{

class Fireball : public Object
{
public:
    Fireball(math::Vector2f initialPosition, math::Vector2f velocity);

    virtual void draw(double delta_time) override;
    virtual void onUpdate(std::vector<Object*> gameObjects, double timeStep) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    void die(bool hasHitEnemy);
    AnimatedSprite* bitmap_;
};

}  // namespace environment

#endif  // ENVIRONMENT_FIREBALL_HPP_
