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
    if (dy < 0.0) 
    {
        dy = -dy;  
        std::cout << "Watch Your head!" << std::endl;
        y = ceilingBlock->y + ceilingBlock->h;
    }
}

void Player::onCollisionWith(Collision collision, Object& object)
{
    if (collision.bottom)
        {
            y = object.y - h; 
            if (dy > 0) dy = 0;
            jumped_ = false;
        }

        if (collision.left)
        {
            dx = 0;
            if(object.x + object.w < x) x = object.x + w;
        }   

        if (collision.right)
        {
            dx = 0;
            if(x + w < object.x ) x = object.x - w;

        }     

        if (collision.top)
        {
        /** 
            Below is special behaviour for future Mario development
            When Mario is jumping up and hit obstacle with his head
            He slides a bit to be next to the block (to jump on block above him)
            instead of just bouncing down
        **/
            if ( x + w - object.x < 10.0f)
            {
                // if (!isObjectAt(gameObjects, object->x - w, object->y))
                // {
                //     x = object->x - w;
                // }
                // else
                // {
                    bouceOfCeiling(&object);
                // }
            }
            
            else if(object.x + object.w - x < 10.0f)
            {
                // if (!isObjectAt(gameObjects, object->x + object->w , object->y))
                // {
                //     x = object->x + w;
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
        std::cout << "Collision {" << collision.left 
        << collision.right 
        << collision.top 
        << collision.bottom 
        << "} with type_" 
        <<  object.type_ 
        << std::endl; 
}

void Player::simulate(std::vector<Object*> gameObjects)
{
    bitmap_->nextFrame();
    auto keys = context_.getKeyboardState();

    dy += grav_; 

    x += dx;
    y += dy;


    if (keys->up)
    {
        if (!jumped_)
       {
            dy = -6.0;
            jumped_ = true;
        }
        else
        {
            dy -= 0.04;
        }

    } 
    else
    {
       dy += 0.1; 
    }

    Object::simulate(gameObjects);

    if (keys->left)  dx += -0.6;
    if (keys->right) dx += 0.6;

    if (dx > 5.0) dx = 5.0;
    if (dx < -5.0) dx = -5.0;

    if (!keys->left && !keys->right) dx *= 0.95;

    context_.getTextRenderer()->draw(std::string("DX: ") + std::to_string(dx),10,24,1.0);
    context_.getTextRenderer()->draw(std::string("DY: ") + std::to_string(dy),10,32,1.0);
}


}  // namespace character
