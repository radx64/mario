#include "Player.hpp"

#include "Bitmap.hpp"
#include "BitmapsContainer.hpp"
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
    auto bitmap = Context::getBitmapsContainer()->get(BitmapType::MARIO_RUNNING_0);
    size.y = bitmap->getHeight();
    size.x = bitmap->getWidth();
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

void Player::onUpdate(std::vector<Object*> gameObjects)
{
    physics_.simulate();
    findCollisions(gameObjects);
}

void Player::setAnimationSpeed(short speed)
{
    graphics_.setSpeed(speed);
}

}  // namespace player
}  // namespace character
