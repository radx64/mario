#include <iostream>
#include <stdexcept>

#include <SDL2/SDL.h>

#include "Bitmap.hpp"
#include "Context.hpp"
#include "FlipFlags.hpp"
#include "graphics/StillRenderer.hpp"


Bitmap::Bitmap(const std::string& filename) : filename_(filename)
{
    SDL_Surface* bitmap = SDL_LoadBMP(filename.c_str());
    if (bitmap == nullptr)
    {
        throw(std::runtime_error(
            std::string("Couldn't load bitmap!: ") + filename ));
    }

    SDL_SetColorKey(bitmap, SDL_TRUE, SDL_MapRGB(bitmap->format, 255, 0, 255));
    texture_ =  SDL_CreateTextureFromSurface(Context::getSdlRenderer(), bitmap);
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

void Bitmap::draw(graphics::IRenderer* renderer, int x, int y)
{
    SDL_Rect renderQuad = {x, y, width_, height_};
    renderer->draw(texture_, &renderQuad);
}

void Bitmap::draw(graphics::IRenderer* renderer, int x, int y, const FlipFlags& f)
{
    SDL_Rect renderQuad = {x, y, width_, height_};
    renderer->draw(texture_, &renderQuad, &f);
}

void Bitmap::copy(graphics::IRenderer* renderer, SDL_Rect* source, SDL_Rect* destination)
{
    renderer->draw(texture_, source, destination);
}

void Bitmap::setColor(int r, int g, int b)
{
    SDL_SetTextureColorMod(texture_, r, g, b);
}
