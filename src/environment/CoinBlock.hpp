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

    virtual void update(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    virtual void draw();
    AnimatedBitmap* fullAnimation_;
    AnimatedBitmap* depletedAnimation_;
    AnimatedBitmap* currentAnimation_;
    int8_t coins_;
    bool bounce_{false};
    int8_t bounceTick_{0};
};

}  // namespace environment

#endif  // ENVIRONMENT_COINBLOCK_HPP_
