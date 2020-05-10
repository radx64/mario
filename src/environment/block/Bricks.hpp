#ifndef ENVIRONMENT_BLOCK_BRICK_HPP_
#define ENVIRONMENT_BLOCK_BRICK_HPP_

#include "Object.hpp"

class Sprite;

namespace environment
{
namespace block
{

/* starts looking simmilar to coinblock, maybe need to extract smth like bouncable common impl */
class Bricks : public Object
{
public:
    Bricks(math::Vector2f initialPosition);

    virtual void draw(double delta_time) override;
    virtual void on_simulate(double timeStep) override;
    virtual void on_collision(Collision collision, Object& object) override;
    bool bounce_{false};
    double bounceTick_{0};
    math::Vector2f originalPosition{};

protected:
    Sprite* bitmap_;
};

}  // namespace block
}  // namespace environment

#endif  // ENVIRONMENT_BLOCK_BRICK_HPP_
