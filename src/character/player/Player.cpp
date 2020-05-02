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
    (void) delta_time;
    graphics_.draw(delta_time);
}

void Player::onCollisionWith(Collision collision, Object& object)
{
    physics_.onCollisionWith(collision, object);
}

void Player::onUpdate(std::vector<Object*> gameObjects, double delta_time)
{
    findCollisions(gameObjects);
    physics_.simulate(delta_time);
}

void Player::setAnimationDelay(double delay)
{
    graphics_.setDelay(delay);
}

}  // namespace player
}  // namespace character
