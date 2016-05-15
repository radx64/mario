#include "Debug.hpp"

#include <SDL2/SDL.h>
#include "Bitmap.hpp"
#include "BitmapsContainer.hpp"
#include "Context.hpp"
#include "KeyboardState.hpp"
#include <iostream>


namespace character
{

Debug::Debug(Context& context, int type) : Object(type), context_(context)
{
    bitmap_ = new AnimatedBitmap({BitmapType::SQUID_0, BitmapType::SQUID_1},
        20,
        *context_.getBitmapsContainer()
    );
    h = context_.getBitmapsContainer()->get(BitmapType::SQUID_0)->getHeight();
    w = context_.getBitmapsContainer()->get(BitmapType::SQUID_0)->getWidth();
}

void Debug::draw()
{
    auto renderer = context_.getRenderer();

    if (type_ == 0)
    {
        bitmap_->draw(x, y);

    }
    else
    {
        context_.getBitmapsContainer()->get(BitmapType::BRICK_RED)->draw(x,y);
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
    SDL_Rect r {(int)x,(int)y,w,h};
    SDL_RenderDrawRect(renderer, &r);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderDrawLine(renderer, x + w/2, y+h/2, x + w/2 + dx*10.0, y+h/2);
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
    SDL_RenderDrawLine(renderer, x + w/2, y+h/2, x + w/2, y+h/2 + dy*10.0);
}

bool Debug::isObjectAt(std::vector<Object*> gameObjects, float x, float y)
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

void Debug::bouceOfCeiling(Object* ceilingBlock)
{
    if (dy < 0.0) 
    {
        dy = -dy;  
        std::cout << "Bounce off..." << std::endl;
        y = ceilingBlock->y + ceilingBlock->h;
    }
}

void Debug::simulate(std::vector<Object*> gameObjects)
{
    bitmap_->nextFrame();
    if (type_ != 0) return;  // for testing purposes
    auto keys = context_.getKeyboardState();

    float grav = 0.15;
    dy += grav; 

    x += dx;
    y += dy;


    if (keys->up)
    {
        if (!jumped_)
       {
            dy -= 6.0;
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


    if (keys->left)  dx += -0.6;
    if (keys->right) dx += 0.6;

    if (dx > 5.0) dx = 5.0;
    if (dx < -5.0) dx = -5.0;

    if (!keys->left && !keys->right) dx *= 0.95;

    for (auto object : gameObjects)
    {
        if (object == this) continue; // skip collision with itself

        auto col = checkCollision(*object);
        (void)col;
        if (col.bottom)
        {
            y = object->y - h; 
            dy = 0;
            jumped_ = false;
        }

        if (col.left)
        {
            dx = 0;
            if(object->x + object->w < x) x = object->x + w;
        }   

        if (col.right)
        {
            dx = 0;
            if(x + w < object->x ) x = object->x - w;

        }     

        if (col.top)
        {
        /** 
            Below is special behaviour for future Mario development
            When Mario is jumping up and hit obstacle with his head
            He slides a bit to be next to the block (to jump on block above him)
            instead of just bouncing down
        **/
            if ( x + w - object->x < 10.0f)
            {
                if (!isObjectAt(gameObjects, object->x - w, object->y))
                {
                    x = object->x - w;
                }
                else
                {
                    std::cout << "TADA1" << std::endl;
                    bouceOfCeiling(object);
                }
            }
            
            else if(object->x + object->w - x < 10.0f)
            {
                if (!isObjectAt(gameObjects, object->x + object->w , object->y))
                {
                    x = object->x + w;
                }
                else
                {
                    std::cout << "TADA2" << std::endl;
                    bouceOfCeiling(object); 
                }
            }
            else
            {
                std::cout << "TADA3" << std::endl;
                bouceOfCeiling(object);
            }

        }      
        if (col.left || col.right || col.top || col.bottom)
        {      
            std::cout << "Collision {" << col.left << col.right <<col.top << col.bottom 
            << "} with type_" <<  object->type_ << std::endl; 
        }
    }
}


}  // namespace character
