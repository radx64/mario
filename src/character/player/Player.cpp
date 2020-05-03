#include "Player.hpp"

#include "Context.hpp"
#include "TextRenderer.hpp"

namespace character
{
namespace player
{

Player::Player()
: Object(ObjectType::Player),
graphics_(*this),
physics_(*this)
{
    collidable = true;
    moving = true;
}

void Player::draw(double delta_time)
{
    graphics_.draw(delta_time);
}

void Player::on_collision(Collision collision, Object& object)
{
    physics_.on_collision(collision, object);
}

void Player::on_simulate(double delta_time)
{
    physics_.simulate(delta_time);
}

void Player::on_input()
{
   physics_.input();
}

void Player::setAnimationDelay(double delay)
{
    graphics_.setDelay(delay);
}

}  // namespace player
}  // namespace character
