#ifndef ENVIRONMENT_BLOCK_COINS_HPP_
#define ENVIRONMENT_BLOCK_COINS_HPP_

#include "environment/block/Question.hpp"

#include "math/Vector2.hpp"

namespace environment
{
namespace block
{

class Coins : public Question
{
public:
    Coins(math::Vector2f position, uint8_t coins);
    virtual void on_collision(Collision collision, Object& object) override;

private:
    int8_t coins_;
};

}  // namespace block
}  // namespace environment

#endif  // ENVIRONMENT_BLOCK_COINS_HPP_