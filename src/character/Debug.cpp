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

}

void Debug::draw()
{
    auto renderer = context_.getRenderer();

    if (type_ == 0)
    {
        context_.getBitmapsContainer()->get(BitmapType::QUESTIONBLOCK_0)->draw(x,y);  
    }
    else
    {
        context_.getBitmapsContainer()->get(BitmapType::BRICK_RED)->draw(x,y);
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderDrawLine(renderer, x + w/2, y+h/2, x + w/2 + dx*150.0, y+h/2);
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
    SDL_RenderDrawLine(renderer, x + w/2, y+h/2, x + w/2, y+h/2 + dy*150.0);
}

bool Debug::isObjectAt(std::vector<Object*> gameObjects, float x, float y)
{
    for(auto object : gameObjects)
    {
        if ((x >= object->x && x < object->x + object->w) &&
            (y >= object->y && y < object->y + object->h))
        {
            std::cout << "Found object" << std::endl;
            return true;
        }
    }
    return false;
}

void Debug::simulate(std::vector<Object*> gameObjects)
{
    if (type_ != 0) return;  // for testing purposes
    auto keys = context_.getKeyboardState();

        float grav = 0.1;
        dy += grav; 

    x += dx;
    y += dy;


    if (keys->up)
    {
        if (!jumped_)
       {
            dy -= 4.4;
            jumped_ = true;
        }

    } else
    {
        //if (dy < 0) 
    }


    if (keys->left)  dx += -0.6;
    if (keys->right) dx += 0.6;

    if (dx > 5.0) dx = 5.0;
    if (dx < -5.0) dx = -5.0;

    if (!keys->left && !keys->right) dx *= 0.15;

    for (auto object : gameObjects)
    {
        if (object == this) continue; // skip collision with itself

        auto col = checkCollision(*object);
        (void)col;
        if (col.bottom)
        {
            y = object->y - h; 
            dy=0;
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
            instead of just bounding down
        **/
            if ( x + w - object->x < 10.0f)
            {
                if (!isObjectAt(gameObjects, object->x - w, object->y))
                {
                    x = object->x - w;
                }
                else
                {
                    y = object->y + object->h;
                    dy = -dy;  
                }
            }
            
            else if(object->x + object->w - x < 10.0f)
            {
                if (!isObjectAt(gameObjects, object->x + object->w , object->y))
                {
                    x = object->x + w;
                }
            }
            else
            {
                y = object->y + object->h;
                dy = -dy;
            }

        }         
    }
}


}  // namespace character
