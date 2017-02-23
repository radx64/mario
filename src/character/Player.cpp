#include "Player.hpp"

#include <iostream>

#include <SDL2/SDL.h>

#include "Bitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include "TextRenderer.hpp"

namespace character
{

Player::Player(int type)
: Object(type),
graphics_(*this),
physics_(*this)
{
    auto bitmap = Context::getBitmapsContainer()->get(BitmapType::MARIO_RUNNING_0);
    size.y = bitmap->getHeight();
    size.x = bitmap->getWidth();
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

void Player::update(std::vector<Object*> gameObjects)
{
    physics_.simulate();
    Object::update(gameObjects);
}

void Player::setAnimationSpeed(short speed)
{
    graphics_.setSpeed(speed);
}

}  // namespace character
