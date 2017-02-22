#ifndef ENVIRONMENT_COINBLOCK_HPP_
#define ENVIRONMENT_COINBLOCK_HPP_

#include "Object.hpp"
#include "Bitmap.hpp"
#include <memory>

class AnimatedBitmap;

namespace environment
{

class CoinBlock : public Object
{
public:
    CoinBlock(int type);

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
    float oryginalY_{};
};

}  // namespace environment

#endif  // ENVIRONMENT_COINBLOCK_HPP_
