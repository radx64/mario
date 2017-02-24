#ifndef ENVIRONMENT_COINPARTICLE_HPP_
#define ENVIRONMENT_COINPARTICLE_HPP_

#include "Object.hpp"
#include "Bitmap.hpp"

#include "math/Vector2.hpp"

class AnimatedBitmap;

namespace environment
{

class CoinParticle : public Object
{
public:
    CoinParticle(math::Vector2f initialPosition);

    virtual void draw() override;
    virtual void update(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    AnimatedBitmap* bitmap_;
    math::Vector2f initialPosition_;
    int32_t lifetime_{};
};

}  // namespace environment

#endif  // ENVIRONMENT_COINPARTICLE_HPP_
