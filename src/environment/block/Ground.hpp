#ifndef ENVIRONMENT_BLOCK_GROUND_HPP_
#define ENVIRONMENT_BLOCK_GROUND_HPP_

#include "Object.hpp"

class Sprite;

namespace environment
{
namespace block
{

class Ground : public Object
{
public:
    Ground();

    virtual void draw(double delta_time) override;
    virtual void on_simulate(double timeStep) override;
    virtual void on_collision(Collision collision, Object& object) override;

protected:
    Sprite* sprite_;
};

}  // namespace block
}  // namespace environment

#endif  // ENVIRONMENT_BLOCK_GROUND_HPP_
