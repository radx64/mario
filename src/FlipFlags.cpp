#include "FlipFlags.hpp"

FlipFlags::FlipFlags()
{
    flags_ = SDL_FLIP_NONE;
}

void FlipFlags::NO_FLIP() { flags_ = SDL_FLIP_NONE;}

void FlipFlags::FLIP_HORIZONTAL()
{
    flags_  = static_cast<SDL_RendererFlip>(
        static_cast<int>(flags_) | static_cast<int>(SDL_FLIP_HORIZONTAL));
}

void FlipFlags::FLIP_VERTICAL()
{
    flags_  = static_cast<SDL_RendererFlip>(
        static_cast<int>(flags_) | static_cast<int>(SDL_FLIP_VERTICAL));
}

SDL_RendererFlip FlipFlags::getSDL() const
{
    return flags_;
}
