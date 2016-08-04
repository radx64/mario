#ifndef ENVIRONMENT_BRICKBLOCK_HPP_
#define ENVIRONMENT_BRICKBLOCK_HPP_

#include "Object.hpp"
#include "Bitmap.hpp"
#include <memory>

class Context;

namespace environment
{

class BrickBlock : public Object
{
public:
    BrickBlock(Context& context, int type);

    virtual void update(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    virtual void draw();
    Context& context_;
    std::shared_ptr<Bitmap> bitmap_;
    int hitCount_{0};
};

}  // namespace environment

#endif  // ENVIRONMENT_BRICKBLOCK_HPP_
