#include <iostream>
#include <stdexcept>

#include <SDL2/SDL.h>

#include "Context.hpp"
#include "FlipFlags.hpp"
#include "graphics/StillRenderer.hpp"
#include "Sprite.hpp"


Sprite::Sprite(const std::string& filename) : filename_(filename)
{
    SDL_Surface* sprite = SDL_LoadBMP(filename.c_str());
    if (sprite == nullptr)
    {
        throw(std::runtime_error(
            std::string("Couldn't load sprite!: ") + filename ));
    }

    SDL_SetColorKey(sprite, SDL_TRUE, SDL_MapRGB(sprite->format, 255, 0, 255));
    texture_ =  SDL_CreateTextureFromSurface(Context::getSdlRenderer(), sprite);
    SDL_FreeSurface(sprite);
    SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_);
}

Sprite::~Sprite()
{
   std::cout << "Sprite " << filename_ << " destroyed" << std::endl;
   SDL_DestroyTexture(texture_);
}

int Sprite::getWidth()
{
    return width_;
}

int Sprite::getHeight()
{
    return height_;
}

void Sprite::draw(graphics::IRenderer* renderer, int x, int y)
{
    SDL_Rect renderQuad = {x, y, width_, height_};
    renderer->draw(texture_, &renderQuad);
}

void Sprite::draw(graphics::IRenderer* renderer, int x, int y, const FlipFlags& f)
{
    SDL_Rect renderQuad = {x, y, width_, height_};
    renderer->draw(texture_, &renderQuad, &f);
}

void Sprite::copy(graphics::IRenderer* renderer, SDL_Rect* source, SDL_Rect* destination)
{
    renderer->draw(texture_, source, destination);
}

void Sprite::setColor(int r, int g, int b)
{
    SDL_SetTextureColorMod(texture_, r, g, b);
}
