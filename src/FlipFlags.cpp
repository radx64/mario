#include "FlipFlags.hpp"

FlipFlags::FlipFlags()
{
    flags_ = SDL_FLIP_NONE;
}

void FlipFlags::no_flip() { flags_ = SDL_FLIP_NONE;}

void FlipFlags::flip_horizontal()
{
    flags_  = static_cast<SDL_RendererFlip>(
        static_cast<int>(flags_) | static_cast<int>(SDL_FLIP_HORIZONTAL));
}

void FlipFlags::flip_vertical()
{
    flags_  = static_cast<SDL_RendererFlip>(
        static_cast<int>(flags_) | static_cast<int>(SDL_FLIP_VERTICAL));
}

SDL_RendererFlip FlipFlags::toSDL() const
{
    return flags_;
}
