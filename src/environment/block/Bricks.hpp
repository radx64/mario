#ifndef ENVIRONMENT_BLOCK_BRICK_HPP_
#define ENVIRONMENT_BLOCK_BRICK_HPP_

#include "Object.hpp"

class Sprite;

namespace environment
{
namespace block
{

class Bricks : public Object
{
public:
    Bricks();

    virtual void draw(double delta_time) override;
    virtual void on_simulate(double timeStep) override;
    virtual void on_collision(Collision collision, Object& object) override;

protected:
    Sprite* bitmap_;
};

}  // namespace block
}  // namespace environment

#endif  // ENVIRONMENT_BLOCK_BRICK_HPP_
