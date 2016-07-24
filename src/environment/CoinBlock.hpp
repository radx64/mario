#ifndef ENVIRONMENT_COINBLOCK_HPP_
#define ENVIRONMENT_COINBLOCK_HPP_

#include "Object.hpp"
#include "Bitmap.hpp"
#include <memory>

class Context;
class AnimatedBitmap;

namespace environment
{

class CoinBlock : public Object
{
public:
    CoinBlock(Context& context, int type);
    ~CoinBlock();

    virtual void draw() override;
    virtual void simulate(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    Context& context_;
    AnimatedBitmap* fullAnimation_;
    AnimatedBitmap* depletedAnimation_;
    AnimatedBitmap* currentAnimation_;
    int8_t coins_;
};

}  // namespace environment

#endif  // ENVIRONMENT_COINBLOCK_HPP_