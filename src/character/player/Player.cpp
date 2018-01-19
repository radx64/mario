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

void Player::draw()
{
    graphics_.draw();
}

void Player::onCollisionWith(Collision collision, Object& object)
{
    physics_.onCollisionWith(collision, object);
}

void Player::onUpdate(std::vector<Object*> gameObjects, double timeStep)
{
    physics_.simulate(timeStep);
    findCollisions(gameObjects);
}

void Player::setAnimationDelay(short delay)
{
    graphics_.setDelay(delay);
}

}  // namespace player
}  // namespace character
