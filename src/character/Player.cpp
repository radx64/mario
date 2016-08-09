#include "Player.hpp"

#include <iostream>

#include <SDL2/SDL.h>

#include "Bitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include "TextRenderer.hpp"

namespace character
{

Player::Player(Context& context, int type)
: Object(type),
context_(context),
graphics_(*this, context),
physics_(*this, context)
{
    h = context_.getBitmapsContainer()->get(BitmapType::MARIO_RUNNING_0)->getHeight();
    w = context_.getBitmapsContainer()->get(BitmapType::MARIO_RUNNING_0)->getWidth();
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

    context_.getTextRenderer()->draw(std::string("AX: ") + std::to_string(ax),10,24,1.0);
    context_.getTextRenderer()->draw(std::string("AY: ") + std::to_string(ay),10,32,1.0);
}


}  // namespace character
