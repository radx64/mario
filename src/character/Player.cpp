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

void Player::simulate()
{
    physics_.simulate();
}

void Player::onCollisionWith(Collision collision, Object& object)
{
    physics_.onCollisionWith(collision, object);
}

void Player::update(std::vector<Object*> gameObjects)
{
    simulate();
    Object::update(gameObjects);
    draw();

    Context::getTextRenderer()->draw(std::string("VX: ") + std::to_string(velocity.x),10,24,1.0);
    Context::getTextRenderer()->draw(std::string("VY: ") + std::to_string(velocity.y),10,32,1.0);
}


}  // namespace character
