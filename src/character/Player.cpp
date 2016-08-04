#include "Player.hpp"

#include <iostream>

#include <SDL2/SDL.h>

#include "Bitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include "FlipFlags.hpp"
#include "KeyboardState.hpp"
#include "TextRenderer.hpp"

namespace character
{

Player::Player(Context& context, int type)
: Object(type),
context_(context),
graphics_(*this, context)
{
    h = context_.getBitmapsContainer()->get(BitmapType::MARIO_RUNNING_0)->getHeight();
    w = context_.getBitmapsContainer()->get(BitmapType::MARIO_RUNNING_0)->getWidth();
}

void Player::draw()
{
    graphics_.draw();
}

bool Player::isObjectAt(std::vector<Object*> gameObjects, float x, float y)
{
    for(auto object : gameObjects)
    {
        if ((x >= object->x && x < object->x + object->w) &&
            (y >= object->y && y < object->y + object->h))
        {
            return true;
        }
    }
    return false;
}

void Player::bouceOfCeiling(Object* ceilingBlock)
{
    if (ay < 0.0)
    {
        ay = -ay;
        y += ay;
        std::cout << "Watch Your head!" << std::endl;
        y = ceilingBlock->y + ceilingBlock->h;
    }
}

void Player::onCollisionWith(Collision collision, Object& object)
{
    if (collision.get() == Collision::State::Left)
    {

         if (ax < 0) ax = 0;
         if(object.x + object.w > x) x = object.x + w;
    }

    if (collision.get() == Collision::State::Right)
    {
        if (ax > 0) ax = 0;
        if(x + w < object.x ) x = object.x - w;
    }

    if (collision.get() == Collision::State::Bottom)
    {
        y = object.y - h;
        if (ay > 0) ay = 0;
        jumped_ = false;
    }

    if (collision.get() == Collision::State::Top)
    {
    /**
        Below is special behaviour for future Mario development
        When Mario is jumping up and hit obstacle with his head
        He slides a bit to be next to the block (to jump on block above him)
        instead of just bouncing down
    **/
        bouceOfCeiling(&object);

        if ( x + w - object.x < 10.0f)
        {
            // if (!isObjectAt(gameObjects, object.x - w, object.y))
            // {
            //     x = object.x - w;
            // }
            // else
            // {
                bouceOfCeiling(&object);
            // }
        }

        else if(object.x + object.w - x < 10.0f)
        {
            // if (!isObjectAt(gameObjects, object.x + object.w , object.y))
            // {
            //     x = object.x + w;
            // }
            // else
            // {
                bouceOfCeiling(&object);
            // }
        }
        else
        {
            bouceOfCeiling(&object);
        }
    }
}

void Player::update(std::vector<Object*> gameObjects)
{
    auto keys = context_.getKeyboardState();

    ay += grav_;

    x += ax;
    y += ay;


    if (keys->up)
    {
        if (!jumped_)
       {
            ay = -8.0;
            jumped_ = true;
        }
        else
        {
            ay -= 0.04;
        }

    }
    else
    {
       ay += 0.2;
    }

    Object::update(gameObjects);

    if (keys->left)  ax += -0.6;
    if (keys->right) ax += 0.6;

    if (ax > horizontalMaxSpeed_) ax = horizontalMaxSpeed_;
    if (ax < -horizontalMaxSpeed_) ax = -horizontalMaxSpeed_;

    if (!keys->left && !keys->right) ax *= 0.65;

    draw();

    context_.getTextRenderer()->draw(std::string("AX: ") + std::to_string(ax),10,24,1.0);
    context_.getTextRenderer()->draw(std::string("AY: ") + std::to_string(ay),10,32,1.0);
}


}  // namespace character
