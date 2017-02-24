#ifndef ENVIRONMENT_COINBLOCK_HPP_
#define ENVIRONMENT_COINBLOCK_HPP_

#include <memory>

#include "Bitmap.hpp"
#include "Object.hpp"
#include "math/Vector2.hpp"

class AnimatedBitmap;

namespace environment
{

class CoinBlock : public Object
{
public:
    CoinBlock(int type, math::Vector2f position);

    virtual void draw() override;
    virtual void update(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    AnimatedBitmap* fullAnimation_;
    AnimatedBitmap* depletedAnimation_;
    AnimatedBitmap* currentAnimation_;
    int8_t coins_;
    bool bounce_{false};
    int8_t bounceTick_{0};
    math::Vector2f originalPosition{};
};

}  // namespace environment

#endif  // ENVIRONMENT_COINBLOCK_HPP_
