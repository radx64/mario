#include "Debug.hpp"

#include <SDL2/SDL.h>

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
    SDL_Rect rect {x, y, w, h};
    auto renderer = context_.getRenderer();
    SDL_SetRenderDrawColor(renderer, r_, g_, b_, 0x00);
    SDL_RenderDrawRect(renderer, &rect);
}

void Debug::simulate(std::vector<Object*> gameObjects)
{
    if (type_ != 0) return;  // for testing purposes
    auto keys = context_.getKeyboardState();

    dx = 0;
    //dy = 0;

    if (keys->up)
    {
        if (!jumped_)
        {
            dy -= 50;
            jumped_ = true;
        }

    }
    if (keys->down)  dy += 10;
    if (keys->left)  dx -= 3;
    if (keys->right) dx += 3;

    for (auto object : gameObjects)
    {
        if (object == this) continue; // skip collision with itself

        if (checkCollision(*object))
        {
            if (dx != 0 && object->x > x) 
            {
                x = object->x - w;
                dx = 0;
                return;
            }

            if (dx != 0 && object->x < x) 
            {
                x = object->x + w;
                dx = 0;
                return;
            }

            if (dy != 0 && y < object->y)
            {
                y = object->y - h;
                jumped_ = false;
                dy = 0;
                return;
            }

             if (dy != 0 && y > object->y)
            {
                y = object->y + h;
                dy = 0;
                jumped_ = false;
                return;
            }           

            std::cout << "Collision with " << object->type_ << std::endl;
        }


    }
    x += dx;
    y += dy;

    dy = dy * 0.5 + 5;
}


}  // namespace character
