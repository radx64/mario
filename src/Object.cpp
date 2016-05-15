#include "Object.hpp"

#include <SDL2/SDL.h>

#include "Context.hpp"
#include "KeyboardState.hpp"

#include <iostream>

Object::Object(Context& context, int type) : context_(context), type_(type)
{
    r_ = 0xFF; g_ = 0xFF; b_ = 0xFF;
}

void Object::draw()
{
    SDL_Rect rect {x, y, w, h};
    auto renderer = context_.getRenderer();
    SDL_SetRenderDrawColor(renderer, r_, g_, b_, 0x00);
    SDL_RenderDrawRect(renderer, &rect);
}

void Object::checkCollision(Object& different)
{
    bool collsion = (abs(x - different.x) < (w + different.w) / 2) &&
        (abs(y - different.y) < (h + different.h) / 2);

    if (collsion)
    {
        r_ = 0xFF; g_ = 0x00; b_ = 0x00;
    }
    else
    {
        r_ = 0xFF; g_ = 0xFF; b_ = 0xFF;
    }
}

void Object::simulate()
{
    if (type_ != 0) return;  // for testing purposes

    auto keys = context_.getKeyboardState();
    if (keys->up)    y-=2;
    if (keys->down)  y+=2;
    if (keys->left)  x-=2;
    if (keys->right) x+=2;

}
