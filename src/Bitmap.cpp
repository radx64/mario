#include "Bitmap.hpp"

#include <stdexcept>

#include <SDL2/SDL.h>

Bitmap::Bitmap(SDL_Renderer* renderer, std::string filename)
{
    SDL_Surface* bitmap = SDL_LoadBMP(filename.c_str());
    if (bitmap == nullptr)
    {
        throw(std::runtime_error(
            std::string("Couldn't load bitmap!: ") + filename ));
    }

    SDL_SetColorKey(bitmap, SDL_TRUE, SDL_MapRGB(bitmap->format, 255, 0, 255));
    texture_ =  SDL_CreateTextureFromSurface(renderer, bitmap);
    SDL_FreeSurface(bitmap);
    SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_);
}

Bitmap::~Bitmap()
{
   SDL_DestroyTexture(texture_); 
}

void Bitmap::draw(SDL_Renderer* renderer, int x, int y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width_;
    rect.h = height_;

    SDL_RenderCopy(renderer, texture_, NULL, &rect);

}
