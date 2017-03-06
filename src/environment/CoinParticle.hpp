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

    virtual void draw() override;
    virtual void onUpdate(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    AnimatedSprite* bitmap_;
    math::Vector2f initialPosition_;
    int32_t lifetime_{};
};

}  // namespace environment

#endif  // ENVIRONMENT_COINPARTICLE_HPP_
