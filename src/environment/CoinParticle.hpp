#ifndef ENVIRONMENT_COINPARTICLE_HPP_
#define ENVIRONMENT_COINPARTICLE_HPP_

#include "Object.hpp"

#include "math/Vector2.hpp"

class AnimatedSprite;

namespace environment
{

class CoinParticle : public Object
{
public:
    CoinParticle(math::Vector2f initialPosition);

    virtual void draw(double delta_time) override;
    virtual void onUpdate(std::vector<Object*> gameObjects, double timeStep) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    AnimatedSprite* bitmap_;
    math::Vector2f initialPosition_;
    double lifetime_{};
};

}  // namespace environment

#endif  // ENVIRONMENT_COINPARTICLE_HPP_
