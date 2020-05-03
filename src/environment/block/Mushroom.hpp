#ifndef ENVIRONMENT_BLOCK_MUSHROOM_HPP_
#define ENVIRONMENT_BLOCK_MUSHROOM_HPP_

#include "math/Vector2.hpp"

#include "environment/block/Question.hpp"

namespace environment
{
namespace block
{

class Mushroom : public Question
{
public:
    Mushroom(math::Vector2f position);
    virtual void on_collision(Collision collision, Object& object) override;
};

}  // namespace block
}  // namespace environment

#endif  // ENVIRONMENT_BLOCK_MUSHROOM_HPP_