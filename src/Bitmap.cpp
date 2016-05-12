#include "Bitmap.hpp"

#include <stdexcept>

#include <SDL2/SDL.h>

Bitmap::Bitmap(SDL_Renderer* renderer, std::string filename) : renderer_(renderer)
{
    SDL_Surface* bitmap = SDL_LoadBMP(filename.c_str());
    if (bitmap == nullptr)
    {
        throw(std::runtime_error(
            std::string("Couldn't load bitmap!: ") + filename ));
    }

    SDL_SetColorKey(bitmap, SDL_TRUE, SDL_MapRGB(bitmap->format, 255, 0, 255));
    texture_ =  SDL_CreateTextureFromSurface(renderer_, bitmap);
    SDL_FreeSurface(bitmap);
    SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_);
}

Bitmap::~Bitmap()
{
   SDL_DestroyTexture(texture_); 
}

int Bitmap::getWidth()
{
    return width_;
}

int Bitmap::getHeight()
{
    return height_;
}

void Bitmap::draw(int x, int y)
{
    SDL_Rect renderQuad = {x, y, width_, height_};
    SDL_RenderCopy(renderer_, texture_, NULL, &renderQuad);
}
