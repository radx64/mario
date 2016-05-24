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
    ~BrickBlock();

    virtual void draw() override;
    virtual void simulate(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    Context& context_;
    std::shared_ptr<Bitmap> bitmap_;
};

}  // namespace environment

#endif  // ENVIRONMENT_BRICKBLOCK_HPP_
