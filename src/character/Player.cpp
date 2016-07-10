#include "Player.hpp"

#include <SDL2/SDL.h>
#include "Bitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include "KeyboardState.hpp"
#include "TextRenderer.hpp"
#include <iostream>

namespace character
{

Player::Player(Context& context, int type) : Object(type), context_(context)
{
    bitmap_ = new AnimatedBitmap({BitmapType::SQUID_0, BitmapType::SQUID_1},
        20,
        *context_.getBitmapsContainer()
    );
    h = context_.getBitmapsContainer()->get(BitmapType::SQUID_0)->getHeight();
    w = context_.getBitmapsContainer()->get(BitmapType::SQUID_0)->getWidth();

    // h = 32;
    // w = 32;
}

void Player::draw()
{
    bitmap_->draw(x, y);

    auto renderer = context_.getRenderer();
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
    SDL_Rect r{(int)x, (int)y, (int)w, (int)h};
    SDL_RenderDrawRect(renderer, &r);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderDrawLine(renderer, (int)x, (int)y, (int)x+(int)ax*4.0, (int)y);

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
    SDL_RenderDrawLine(renderer, (int)x, (int)y, (int)x, (int)y+(int)ay*4.0);


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
    if (collision.get() == Collision::State::Bottom)
        {
            y = object.y - h;
            if (ay > 0) ay = 0;
            jumped_ = false;
        }

        if (collision.get() == Collision::State::Left)
        {
             if (ax < 0) ax = 0;
            // if(object.x + object.w < x) x = object.x + w;
        }

        if (collision.get() == Collision::State::Right)
        {
            if (ax > 0) ax = 0;
            // if(x + w < object.x ) x = object.x - w;

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
        std::cout << "Collision {"
        << (collision.get() == Collision::State::Left)
        << (collision.get() == Collision::State::Right)
        << (collision.get() == Collision::State::Top)
        << (collision.get() == Collision::State::Bottom)
        << "} with type_"
        <<  object.type_
        << std::endl;
}

void Player::simulate(std::vector<Object*> gameObjects)
{
    bitmap_->nextFrame();
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

    Object::simulate(gameObjects);

    if (keys->left)  ax += -0.6;
    if (keys->right) ax += 0.6;

    if (ax > horizontalMaxSpeed_) ax = horizontalMaxSpeed_;
    if (ax < -horizontalMaxSpeed_) ax = -horizontalMaxSpeed_;

    if (!keys->left && !keys->right) ax *= 0.95;

    context_.getTextRenderer()->draw(std::string("AX: ") + std::to_string(ax),10,24,1.0);
    context_.getTextRenderer()->draw(std::string("AY: ") + std::to_string(ay),10,32,1.0);
}


}  // namespace character
