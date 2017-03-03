#ifndef ENVIRONMENT_BLOCK_BRICK_HPP_
#define ENVIRONMENT_BLOCK_BRICK_HPP_

#include "Object.hpp"
#include <memory>

class Bitmap;

namespace environment
{
namespace block
{

class Bricks : public Object
{
public:
    Bricks();

    virtual void draw() override;
    virtual void onUpdate(std::vector<Object*> gameObjects) override;
    virtual void onCollisionWith(Collision collision, Object& object) override;

protected:
    Bitmap* bitmap_;
};

}  // namespace block
}  // namespace environment

#endif  // ENVIRONMENT_BLOCK_BRICK_HPP_
