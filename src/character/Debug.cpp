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
    SDL_Rect rect {(int)x, (int)y, w, h};
    auto renderer = context_.getRenderer();
    context_.getBitmapsContainer()->get(BitmapType::BRICK_RED)->draw(x,y);
    SDL_SetRenderDrawColor(renderer, r_, g_, b_, 0x00);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderDrawLine(renderer, x + w/2, y+h/2, x + w/2 + dx*150.0, y+h/2);
    SDL_RenderDrawLine(renderer, x + w/2, y+h/2, x + w/2, y+h/2 + dy*150.0);
}

void Debug::simulate(std::vector<Object*> gameObjects)
{
    if (type_ != 0) return;  // for testing purposes
    auto keys = context_.getKeyboardState();

    if (keys->up)
    {
        if (!jumped_)
       {
            dy -= 0.4;
            jumped_ = true;
        }

    }

    if (keys->down)  dy += 0.3;
    if (keys->left)  dx = -0.3;
    if (keys->right) dx = 0.3;

    if (!keys->left && !keys->right) dx = 0;
    //if (!keys->up && !keys->down) dy = 0;


    for (auto object : gameObjects)
    {
        if (object == this) continue; // skip collision with itself

        auto col = checkCollision(*object);
        (void)col;
        if (col.bottom)
        {
            dy = 0;
            jumped_ = false;
            if(y + h > object->y) y = object->y - h;
        }

        if (col.left)
        {
            dx = 0;
            if(x + w > object->x) x = object->x + w;
        }      
            // if (dx != 0 && object->x > x) 
            // {
            //     x = object->x - w;
            //     dx = 0;
            //     return;
            // }

            // if (dx != 0 && object->x < x) 
            // {
            //     x = object->x + w;
            //     dx = 0;
            //     return;
            // }

            // if (dy != 0 && y < object->y)
            // {
            //     y = object->y - h;
            //     jumped_ = false;
            //     dy = 0;
            //     return;
            // }

            //  if (dy != 0 && y > object->y)
            // {
            //     y = object->y + h;
            //     dy = 0;
            //     jumped_ = false;
            //     return;
            // }           

        if(col.left || col.right || col.top || col.bottom)
        {
            std::cout << "Collision with {" 
                << col.left 
                << col.right 
                << col.top 
                << col.bottom 
                << "} of "<< object->type_  << "DX: " << dx << " DY:" << dy << std::endl;
        }

        float grav = 0.0015;
        dy += grav;

        x += dx;
        y += dy;

    }
}


}  // namespace character
