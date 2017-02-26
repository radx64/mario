#ifndef ENVIRONMENT_BRICKBLOCK_HPP_
#define ENVIRONMENT_BRICKBLOCK_HPP_

#include "Object.hpp"
#include "Bitmap.hpp"
#include <memory>

namespace environment
{

class BrickBlock : public Object
{
public:
    BrickBlock();

    virtual void draw() override;
    virtual void onUpdate(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    std::shared_ptr<Bitmap> bitmap_;
};

}  // namespace environment

#endif  // ENVIRONMENT_BRICKBLOCK_HPP_
