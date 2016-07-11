#include "Bitmap.hpp"
#include "FlipFlags.hpp"

#include <stdexcept>

#include <SDL2/SDL.h>

#include <iostream>



Bitmap::Bitmap(SDL_Renderer* renderer, const std::string& filename) :
renderer_(renderer), filename_(filename)
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
   std::cout << "Bitmap " << filename_ << " destroyed" << std::endl;
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

void Bitmap::draw(int x, int y, const FlipFlags& f)
{
    SDL_Rect renderQuad = {x, y, width_, height_};

    SDL_RendererFlip rf = f.getSDL();

    SDL_RenderCopyEx(renderer_, texture_, NULL, &renderQuad, 0, NULL, rf);
}

void Bitmap::copy(SDL_Rect* source, SDL_Rect* destination)
{
    SDL_RenderCopy(renderer_, texture_, source, destination);
}

void Bitmap::setColor(int r, int g, int b)
{
    SDL_SetTextureColorMod(texture_, r, g, b);
}
